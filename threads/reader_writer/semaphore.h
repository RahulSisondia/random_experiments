#pragma once
#ifndef __semaphore_h__
#define __semaphore_h__

#include <condition_variable>
#include <mutex>

/*
 * C++ doesn't actually have semaphores.  It has mutexes and condition
 * variables, which we can use to make a semaphore.
 */

class semaphore {
 public:
  semaphore(int init) : m_value(init) {}

  /* Semaphore down operation. */
  void wait();

  /* Semaphore up operation. */
  void signal();

 private:
  int m_value;                         // Value of semaphore.
  std::mutex m_mux;                    // Controls access.
  std::condition_variable m_waitcond;  // Controls waiting and restart
};

void semaphore::wait() {
  // This locks the mutex until it is destroyed at method exit.
  std::unique_lock<std::mutex> lck(m_mux);
  // Check the mutex value, and wait if need be.
  if (--m_value < 0) {
    // Make us wait.  When we wait, the mutex is unlocked until the
    // wait ends.
    m_waitcond.wait(lck);
  }
}

/* Semaphore up operation. */
void semaphore::signal() {
  // This locks the mutex until it is destroyed at method exit.
  std::unique_lock<std::mutex> lck(m_mux);
  // Start a waiting thread if required.
  if (++m_value <= 0) m_waitcond.notify_one();
}
#endif