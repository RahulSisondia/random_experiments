#include "../my_util.h"
// https://www.interviewbit.com/problems/generate-all-parentheses-ii/
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

/*
https://practice.geeksforgeeks.org/problems/print-n-bit-binary-numbers-having-more-1s-than-0s0252/1
Given a positive integer N, print all N bit binary numbers
having more 1’s than 0’s for any prefix of the number. Inputs:  (a)2   (b) 3
Outputs: (a) 11 10   (b) 111 110 10
*/

void print_n_bit_binary(int N, int ones, int zeros, string op,
                        vector<string>& result) {
  if (N == 0) {
    result.push_back(op);
    return;
  }

  string op1(op);
  op1.push_back('1');
  print_n_bit_binary(N - 1, ones + 1, zeros, op1, result);

  if (ones > zeros) {
    string op2(op);
    op2.push_back('0');
    print_n_bit_binary(N - 1, ones, zeros + 1, op2, result);
  }
}

vector<string> print_n_bit_binary(int N) {
  vector<string> result;
  int ones = 0;
  int zeros = 0;
  string op;
  print_n_bit_binary(N, ones, zeros, op, result);
  return result;
}
void test_print_n_bit_binary() {
  CHECK(print_n_bit_binary(3), {"111", "110", "101"});
}