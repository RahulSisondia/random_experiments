// dutch_national_flag.cpp : This file contains the 'main' function. Program
// execution begins and ends there.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Sort the input array, the array is assumed
// to have values in {0, 1, 2}
void sort012(vector<int>& a) {
  int lo = 0;
  int hi = a.size() - 1;
  int mid = 0;

  while (mid <= hi) {
    switch (a[mid]) {
      case 0:
        std::swap(a[lo++], a[mid++]);
        break;
      case 1:
        mid++;
        break;
      case 2:
        std::swap(a[mid], a[hi--]);
        break;
    }
  }
}

// Utility function to print array arr[]
void printArray(vector<int> arr) {
  for (size_t i = 0; i < arr.size(); i++) cout << arr[i] << " ";
  cout << "\n";
}

// Driver Code
int main() {
  std::vector<int> arr = {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1};
  sort012(arr);

  cout << "array after segregation ";
  printArray(arr);

  getchar();
  return 0;
}
