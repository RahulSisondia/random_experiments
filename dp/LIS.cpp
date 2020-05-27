// LIS.cpp : This file contains the 'main' function. Program execution begins
// and ends there.
//

#include <algorithm>
#include <climits>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

/*
  I was trying to implement algorithm take 3 mentioned at
  https://courses.engr.illinois.edu/cs473/sp2011/Lectures/08_handout.pdf
  but it did not workout so far.
*/

int LIS_ending(vector<int> v, int& max) {
  if (v.size() == 0) {
    return 0;
  }
  int m = 1;
  for (int i = 0; i < v.size() - 1; i++) {
    if (v[i] < v.back()) {
      m = std::max(m, 1 + LIS_ending({v.begin(), v.begin() + i}, max));
    }
  }
  if (m > max) max = m;
  return m;
}

// main function
int main() {
  // int arr[] = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };
  vector<int> v = {10, 22, 9, 33};
  int max = INT_MIN;
  int m = LIS_ending(v, max);
  cout << "Length of LIS is " << LIS_ending(v, max);
  return 0;
}