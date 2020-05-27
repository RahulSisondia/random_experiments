#pragma once
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <thread>
#include <utility>

#include "read_write_lock.h"
#include "semaphore.h"

using namespace std;

/*
 * This is a hack to lock cout printing by lines.  It's ugly and not too
 * general, but it seems to work for this.  Use coulock() << ... whatever ...
 * << unlendl; to print a line to cout while holding a mutex so one line won't
 * be interrupted by another.
 */
static recursive_mutex io_mux;
inline ostream &coulock() {
  io_mux.lock();
  return cout;
}
class unlocking_endl_class {};
unlocking_endl_class unlendl;
inline ostream &operator<<(ostream &s, unlocking_endl_class &e) {
  s << endl;
  io_mux.unlock();
  return s;
}

/*
 * Call rand() under a mutex lock.  Not safe to call from threads unguarded.
 */
int locked_rand() {
  static mutex mux;
  unique_lock<mutex> locker(mux);
  return rand();
}

/*
 * Choose one of the strings from a list at random.
 */
string rand_name() {
  string names[] = {"international",   "consolidated", "confederated",
                    "amalgomated",     "fubar",        "reinitialized",
                    "discombobulated", "missing",      "fiduciary",
                    "exasperated",     "laminated",    "embalmed"};
  int which = locked_rand() % (sizeof names / sizeof names[0]);
  return names[which];
}

/*
 * This is the shared data structure, a un-ordered linked list of names and
 * values.
 */
class data_node {
 private:
  int m_value;
  string m_name;

 public:
  data_node(string n, int v = 0) : m_value(v), m_name(n) {}
  int value() { return m_value; }
  void incval(int i) { m_value += i; }
  string name() { return m_name; }
};
list<data_node> data_list;

/*
 * The reader-writer control object.  This contains the methods for
 * readers and writers to enter and leave the reading and writing sections.
 */
readerwriter rwctl;

/*
 * Find a random name.  If not quiet, prints what it does.
 */
void finder(bool quiet) {
  // Choose a name at random to look for.
  string tofind = rand_name();

  rwctl.enter_read();

  // Scan for the name.
  auto scan = data_list.begin();
  while (scan != data_list.end()) {
    if (tofind == scan->name()) break;
    ++scan;
  }

  // Print results.
  if (!quiet) {
    if (scan == data_list.end())
      coulock() << tofind << " is not listed" << unlendl;
    else
      coulock() << scan->name() << " is valued at " << scan->value() << unlendl;
  }

  rwctl.leave_read();
}

/*
 * Find the average value in the list.  If not quiet, print it.
 */
void av(bool quiet) {
  int sum = 0;

  rwctl.enter_read();

  // Go through the list and make the sum.
  auto scan = data_list.begin();
  for (; scan != data_list.end(); ++scan) sum += scan->value();

  // Copy the size to local data so we can release.
  int ct = data_list.size();

  rwctl.leave_read();

  // Print results.
  if (!quiet) {
    if (ct > 0)
      coulock() << "Average is " << (double)sum / (double)ct << unlendl;
    else
      coulock() << "No items to average" << unlendl;
  }
}

/*
 * Find the range.  If not quiet, print the result.
 */
void range(bool quiet) {
  rwctl.enter_read();

  // Is there anything?
  if (data_list.size() == 0) {
    // No.  Bail.
    rwctl.leave_read();
    if (!quiet) coulock() << "No items for range computation." << unlendl;
  } else {
    // Yes. Find the range.
    auto scan = data_list.begin();
    int min = scan->value();
    int max = scan->value();
    for (++scan; scan != data_list.end(); ++scan) {
      if (min > scan->value()) min = scan->value();
      if (max < scan->value()) max = scan->value();
    }
    rwctl.leave_read();

    // Print the result.
    if (!quiet) coulock() << "Range is " << min << " to " << max << unlendl;
  }
}

/* This contains a count of reads.  It is only updated occassionally in order
   to reduce overhead.   It is an atomic counter so I can access it from
   different threads without using a mutex. */
atomic<int> read_count(0);

/*
 * Reader thread.  Performs some number of read operations.  Chooses
 * randomly which of finder, av or range to run.
 */
void reader(bool quiet, int cnt) {
  for (int i = 1; i <= cnt; ++i) {
    // Pick one randomly and run it.
    int choice = locked_rand() % 100;

    if (choice < 20)
      av(quiet);
    else if (choice < 40)
      range(quiet);
    else
      finder(quiet);

    // Sometimes we update the count.
    if (i % 256 == 0) read_count += 256;
  }
  read_count += cnt % 256;
}

/*
 *************** Some updaters. *******************
 */

/*
 * Update a random item.  Find the (an) item given by which, and add
 * the increment.
 */
void update(bool quiet, int increment, string which) {
  bool created = false;

  rwctl.enter_write();

  // Find in the list.
  auto scan = data_list.begin();
  for (; scan != data_list.end(); ++scan) {
    if (which == scan->name()) {
      // If found, increment.
      scan->incval(increment);
      break;
    }
  }

  // If not found add to the front.
  if (scan == data_list.end()) {
    // Add to the front of the list.
    data_list.push_front(data_node(which, increment));
    created = true;
  }

  rwctl.leave_write();

  // Fess up.
  if (!quiet)
    coulock() << which << " " << (created ? "created with" : "given") << " "
              << increment << unlendl;
}

/*
 * Delete a random item, if present.  If it picks a name which is not in the
 * list, does nothing.
 */
void remove_node(bool quiet) {
  // Choose a random name.
  string which = rand_name();

  rwctl.enter_write();

  // Scan the list to look for the randomly-chosen name.
  auto scan = data_list.begin();
  while (scan != data_list.end() && scan->name() != which) ++scan;

  // If something was found, remove it.
  bool was_deleted = false;
  if (scan != data_list.end()) {
    data_list.erase(scan);
    was_deleted = true;
  }

  rwctl.leave_write();

  // Let us know.
  if (!quiet) {
    if (was_deleted)
      coulock() << which << " deleted" << unlendl;
    else
      coulock() << which << " could not be found" << unlendl;
  }
}

/* This contains a count of reads.  It is not always up-to-date */
atomic<int> write_count(0);

/*
 * Update thread.  Performs some number of writing operations.  Chooses
 * randomly which of update or remove_node to call.
 */
void writer(bool quiet, int cnt) {
  for (int i = 1; i <= cnt; ++i) {
    int choice = locked_rand() % 100;

    if (choice < 65)
      update(quiet, locked_rand() % 100 - 10, rand_name());
    else
      remove_node(quiet);

    if (i % 256 == 0) {
      write_count += 256;
    }
  }
  write_count += cnt % 256;
}
