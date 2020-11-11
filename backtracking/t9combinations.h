#include "../my_util.h"
using namespace std;

void generate(vector<string> trans, string digits, int deep, string& res,
              vector<string>& set) {
  if (deep == digits.length()) {
    set.push_back(res);
    return;
  }

  int digit = digits[deep] - 48;
  for (size_t i = 0; i < trans[digit].size(); i++) {
    res.push_back(trans[digit][i]);
    generate(trans, digits, deep + 1, res, set);
    res.resize(res.size() - 1);
  }
}
vector<string> combinations(string digit) {
  vector<string> trans = {"",    "",    "abc",  "def", "ghi",
                          "jkl", "mno", "pqrs", "tuv", "wxyz"};

  int deep = 0;
  vector<string> set;
  string result;
  generate(trans, digit, deep, result, set);
  return set;
}

void test_t9_combinations() {
  CHECK(combinations("23"),
        {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"});

  PRINT_MSG;
}
