// subarray-with-given-sum.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// void get_arrays(std::vector<std::vector<uint64_t>>& tests,
// std::vector<uint64_t>& sum_arr)
//{
//	string input;
//	getline(std::cin, input);
//	tests.reserve(stoi(input));
//	sum_arr.reserve(stoi(input));
//	while (!std::cin.eof())
//	{
//
//		// Read the array size
//		getline(std::cin, input);
//		if (std::cin.eof() || input.empty()) break;
//
//		string num;
//		stringstream ss(input);
//		getline(ss, num, ' ');
//		std::vector<uint64_t> test;
//		test.reserve(stoi(num));
//		tests.push_back(test);
//
//		// Read the sum array
//		getline(ss, num, ' ');
//		sum_arr.push_back(stoi(num));
//
//		// Read the array
//		getline(std::cin, input);
//		num.clear();
//		ss.str("");
//		ss.clear();
//		ss << input;
//		auto & test_arr = tests.back();
//		do {
//			getline(ss, num, ' ');
//			test_arr.push_back(stoi(num));
//		} while (!ss.eof());
//	}
//}

void get_arrays(std::vector<std::vector<uint64_t>>& tests,
                std::vector<uint64_t>& sum_arr) {
  size_t test_count;
  cin >> test_count;
  while (test_count != 0) {
  }
}
int subArraySum(const vector<uint64_t> arr, int sum) {
  /* Initialize curr_sum as value of first element
     and starting point as 0 */
  uint64_t curr_sum = arr[0];
  uint64_t start = 0, i;
  size_t n = arr.size();

  /* Add elements one by one to curr_sum and if the curr_sum exceeds the
     sum, then remove starting element */
  for (i = 1; i <= n; i++) {
    // If curr_sum exceeds the sum, then remove the starting elements
    while (curr_sum > sum && start < i - 1) {
      curr_sum = curr_sum - arr[start];
      start++;
    }

    // If curr_sum becomes equal to sum, then return true
    if (curr_sum == sum) {
      printf("Sum found between indexes %llu and %llu\n", start, i - 1);
      return 1;
    }

    // Add this element to curr_sum
    if (i < n) curr_sum = curr_sum + arr[i];
  }

  // If we reach here, then no subarray
  printf("No subarray found");
  return 0;
}

int main() {
  std::vector<std::vector<uint64_t>> tests;
  std::vector<uint64_t> sum_arr;
  get_arrays(tests, sum_arr);
  uint64_t i = 0;
  for (auto test : tests) {
    subArraySum(test, sum_arr[i++]);
  }
  return 0;
}
