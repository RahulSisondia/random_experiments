#include <cmath>
#include <functional>
#include <future>
#include <iostream>
#include <thread>

// unique function to avoid disambiguating the std::pow overload set
int f(int x, int y) {
  std::cout << "task_bind:\t"
            << " thread_id: " << std::this_thread::get_id() << '\n';
  return std::pow(x, y);
}

void task_lambda() {
  std::packaged_task<int(int, int)> task([](int a, int b) {
    std::cout << "task_lambda:\t"
              << " thread_id: " << std::this_thread::get_id() << '\n';
    return std::pow(a, b);
  });
  std::future<int> result = task.get_future();

  task(2, 9);

  std::cout << "task_lambda result:\t" << result.get()
            << " thread_id: " << std::this_thread::get_id() << '\n';
}

void task_bind() {
  std::packaged_task<int()> task(std::bind(f, 2, 11));
  std::future<int> result = task.get_future();

  task();

  std::cout << "task_bind result:\t" << result.get()
            << " thread_id: " << std::this_thread::get_id() << '\n';
}

void task_thread() {
  std::packaged_task<int(int, int)> task(f);
  std::future<int> result = task.get_future();

  std::thread task_td(std::move(task), 2, 10);
  task_td.join();

  std::cout << "task_thread result:\t" << result.get()
            << " thread_id: " << std::this_thread::get_id() << '\n';
}

int main() {
  std::cout << "main_thread:\t"
            << " thread_id: " << std::this_thread::get_id() << '\n';
  task_lambda();
  task_bind();
  task_thread();
  return 0;
}