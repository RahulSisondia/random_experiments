#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

static int count_ops = 0;

//  Accept count of tests and number of inputs from the user.
  // string in;
  // string op;
  // op.reserve(in.size() * 2);
  // int N;
  // cin >> N;
  // while (N--) {
  //   cin >> in;
  //   op.push_back(in[0]);
  //   solve(in.substr(1), op);
  //   op.clear();
  //   in.clear();
  // }

template <typename t>
void PRINT_MATRIX(vector<vector<t>> m) {
  for (int i = 0; i < m.size(); i++) {
    cout << endl;
    for (int j = 0; j < m[0].size(); j++) {
      cout << m[i][j] << "  ";
    }
  }
  cout << endl;
}
template <typename t>
void PRINT_VECTOR(vector<t> vect) {
  std::for_each(vect.begin(), vect.end(),
                [](auto item) { cout << item << endl; });
}


template <typename t>
void CHECK(const t& returned, const t& expected) {
  if (returned != expected) {
    cout << "Test failed\n"
         << "Expected: " << expected << ", Returned: " << returned << endl;
    assert(0);
  }
}

template <typename t>
void CHECK_VECTOR(const vector<t>& vect, const vector<t>& result) {
  assert(vect.size() == result.size());
  std::for_each(vect.begin(), vect.end(), [&result](auto value) {
    assert(std::find(result.begin(), result.end(), value) != result.end());
  });
}

#define PASSED_MSG cout << __func__ << " tests passed." << endl