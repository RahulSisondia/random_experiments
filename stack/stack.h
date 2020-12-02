#include "../my_util.h"

/*
Given an array, print the Next Greater Element (NGE) for every element. The Next
greater Element for an element x is the first greater element on the right side
of x in array. Elements for which no greater element exist, consider next
greater element as -1.
*/
vector<int> next_greater_to_right(vector<int> v) {
  stack<int> s;
  vector<int> result;
  for (int i = v.size() - 1; i >= 0; i--) {
    if (s.empty()) {
      result.push_back(-1);
      s.push(v[i]);
    } else if (s.top() > v[i]) {
      result.push_back(s.top());
      s.push(v[i]);
    } else {
      while (s.empty() == false && s.top() <= v[i]) {
        s.pop();
      }
      if (s.empty())
        result.push_back(-1);
      else
        result.push_back(s.top());
      s.push(v[i]);
    }
  }
  reverse(result.begin(), result.end());
  return result;
}

void test_next_greater_to_right() {
  vector<int> v = {1, 3, 0, 0, 2, 4};
  // PRINT(next_greater_to_right(v), ",");
  CHECK(next_greater_to_right(v), {3, 4, 2, 2, 4, -1});
  PRINT_MSG;
}

/*
The only difference from above solution is that we start the loop from left to
right and don't reverse the array.
*/
vector<int> next_greater_to_left(vector<int> v) {
  stack<int> s;
  vector<int> result;
  for (int i = 0; i < v.size(); i++) {
    if (s.empty()) {
      result.push_back(-1);
      s.push(v[i]);
    } else if (s.top() > v[i]) {
      result.push_back(s.top());
      s.push(v[i]);
    } else {
      while (s.empty() == false && s.top() <= v[i]) {
        s.pop();
      }
      if (s.empty())
        result.push_back(-1);
      else
        result.push_back(s.top());
      s.push(v[i]);
    }
  }
  return result;
}

void test_next_greater_to_left() {
  vector<int> v = {1, 3, 0, 0, 2, 4};
  // PRINT(next_greater_to_left(v), ",");
  CHECK(next_greater_to_left(v), {-1, -1, 3, 3, 3, -1});
  PRINT_MSG;
}