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
/*
 In the interview, I would rather draw a box and then check in_valid in four
 steps.
 is_row_valid() ==> g[r--][c]
 is_col_valid() ==> g[r][c--]
 is_uppper_diagnoal ==> g[r--][c--]
 is_lower_diaginal ==> g[r++][c--]
*/
void SolveNQueens(int n, int row, vector<int>* col_placement,
                  vector<vector<int>>* result) {
  if (row == n) {
    // All queens are legally placed.
    result->emplace_back(*col_placement);
    return;
  }

  for (int col = 0; col < n; ++col) {
    col_placement->emplace_back(col);
    if (IsValid(*col_placement)) {
      SolveNQueens(n, row + 1, col_placement, result);
    }
    col_placement->pop_back();
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

/*
 We can initialize the board as
   vector<string> board(n,string(n,'.'));

 We run the recursion from the first row. In each row we try to place the
 the queen.
 here we are placing the queens row wise
*/
class Solution_51 {
 public:
  vector<vector<string>> ret;
  bool is_valid(vector<string>& board, int row, int col) {
    // check col
    for (int i = row; i >= 0; --i)
      if (board[i][col] == 'Q') return false;
    // check left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
      if (board[i][j] == 'Q') return false;
    // check right diagonal
    for (int i = row, j = col; i >= 0 && j < board.size(); --i, ++j)
      if (board[i][j] == 'Q') return false;
    return true;
  }
  void dfs(vector<string>& board, int row) {
    // exit condition
    if (row == board.size()) {
      ret.push_back(board);
      return;
    }
    // iterate every possible position
    for (int i = 0; i < board.size(); ++i) {
      if (is_valid(board, row, i)) {
        // make decision
        board[row][i] = 'Q';
        // next iteration
        dfs(board, row + 1);
        // back-tracking
        board[row][i] = '.';
      }
    }
  }
  vector<vector<string>> solveNQueens(int n) {
    // return empty if n <= 0
    if (n <= 0) return {{}};
    vector<string> board(n, string(n, '.'));
    dfs(board, 0);
    return ret;
  }
};

void test_NQueens_51() {
  Solution_51 s;
  PRINT_MSG;
}