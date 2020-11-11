#pragma once

#include "../my_util.h"

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
        // std::cout << "Pushed : "
        //           << " index : " << i << " level : " << level << "  ";
        permute_util(A, visited, current, result, level + 1);
        current.pop_back();
        visited[i] = false;
        // std::cout << "Popped : "
        //           << " index : " << i << " level : " << level << " ";
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
  void permute(vector<string> &str, int start, vector<vector<string>> &result) {
    if (start == str.size() - 1) {
      result.push_back(str);
      return;
    }
    for (int i = start; i < str.size(); i++) {
      swap(str[start], str[i]);
      permute(str, start + 1, result);
      swap(str[start], str[i]);
    }
  }

  vector<vector<string>> permute(vector<string> &num) {
    vector<vector<string>> result;
    if (num.size() == 0) return result;
    sort(num.begin(), num.end());
    permute(num, 0, result);
    return result;
  }
};

void test_permutations() {
  Permute<string> p;
  vector<string> s_vect{"A", "B", "C"};
  CHECK(p.permute(s_vect), {{"A", "B", "C"},
                            {"A", "C", "B"},
                            {"B", "A", "C"},
                            {"B", "C", "A"},
                            {"C", "A", "B"},
                            {"C", "B", "A"}});

  Permute_IB pib;
  CHECK(pib.permute(s_vect), {
                                 {"A", "B", "C"},
                                 {"A", "C", "B"},
                                 {"B", "A", "C"},
                                 {"B", "C", "A"},
                                 {"C", "B", "A"},
                                 {"C", "A", "B"},
                             });
  PRINT_MSG;
}