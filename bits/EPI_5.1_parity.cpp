// EPI_5.1_parity.cpp : Defines the entry point for the console application.
//
#include <cstdint>
#include <iostream>

void brute_force_to_find_parity(uint64_t num) {
  short count = 0;
  while (num) {
    if (num & 1) count++;
    num = num >> 1;
  }
  /*while (num) {
          count ^= (num & 1);
          num = num >> 1;
  }*/
  if (count % 2)
    std::cout << "odd";
  else
    std::cout << "even";
}

int main() {
  brute_force_to_find_parity(5);
  return 0;
}
