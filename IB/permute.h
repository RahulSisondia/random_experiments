#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename t>
void print(const vector<t> vect) {
  for (int i = 0; i < vect.size(); i++) cout << vect[i] << " ";
  cout << endl;
}

template <typename t>
class Permute {
  void permute_util(const vector<t> &A, vector<bool> &visited,
                    vector<t> &current, vector<vector<t>> &result, int level) {
    if (level == A.size()) {
      result.push_back(current);
      return;
    } else if (level > A.size())
      return;

    for (int i = 0; i < A.size(); ++i) {
      if (!visited[i]) {
        visited[i] = true;
        current.push_back(A[i]);
        std::cout << "Pushed : "
                  << " index : " << i << " level : " << level << "  ";
        print(current);
        permute_util(A, visited, current, result, level + 1);
        current.pop_back();
        visited[i] = false;
        std::cout << "Popped : "
                  << " index : " << i << " level : " << level << " ";
        print(current);
      }
    }
  }

 public:
  vector<vector<t>> permute(vector<t> &A) {
    vector<vector<t>> result;

    if (A.empty()) return result;

    vector<bool> visisted(A.size(), false);
    vector<t> current;

    sort(A.begin(), A.end());
    permute_util(A, visisted, current, result, 0);

    return result;
  }
};

class Permute_IB {
 public:
  void permute(vector<int> &num, int start, vector<vector<int>> &result) {
    if (start == num.size() - 1) {
      result.push_back(num);
      return;
    }
    for (int i = start; i < num.size(); i++) {
      swap(num[start], num[i]);
      permute(num, start + 1, result);
      swap(num[start], num[i]);
    }
  }

  vector<vector<int>> permute(vector<int> &num) {
    vector<vector<int>> result;
    if (num.size() == 0) return result;
    sort(num.begin(), num.end());
    permute(num, 0, result);
    return result;
  }
};
