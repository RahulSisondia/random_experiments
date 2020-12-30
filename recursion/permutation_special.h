#include "../my_util.h"

// https://practice.geeksforgeeks.org/problems/permutation-with-spaces/0
void permutation_with_spaces_util(string in, string op,
                                  vector<string>& result) {
  if (in.empty()) {
    result.emplace_back(op);
    return;
  }

  string op1(op);
  op1.push_back('_');  // Include with space
  op1.push_back(in[0]);

  string op2(op);  // exclude space
  op2.push_back(in[0]);

  // Notice the strategegy that I am using to pass the substring. Rather erasing
  // the input string.
  permutation_with_spaces_util(in.substr(1), op1, result);   
  permutation_with_spaces_util(in.substr(1), op2, result);

  return;
}

vector<string> permutation_with_spaces(string in) {
  vector<string> result;
  string op;
  op.reserve(in.size() * 2);
  op.push_back(in[0]);
  permutation_with_spaces_util(in.substr(1), op, result);
  return result;
}

void test_permutation_with_spaces() {
  CHECK(permutation_with_spaces("ABC"), {"A_B_C", "A_BC", "AB_C", "ABC"});
  PRINT_MSG;
}

/*--------------Permutation with case changes------------------*/
// https://www.geeksforgeeks.org/permute-string-changing-case/

vector<string> permute_with_case_change(string in, string op,
                                        vector<string>& result) {
  if (in.empty()) {
    result.emplace_back(op);
    return result;
  }

  string op1(op), op2(op);
  op1.push_back(in[0]);
  op2.push_back(toupper(in[0]));
  permute_with_case_change(in.substr(1), op1, result);
  permute_with_case_change(in.substr(1), op2, result);
  return result;
}

void test_permute_with_case_change() {
  string temp;
  string in("abc");
  vector<string> tempv;
  permute_with_case_change(in, temp, tempv);
  CHECK(tempv, {"abc", "abC", "aBc", "aBC", "Abc", "AbC", "ABc", "ABC"});
  PRINT_MSG;
}

// -------Letter case permutation ----------------------------
// https://leetcode.com/problems/letter-case-permutation/

class Solution_784 {
 public:
  void solve(string in, string& op, vector<string>& result) {
    if (in.empty()) {
      result.emplace_back(op);
      return;
    }

    if (isalpha(in[0])) {
      string op1(op), op2(op);
      op1.push_back(tolower(in[0]));
      op2.push_back(toupper(in[0]));
      solve(in.substr(1), op1, result);
      solve(in.substr(1), op2, result);

    } else {
      string op1(op);
      op1.push_back(in[0]);
      solve(in.substr(1), op1, result);
    }
    return;
  }

  void solve_backtracking(string& s, int ind, string& cur,
                          vector<string>& ans) {
    if (cur.size() == s.size()) {
      ans.push_back(cur);
      return;
    }
    for (int i = ind; i < s.size(); ++i) {
      if (s[i] >= '0' && s[i] <= '9') {
        cur.push_back(s[i]);
        solve_backtracking(s, i + 1, cur, ans);
        cur.pop_back();
      } else {
        cur.push_back(toupper(s[i]));
        solve_backtracking(s, i + 1, cur, ans);
        cur.pop_back();
        cur.push_back(tolower(s[i]));
        solve_backtracking(s, i + 1, cur, ans);
        cur.pop_back();
      }
    }
    return;
  }
  /* Driver function */
  vector<string> letterCasePermutation(string S) {
    vector<string> result;
    string in(S);
    string op;
    solve(in, op, result);
    return result;
  }
};

void test_letter_case_permutation() {
  Solution_784 s;
  CHECK(s.letterCasePermutation("a1B2"), {"a1b2", "a1B2", "A1b2", "A1B2"});
  PRINT_MSG;
}