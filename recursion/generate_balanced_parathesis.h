#include "../my_util.h"

void generate_balanced_parathesis(int open, int close, string op,
                                  vector<string>& result) {
  if (open == 0 && close == 0) {
    result.push_back(op);
    return;
  }

  if (open > 0) {
    string op1 = op;
    op1.push_back('(');
    generate_balanced_parathesis(open - 1, close, op1, result);
  }
  if (close > open) {
    string op2 = op;
    op2.push_back(')');
    generate_balanced_parathesis(open, close - 1, op2, result);
  }
}

vector<string> generate_balanced_parathesis(int N) {
  int open = N;
  int close = N;
  vector<string> result;
  string current;
  generate_balanced_parathesis(open, close, current, result);
  return result;
}

void test_generate_balanced_parathesis() {
  CHECK(generate_balanced_parathesis(3),
        {"((()))", "(()())", "(())()", "()(())", "()()()"});
  PRINT_MSG;
}