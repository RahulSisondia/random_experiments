#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono;
/*
 Measure the time consumed by the function calls
*/
int main() {
  std::atomic<duration<long, milli>> atom_dur {}; // Thread safe
  milliseconds timespan(1000);  // 1 Sec
  auto start = high_resolution_clock::now();

  for (int i = 0; i < 5; i++) {
    auto st = high_resolution_clock::now();
    std::this_thread::sleep_for(timespan);  // Sleep for the timespan
    auto ed = high_resolution_clock::now();
    auto dur = atom_dur.load();
    dur += duration_cast<milliseconds>(ed - st);
    atom_dur.store(dur);
  }

  auto end = high_resolution_clock::now();
  auto sec = duration_cast<seconds>(end - start).count();
  cout << "Elapsed Seconds: " << sec << endl;
  cout << " Duration (in millisec): " << atom_dur.load().count() << endl;
  cout << " Duration (in sec): " << duration_cast<seconds>(atom_dur.load()).count() << endl;
  return 0;
}
