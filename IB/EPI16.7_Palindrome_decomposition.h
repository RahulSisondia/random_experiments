#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;
// 02044 ==>
// 020, 44
//  020, 4, 4
class Palindrome_decompositon {
private:
  bool is_palindrome(const string str) {
    for (size_t i = 0, j = str.size() - 1; i < j; i++, j--) {
      if (str[i] != str[j])
        return false;
    }
    return true;
  }
  // 02044 ==>
  // 020, 44
  //  020, 4, 4
  void decompositon(const string &str, vector<vector<string>> &result,
                    vector<string> &current, int offset) {

    if (offset == str.size()) {
      result.push_back(current);
      return;
    }

    for (int i = offset + 1; i <= str.size(); i++) {
      string substr = str.substr(offset, i - offset);
      if (is_palindrome(substr)) {
        cout << "Push substring " << substr << " i: " << i
             << " len : " << i - offset << endl;
        current.push_back(substr);
        decompositon(str, result, current, i);
        cout << "Popped substring " << current.back() << " i: " << i
             << " len : " << i - offset  << endl;
        current.pop_back();
      } else
	  {
        cout << "Not Palindrome " << substr << " i: " << i
             << " len : " << i - offset << endl;
	  }
    }
  }

public:
  vector<vector<string>> decompositon(const string &str) {
    vector<vector<string>> result;
    vector<string> current;
    decompositon(str, result, current, 0);
    return result;
  }
};
