#pragma once
#include "../my_util.h"

/*
The only difference from above solution is that we just changed the condition
checks.
*/
vector<int> next_smaller_index_to_left(vector<int> v) {
  stack<int> s;  // Now we shall store index in the stack
  vector<int> left;
  const int pseudo = -1;
  for (int i = 0; i < v.size(); i++) {
    if (s.empty()) {
      left.push_back(pseudo);
      s.push(i);
    } else if (v[s.top()] < v[i]) {
      left.push_back(s.top());
      s.push(i);
    } else {
      while (s.empty() == false && v[s.top()] >= v[i]) {
        s.pop();
      }
      if (s.empty())
        left.push_back(pseudo);
      else
        left.push_back(s.top());
      s.push(i);
    }
  }
  return left;
}

void test_next_smaller_index_to_left() {
  vector<int> v = {1, 3, 0, 0, 2, 4};
  CHECK(next_smaller_index_to_left(v), {-1, 0, -1, -1, 3, 4});
  PRINT_MSG;
}

vector<int> next_smaller_index_to_right(vector<int> v) {
  stack<int> s;  // Now we shall store the indexes
  vector<int> right;
  const int pseudo = v.size();
  for (int i = v.size() - 1; i >= 0; i--) {
    if (s.empty()) {
      right.push_back(pseudo);
      s.push(i);
    } else if (v[s.top()] < v[i]) {
      right.push_back(s.top());
      s.push(i);
    } else {
      while (s.empty() == false && v[s.top()] >= v[i]) {
        s.pop();
      }
      if (s.empty())
        right.push_back(pseudo);
      else
        right.push_back(s.top());
      s.push(i);
    }
  }
  reverse(right.begin(), right.end());
  return right;
}

void test_next_smaller_index_to_right() {
  vector<int> v = {1, 3, 0, 0, 2, 4};
  // PRINT(next_smaller_index_to_right(v));
  // 6 is the pseudo index it it the size of array.
  CHECK(next_smaller_index_to_right(v), {2, 2, 6, 6, 6, 6});
  PRINT_MSG;
}

int max_histogram_area(const vector<int>& v) {
  auto nsl = next_smaller_index_to_left(v);
  auto nsr = next_smaller_index_to_right(v);
  vector<int> width(v.size());
  int max_area = numeric_limits<int>::min();
  for (int i = 0; i < v.size(); i++) {
    width[i] = nsr[i] - nsl[i] - 1;
    int area = width[i] * v[i];
    max_area = max(max_area, area);
  }
  return max_area;
}

void test_max_histogram_area() {
  vector<int> v = {2, 1, 5, 6, 2, 3};
  CHECK(max_histogram_area(v), 10);
  PRINT_MSG;
}

int max_rectangle_area_binary_matrix(vector<vector<int>> matrix) {
  vector<int> v{matrix[0].begin(), matrix[0].end()};
  int area =
      max_histogram_area(v);  // Calculate the max histogram in the first row.
  int max_area = area;
  for (int i = 1; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      if (matrix[i][j] == 0)
        // Be careful. It should be J not i.
        // Ignore the building since it's base is in air :)
        v[j] = 0;
      else
        v[j] = v[j] + matrix[i][j];  // Be careful. It should be J not i.
    }
    area = max_histogram_area(v);
    max_area = max(max_area, area);
    PRINT(max_area);
  }
  return max_area;
}

void test_max_rectangle_area_binary_matrix() {
  vector<vector<int>> matrix = {
      {0, 1, 1, 0}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 0, 0}};
  CHECK(max_rectangle_area_binary_matrix(matrix), 8);
  vector<int> v = {2, 3, 3, 2};
  CHECK(max_histogram_area(v), 8);
  PRINT_MSG;
}