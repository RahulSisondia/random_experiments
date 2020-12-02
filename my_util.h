#pragma once
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

static int count_ops = 0;

// Base function in the recursive class below .
void PRINTV() { cout << "\n"; }

template <typename T, typename... Types>
void PRINTV(T var1, Types... var2) {
  std::cout << var1 << " ";
  PRINTV(var2...);
}

template <typename t>
void PRINT(vector<t> vect, string delimiter = " ", string wrap = "") {
  map<string, string> wrap_dict = {
      {"", ""}, {"{", "}"}, {"(", ")"}, {"{\"", "\"}"}, {"\"", "\""}};
  int i = 0;
  std::cout << "{";
  for (; i < vect.size() - 1; i++) {
    if (wrap.empty())
      std::cout << vect[i] << delimiter;
    else
      std::cout << wrap << vect[i] << wrap_dict[wrap] << delimiter;
  }
  if (wrap.empty())
    std::cout << vect[i];
  else
    std::cout << wrap << vect[i] << wrap_dict[wrap];
  std::cout << "}";
  std::cout << endl;
}

template <typename t>
void PRINT(vector<vector<t>> m, string delimiter = " ", string wrap = "") {
  std::cout << "{";
  std::cout << endl;
  for (int i = 0; i < m.size(); i++) {
    PRINT(m[i], delimiter, wrap);
  }
  std::cout << "}";
  std::cout << endl;
}

template <typename t>
void CHECK(const pair<t, t>& returned, const pair<t, t>& expected) {
  if (returned != expected) {
    std::cout << "Test failed\n"
              << "Expected : {" << expected.first << ", " << expected.second
              << "}"
              << "Returned : {" << returned.first << ", " << returned.second
              << "}" << endl;
    assert(0);
  }
}

template <typename t>
void CHECK(const t& returned, const t& expected) {
  if (returned != expected) {
    std::cout << "Test failed\n"
              << "Expected: " << expected << ", Returned: " << returned << endl;
    assert(0);
  }
}

template <typename t>
void CHECK(const vector<t>& vect, const vector<t>& result) {
  if (result.size() != vect.size()) {
    std::cout << "Test failed due to size mismatch\n"
              << "Expected size: " << result.size()
              << ", Returned size: " << vect.size() << endl;
    assert(0);
  }
  for (int i = 0; i < vect.size(); i++) {
    CHECK(result[i], vect[i]);
  }
}

template <typename t>
void CHECK(const vector<vector<t>>& returned,
           const vector<vector<t>>& expected) {
  if (returned.size() != expected.size()) {
    std::cout << "Test failed due to size mismatch\n"
              << "Expected: " << expected.size()
              << ", Returned: " << returned.size() << endl;
    assert(0);
  }
  for (int i = 0; i < expected.size(); i++) {
    CHECK(returned[i], expected[i]);
  }
}

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

#define PRINT_MSG std::cout << __func__ << " tests passed." << endl