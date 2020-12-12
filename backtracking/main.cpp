#include "EPI16.7_Palindrome_decomposition.h"
#include "N_queens.h"
#include "backtracking.h"
#include "t9combinations.h"

int main() {
  test_NQueens();
  test_t9_combinations();
  test_FindWord();
  test_SolveSudoku();
  // TODO: fix. some problem.
  test_palindromic_decomposition();
  return 0;
}