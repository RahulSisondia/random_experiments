#pragma once
#include "../my_util.h"

int eval_bool_expressions_rec(string str, int i, int j, bool to_eval) {
  count_ops++;
  /*
    Base Cases:
    if it is only one char then expression would return true based on what is
    asked to evaluate.
   */
  if (i > j) return 0;
  if (i == j) {
    if (to_eval == true)
      return (str[i] == 'T');
    else
      return (str[i] == 'F');
  }
  int res = 0;
  for (int k = i + 1; k <= j - 1; k += 2) {
    int left_true = eval_bool_expressions_rec(str, i, k - 1, true);
    int left_false = eval_bool_expressions_rec(str, i, k - 1, false);

    int right_true = eval_bool_expressions_rec(str, k + 1, j, true);
    int right_false = eval_bool_expressions_rec(str, k + 1, j, false);
    // cout << "i: " << i << " j:" << j << " k:" << k
    //      << " left_true : " << left_true << " left_false: " << left_false
    //      << " right_true: " << right_true << " right_false:" << right_false
    //      << " to_eval : " << to_eval << " result: " << res << endl;
    switch (str[k]) {
      case '|': {
        if (to_eval == true)
          res += left_true * right_true + left_false * right_true +
                 left_true * right_false;
        else
          res += left_false * left_false;
        break;
      }
      case '&': {
        if (to_eval == true)
          res += left_true * right_true;
        else
          res += left_false * right_false + left_true * right_false +
                 right_true * left_false;
        break;
      }
      case '^': {
        if (to_eval == true)
          res += left_true * right_false + left_false * right_true;
        else
          res += left_true * right_true + left_false * right_false;
        break;
      }
      default:
        throw "Invalid operator";
        break;
    }
  }
  return res;
}

int eval_bool_expressions_top_down_util(string str, int i, int j, bool to_eval,
                                        unordered_map<string, int>& dp) {
  /*
    Base Cases:
    if it is only one char then expression would return true based on what is
    asked to evaluate.
   */
  if (i > j) return 0;
  string key = to_string(i) + "_" + to_string(j) + "_" + to_string(to_eval);

  if (dp.find(key) != dp.end()) return dp[key];

  count_ops++;

  if (i == j) {
    if (to_eval == true)
      return (str[i] == 'T');
    else
      return (str[i] == 'F');
  }
  int res = 0;
  for (int k = i + 1; k <= j - 1; k += 2) {
    int left_true = eval_bool_expressions_rec(str, i, k - 1, true);
    int left_false = eval_bool_expressions_rec(str, i, k - 1, false);

    int right_true = eval_bool_expressions_rec(str, k + 1, j, true);
    int right_false = eval_bool_expressions_rec(str, k + 1, j, false);
    // cout << "i: " << i << " j:" << j << " k:" << k
    //      << " left_true : " << left_true << " left_false: " << left_false
    //      << " right_true: " << right_true << " right_false:" << right_false
    //      << " to_eval : " << to_eval << " result: " << res << endl;
    switch (str[k]) {
      case '|': {
        if (to_eval == true)
          res += left_true * right_true + left_false * right_true +
                 left_true * right_false;
        else
          res += left_false * left_false;
        break;
      }
      case '&': {
        if (to_eval == true)
          res += left_true * right_true;
        else
          res += left_false * right_false + left_true * right_false +
                 right_true * left_false;
        break;
      }
      case '^': {
        if (to_eval == true)
          res += left_true * right_false + left_false * right_true;
        else
          res += left_true * right_true + left_false * right_false;
        break;
      }
      default:
        throw "Invalid operator";
        break;
    }
  }
  dp[key] = res;
  return res;
}

int eval_bool_expressions_top_down(string str, int i, int j, bool to_eval) {
  unordered_map<string, int> dp;
  return eval_bool_expressions_top_down_util(str, i, j, to_eval, dp);
}

void test_evaluate_bool_expressions() {
  string str;
  str = "T^F&T";

  // count_ops = 0;
  CHECK(eval_bool_expressions_rec(str, 0, str.size() - 1, true), 2);
  // cout << "eval_bool_expressions_rec ops " << count_ops << endl;

  // count_ops = 0;
  CHECK(eval_bool_expressions_top_down(str, 0, str.size() - 1, true), 2);
  // cout << "eval_bool_expressions_top_down ops " << count_ops << endl;

  str = "T&T";
  CHECK(eval_bool_expressions_rec(str, 0, str.size() - 1, true), 1);
  CHECK(eval_bool_expressions_top_down(str, 0, str.size() - 1, true), 1);
  PRINT_MSG;
}