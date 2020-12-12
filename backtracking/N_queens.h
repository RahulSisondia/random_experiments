#pragma once
#include "../my_util.h"

// Test if a newly placed queen will conflict any earlier queens
// placed before.
bool IsValid(const vector<int>& col_placement) {
  // We are intersted only in the entries filled so far.
  int row_id = col_placement.size() - 1;
  for (int i = 0; i < row_id; ++i) {
    int diff = abs(col_placement[i] - col_placement[row_id]);
    // diff == 0 signifies the same row or column check
    // diff == row_id -i signifies the diagnonal chec.
    if (diff == 0 || diff == row_id - i) {
      // A column or diagonal constraint is violated.
      return false;
    }
  }
  return true;
}

/*
In this approach we are are given row position of the queen. We then try to set
on each column on what works out. This solution prints all possible
arangements, we could easily modify if we were to validate an already filled
board.
*/
void SolveNQueens(int n, int row, vector<int>* col_placement,
                  vector<vector<int>>* result) {
  if (row == n) {
    // All queens are legally placed.
    result->emplace_back(*col_placement);
  } else {
    for (int col = 0; col < n; ++col) {
      col_placement->emplace_back(col);
      if (IsValid(*col_placement)) {
        SolveNQueens(n, row + 1, col_placement, result);
      }
      col_placement->pop_back();
    }
  }
}

vector<vector<int>> NQueens(int n) {
  vector<vector<int>> result;

  // Start with the 0th Row
  SolveNQueens(n, 0, make_unique<vector<int>>().get(), &result);
  return result;
}

void test_NQueens() {
  CHECK(NQueens(4), {{1, 3, 0, 2}, {2, 0, 3, 1}});
  PRINT_MSG;
}