#include "../my_util.h"

void permutation_with_spaces_util(string in, string op,
                                  vector<string>& result) {
  if (in.empty()) {
    result.emplace_back(op);
    return;
  }

  string op1(op);
  op1.push_back('_');
  op1.push_back(in[0]);

  string op2(op);
  op2.push_back(in[0]);

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
  CHECK_VECTOR(permutation_with_spaces("ABC"),
               {"A_BC", "A_B_C", "AB_C", "ABC"});
  PASSED_MSG;
}