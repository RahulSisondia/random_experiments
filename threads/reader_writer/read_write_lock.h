#pragma once
#include "semaphore.h"
#include <atomic>

/*
 * This class provides the reader and writer lock controls using semaphores
 * as described in the text.
 */
class readerwriter {
 public:
  readerwriter() : m_readcount(0), m_writesem(0), m_mutex(1) {}

  /*
   * Operations to synchronize readers and writers.
   */
  void enter_read() {
    // This locks the mutex until it is destroyed at method exit.
    m_mutex.wait();
    if (++m_readcount == 1) m_writesem.wait();
    m_mutex.signal();
  }

  void leave_read() {
    m_mutex.wait();
    if (--m_readcount == 0) m_writesem.signal();
    m_mutex.signal();
  }

  void enter_write() { m_writesem.wait(); }

  void leave_write() { m_writesem.signal(); }

 private:
   int m_readcount;
  //std::atomic<int> m_readcount;
  semaphore m_mutex;
  semaphore m_writesem;
};

