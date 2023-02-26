#include <atomic>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <thread>

class Async_pool {
 public:
  void submit_task(std::function<std::thread::id(void)>&& task) {
    std::lock_guard<std::mutex> lg(m_q_mutex);
    m_tasks_result_q.emplace(std::async(std::launch::async, task));
    m_q_cv.notify_one();
  }
  void start_future_handler() {
    m_future_thread = std::thread([this]() {
      std::unique_lock<std::mutex> lc(m_q_mutex);
      while (!m_stop_signal || !m_tasks_result_q.empty()) {
        m_q_cv.wait(lc, [&]() { return !m_tasks_result_q.empty(); });
        auto thread_id = m_tasks_result_q.front().get();
        m_tasks_result_q.pop();
        std::stringstream ss;
        ss << "thread: " << thread_id << " processed " << std::endl;
        std::cout << ss.str();
      }

      std::stringstream ss;
      ss << "All of the async requests are processed by thread: "
         << std::this_thread::get_id() << std::endl;
      std::cout << ss.str();
    });
  }
  void signal_to_stop() { m_stop_signal = true; }
  ~Async_pool() { m_future_thread.join(); }

 private:
  std::queue<std::future<std::thread::id>> m_tasks_result_q;
  std::mutex m_q_mutex;
  std::atomic_bool m_stop_signal{false};
  std::condition_variable m_q_cv;
  std::thread m_future_thread;
};

auto task = []() {
  srand(time(NULL));
  int seconds = rand() % 10 + 1;
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
  auto thread_id = std::this_thread::get_id();
  std::stringstream ss;
  ss << "Thread : " << std::this_thread::get_id() << " worked for " << seconds
     << " seconds" << std::endl;
  std::cout << ss.str();
  return thread_id;
};

int main() {
  Async_pool async_pool;
  async_pool.start_future_handler();

  for (int i = 0; i < 10; i++) {
    async_pool.submit_task(task);
  }
  async_pool.signal_to_stop();
  return 0;
}