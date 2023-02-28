#include <atomic>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <thread>

class Async_pool {
 public:
  void submit_task(std::function<std::thread::id(int a, int b)>&& task, int a,
                   int b) {
    std::lock_guard<std::mutex> lg(m_q_mutex);
    m_tasks_result_q.emplace(std::async(std::launch::async, task, a, b));
    m_q_cv.notify_one();
  }
  void start_future_handler() {
    m_future_thread = std::thread([this]() {
      std::unique_lock<std::mutex> lc(m_q_mutex);
      while (!m_stop_signal || !m_tasks_result_q.empty()) {
        auto now = std::chrono::system_clock::now();
        auto timeout =
            m_q_cv.wait_until(lc, (now + std::chrono::microseconds(200)),
                              [&]() { return !m_tasks_result_q.empty(); });
        // Kept the timeout so low and printing here for some amusement.
        if (!timeout) std::cout << "cv timed out" << std::endl;
        // cv could have timed out. In that let the loop entry point decide when
        // to exit
        if (m_tasks_result_q.empty()) continue;
        auto thread_id = m_tasks_result_q.front().get();
        m_tasks_result_q.pop();
        std::stringstream ss;
        ss << "thread: " << thread_id << " processed " << std::endl;
        std::cout << ss.str();
      }
      lc.unlock();

      std::stringstream ss;
      ss << "All of the async requests are processed by thread: "
         << std::this_thread::get_id() << std::endl;
      std::cout << ss.str();
    });
  }
  void signal_to_stop() {
    std::cout << "Signaled to stop the thread";
    m_stop_signal = true;
  }
  ~Async_pool() {
    signal_to_stop();
    if (m_future_thread.joinable()) {
      m_q_cv.notify_one();
      std::this_thread::sleep_for(std::chrono::seconds(1));
      m_future_thread.join();
    }
  }

 private:
  std::queue<std::future<std::thread::id>> m_tasks_result_q;
  std::mutex m_q_mutex;
  std::atomic_bool m_stop_signal{false};
  std::condition_variable m_q_cv;
  std::thread m_future_thread;
};

auto task = [](int a, int b) {
  srand(time(NULL));
  int seconds = rand() % 10 + 1;
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
  auto thread_id = std::this_thread::get_id();
  std::stringstream ss;
  ss << "Thread : " << std::this_thread::get_id() << " worked for " << seconds
     << " seconds"
     << " Sum: " << a + b << std::endl;
  std::cout << ss.str();
  return thread_id;
};

int main() {
  Async_pool async_pool;
  async_pool.start_future_handler();

  for (int i = 0; i < 5; i++) {
    std::stringstream ss;
    ss << "Submitted task:" << i << std::endl;
    std::cout << ss.str();
    async_pool.submit_task(task, i, i + 10);
  }
  return 0;
}