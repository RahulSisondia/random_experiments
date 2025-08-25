#include "../my_util.h"

bool synthesize_expression(vector<int> v, int i, int cv, int tv) {
  PRINT("i: ", i, " cv: ", cv);
  if (i == v.size()) {
    if (tv == cv) return true;
    return false;
  }
  if (cv > tv) {
    return false;
  }
  bool rv;
  if (i == 0)
    rv = synthesize_expression(v, i + 1, v[i], tv);
  else {
    rv = synthesize_expression(v, i + 1, cv + v[i], tv) ||
         synthesize_expression(v, i + 1, cv * v[i], tv) ||
         synthesize_expression(v, i + 1, ((cv * 10) + v[i]), tv);
  }
  return rv;
}

bool synthesize_expression(const vector<int>& v, int target) {
  return synthesize_expression(v, 0, 0, target);
}
/*
 you are given two operators + and * and a target value.
 you have to evaluate if the the given numbers can form the target value using
 the either of the two operators or appending the two digits.
*/
void test_synthesize_expression() {
  // 1+2*3
  CHECK(synthesize_expression({1, 2, 3}, 9), true);
  // 1*2+3
  CHECK(synthesize_expression({1, 2, 3}, 5), true);
  // 1+2+3
  CHECK(synthesize_expression({1, 2, 3}, 6), true);
  // 12*3
  CHECK(synthesize_expression({1, 2, 3}, 36), true);
  CHECK(synthesize_expression({1, 2, 3}, 30), false);
  PRINT_MSG;
}
