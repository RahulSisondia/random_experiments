#include "../my_util.h"
/*
Pattern to solve backtracking problems.

bool Solve(configuration conf) {
  if (no more choices)  // BASE CASE
    return (conf is goal state);
  for (all available choices) {
    try
      one choice c;
    // recursively solve after making choice
    ok = Solve(conf with choice c made);
    if (ok)
      return true;
    else
      unmake choice c;
  }
  return false;  // tried all choices, no soln found
}
*/

/*
The base case does the check in the lexicon to know whether a given permutation
is a word or not. Each time we make a recursive call, we check the result to see
if it was successful, and if so, stop here. Only if it fails do we continue
exploring the other choices.
*/
using Lexicon = unordered_set<string>;
string FindWord(string soFar, string rest, const Lexicon &lex) {
  if (rest.empty()) {
    // PRINT("sofar :", soFar);
    return (lex.count(soFar) ? soFar : "");
  } else {
    for (int i = 0; i < rest.length(); i++) {
      string remain = rest.substr(0, i) + rest.substr(i + 1);
      string found = FindWord(soFar + rest[i], remain, lex);
      if (!found.empty()) return found;
    }
  }
  return "";  // empty string indicates failure
}

// Find the word or its anagram in the dictionary.
void test_FindWord() {
  string temp;
  CHECK(FindWord(temp, "tac", {"cab", "cat", "dog", "cacocab"}), {"cat"});
  PRINT_MSG;
}

/********************Sodoku Solver ********************/

using Grid = vector<vector<int>>;
#define UNASSIGNED 0

bool UsedInRow(Grid &grid, int row, int num) {
  for (int col = 0; col < grid[0].size(); col++)
    if (grid[row][col] == num) return true;
  return false;
}
bool UsedInCol(Grid &grid, int col, int num) {
  for (int row = 0; row < grid.size(); row++)
    if (grid[row][col] == num) return true;
  return false;
}

bool UsedInBox(Grid &grid, int boxStartRow, int boxStartCol, int num) {
  for (int row = boxStartRow; row < 3; row++)
    for (int col = boxStartCol; col < 3; col++)
      if (grid[row][col] == num) return true;
  return false;
}

bool NoConflicts(Grid &grid, int row, int col, int num) {
  return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) &&
         !UsedInBox(grid, row - row % 3, col - col % 3, num);
}

bool FindUnassignedLocation(Grid &grid, int &row, int &col) {
  for (row = 0; row < grid.size(); row++)
    for (col = 0; col < grid[0].size(); col++)
      if (grid[row][col] == UNASSIGNED) return true;
  return false;
}

bool SolveSudoku(Grid &grid) {
  int row, col;
  if (!FindUnassignedLocation(grid, row, col)) return true;  // success!
  for (int num = 1; num <= 9; num++) {       // consider digits 1 to 9
    if (NoConflicts(grid, row, col, num)) {  // if looks promising,
      grid[row][col] = num;                  // make tentative assignment
      if (SolveSudoku(grid)) return true;    // recur, if success, yay!
      grid[row][col] = UNASSIGNED;           // failure, unmake & try again
    }
  }
  return false;  // this triggers backtracking
}

void test_SolveSudoku() {
  /* clang-format off */
Grid grid =  { {3, 0, 6, 5, 0, 8, 4, 0, 0}, 
               {5, 2, 0, 0, 0, 0, 0, 0, 0}, 
               {0, 8, 7, 0, 0, 0, 0, 3, 1}, 
               {0, 0, 3, 0, 1, 0, 0, 8, 0}, 
               {9, 0, 0, 8, 6, 3, 0, 0, 5}, 
               {0, 5, 0, 0, 9, 0, 6, 0, 0}, 
               {1, 3, 0, 0, 0, 0, 2, 5, 0}, 
               {0, 0, 0, 0, 0, 0, 0, 7, 4}, 
               {0, 0, 5, 2, 0, 6, 3, 0, 0} };
  
  CHECK(SolveSudoku(grid), true);
  //PRINTV(grid,",", "");
  CHECK(grid, {
{3,1,6,5,2,8,4,9,7},
{5,2,9,1,4,7,8,6,3},
{4,8,7,6,5,2,9,3,1},
{6,9,3,4,1,5,7,8,2},
{9,7,2,8,6,3,1,4,5},
{7,5,1,3,9,4,6,2,8},
{1,3,4,7,8,9,2,5,6},
{2,6,8,9,3,1,5,7,4},
{8,4,5,2,7,6,3,1,9},
});
  /* clang-format on */
  PRINT_MSG;
}
