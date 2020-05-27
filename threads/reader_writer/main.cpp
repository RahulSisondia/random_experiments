#include "read_write_lock.h"
#include "reader_writer.h"
#include "semaphore.h"

/*
http://sandbox.mc.edu/~bennet/cs422b/notes/rw3_cpp.html
 ******************************************************************************
 * This is a readers/writers test application which maintains a shared linked
 * list of string/integer pairs.  It stars a specified number of reading and
 * writing threads which each perform a sepcified number of operations on
 * the list.  In addition, a monitor thread runs which periodically reports
 * the number of completed operations.  Run with command-line options to
 * control the program's behavior:
 *  -q    Run more quietly.  Want this for most measurements.
 *  -r N  Specify the number of reading threads, default 10.
 *  -w N  Specify the number of writing threads, default 10.
 *  -n N  Specify the number operations (reads or writes) performed by each
 *        thread.
 ******************************************************************************
 */

/*
 * This monitors progress.
 */
atomic<bool> monitor_stop(false);
void monitor(int nread, int nwrite) {
  while (!monitor_stop) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    int rc = read_count;
    int wc = write_count;
    coulock() << "=== " << rc << " reads (" << 100.0 * rc / nread << "%), "
              << wc << " writes (" << 100.0 * wc / nwrite
              << "%) ===" << unlendl;
  }
}

void usage() {
  cerr << "Flags: -q[uiet], -r nreader, -w nwriter "
       << "-n numop" << endl;
  exit(1);
}

/*
 * The main starts the threads that start the test threads, then wait it all.
 */
int main(int argc, char **argv) {
  // Parameters
  bool quiet = false;  // Threads should shut up.
  int nreader = 10;    // Number of reading threads.
  int nwriter = 10;    // Size of update threads.
  int nop = 10;        // Number of operations for each thread.

  // Collect the parameter values.
  for (argc--, argv++; argc > 0; argc--, argv++) {
    if (string(*argv) == "-q") {
      quiet = true;
    } else if ((*argv)[0] == '-' && argc > 1) {
      --argc;
      switch ((*argv++)[1]) {
        case 'r':
          nreader = atoi(*argv);
          break;
        case 'w':
          nwriter = atoi(*argv);
          break;
        case 'n':
          nop = atoi(*argv);
          break;
        default:
          usage();
      }
    } else {
      usage();
    }
  }

  cout << "Running " << nreader << " read threads and " << nwriter
       << " update threads, " << nop << " operations each" << endl;

  srand(time(NULL));

  // Start the reading and writing threads.  Start them alternately,
  // and collect in a list.
  list<thread> threads;
  for (int i = 0; i < max(nreader, nwriter); ++i) {
    if (i < nreader) threads.push_back(thread(reader, quiet, nop));
    if (i < nwriter) threads.push_back(thread(writer, quiet, nop));
  }

  // Start the progress monitor thread.
  thread monthread(monitor, nop * nreader, nop * nwriter);

  // Run join on all the reader/writer threads.
  for (auto &t : threads) {
    t.join();
  }

  // Now that they are done, ask the monitor to stop, then join it.
  monitor_stop = true;
  monthread.join();
}
