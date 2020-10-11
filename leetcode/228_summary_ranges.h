#pragma once
/*
Given a sorted integer array without duplicates, return the summary of its
ranges. For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"]. Analysis:

My note - This is another sliding window problem. We need to have to pointers
first pointer increases suddenly.


This is an easy question. Since the ranges are all continuous integers, we just
need scan the whole array, compare each element with its previous one, if they
are not continuous numbers, the current number must belong a new range. In my
code, the start and end of the current range is kept in each iteration, don't
forget the case that only one number can become a range and the output format is
slight different required in this question.

https://leetcode.com/problems/summary-ranges/discuss/63284/10-line-c%2B%2B-easy-understand
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../my_util.h"

using namespace std;

vector<string> summary_range(const vector<int>& vect) {
  vector<string> res;
  int begin, end;
  size_t n = vect.size();
  for (int i = 0; i < n; i++) {
    begin = vect[i];  // Left side value in the sliding window
    while (i != n - 1 && vect[i] == vect[i + 1] - 1) {
      i++;
    }
    end = vect[i]; // Right side value in the sliding window
    if (begin == end) // if both are same then just push the element
      res.emplace_back(to_string(end));
    else {
      string str = to_string(begin) + "->" + to_string(end);
      res.emplace_back(str);
    }
  }
  return res;
}

void test_summary_range_228() {
  vector<string> res = summary_range({0, 1, 2, 4, 5, 7});
  CHECK_VECTOR(summary_range({0, 1, 2, 4, 5, 7}), {"0->2", "4->5", "7"});
  cout << "test_summary_range_228 passed" << endl;
}