#pragma once

#include "../my_util.h"

template <typename t>
class Permute {
  /*
   We are passing the args by reference and we undo choices
   made before, another advantage of passing the visited set
   is that we avoid handle duplicate chars in the input.
   This approach is based on the DFS and preferred way to
   do the permutation.
   */
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

    vector<bool> visited(A.size(), false);
    vector<t> current;

    sort(A.begin(), A.end());
    permute_util(A, visited, current, result, 0);

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
/* This is another simple version to use without visiting flag. We keep on
  reducing the input. Also notice that we pass the arguments by value
 */
void RecPermute(string soFar, string rest, vector<string> &result) {
  if (rest.empty()) {
    result.push_back(soFar);
  } else {
    for (int i = 0; i < rest.length(); i++) {
      string remaining = rest.substr(0, i) + rest.substr(i + 1);
      RecPermute(soFar + rest[i], remaining, result);
    }
  }
}

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

  string temp;
  vector<string> result;
  RecPermute(temp, "abc", result);
  CHECK(result, {"abc", "acb", "bac", "bca", "cab", "cba"});
  PRINT_MSG;
}
