#pragma once
#include "../my_util.h"

// 02044 ==>
// 020, 44
//  020, 4, 4
bool is_palindrome(string str, int i, int j) {
  while (i <= j) {
    if (str[i] != str[j]) return false;
    i++;
    j--;
  }
  return true;
}

void palindromic_decomposition(string str, int index, vector<string>& current,
                               vector<vector<string>>& result) {
  if (index >= str.size()) {
    result.push_back(current);
    return;
  }

  for (int i = index; i < str.size(); i++) {
    if (is_palindrome(str, index, i)) {
      string temp = str.substr(index, i - index + 1);
      current.push_back(str.substr(index, i - index + 1));
      palindromic_decomposition(str, i + 1, current, result);
      current.pop_back();
    }
  }
}
vector<vector<string>> palindromic_decomposition(const string str) {
  vector<vector<string>> res;
  vector<string> current;
  palindromic_decomposition(str, 0, current, res);
  return res;
}
void test_palindromic_decomposition() {
  CHECK(palindromic_decomposition("02044"), {
                                                {"0", "2", "0", "4", "4"},
                                                {"0", "2", "0", "44"},
                                                {"020", "4", "4"},
                                                {"020", "44"},
                                            });
  PRINT_MSG;
}