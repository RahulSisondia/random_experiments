#pragma once
#include <memory>
#include <vector>

using namespace std;

// Test if a newly placed queen will conflict any earlier queens
// placed before.
bool IsValid(const vector<int>& col_placement) {
  // We are intersted only in the entries filled so far.
  int row_id = col_placement.size() - 1;
  for (int i = 0; i < row_id; ++i) {
    int diff = abs(col_placement[i] - col_placement[row_id]);
	// diff == 0 signifies the same, row or column check
	// diff == row_id -i signifies the diagnonal chec.
    if (diff == 0 || diff == row_id - i) {
      // A column or diagonal constraint is violated.
      return false;
    }
  }
  return true;
}

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
  SolveNQueens(n, 0, make_unique<vector<int>>().get(), &result);
  return result;
}