#include "../my_util.h"
/*
Assume the following rules are for the tic-tac-toe game on an n x n board
between two players:

A move is guaranteed to be valid and is placed on an empty block.
Once a winning condition is reached, no more moves are allowed.
A player who succeeds in placing n of their marks in a horizontal, vertical, or
diagonal row wins the game. Implement the TicTacToe class:

TicTacToe(int n) Initializes the object the size of the board n.
int move(int row, int col, int player) Indicates that player with id player
plays at the cell (row, col) of the board. The move is guaranteed to be a valid
move. Follow up: Could you do better than O(n2) per move() operation?
*/
/*
  Lessons :
  1. Whenever we see a board problem. Think of applying the Graph or DP.
  2. The processing is bit different that usual BFS but idea is sane.
  On very move we move in the eigth direction. If we find a match then we
  continue in the same direction in the hope that next value coulld also be the
  same.
  3. This agorith is slow though. It gives TLE in leetcode.
*/
class TicTacToe_bfs {
 public:
  /** Initialize your data structure here. */
  TicTacToe_bfs(int n) : board(n, vector<int>(n, 0)) {}

  /** Player {player} makes a move at ({row}, {col}).
      @param row The row of the board.
      @param col The column of the board.
      @param player The player, can be either 1 or 2.
      @return The current winning condition, can be either:
              0: No one wins.
              1: Player 1 wins.
              2: Player 2 wins.
  */
  int move(int row, int col, int player) {
    board[row][col] = player;  // Place the player on the board.
    int count = 0;
    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board[0].size(); j++) {
        if (board[i][j] == board[row][col])
          count = max(count, bfs(i, j, player));
      }
    }
    return (count == board.size()) ? player : 0;
  }

 private:
  int bfs(int row, int col, int player) {
    int max_count = 0;
    int r = 0;
    int c = 0;
    for (auto dir : dirs) {
      int count = 1;  // Procecced the current node
      r = row + dir[0];
      c = col + dir[1];
      while (is_valid(r, c, player)) {
        count++;
        /*
         We found a favorable move. Continue in the same direction in the hope
         we may found another favorable move.
        */
        r += dir[0];
        c += dir[1];
      }
      max_count = max(max_count, count);
    }
    return max_count;
  }
  bool is_valid(int row, int col, int player) {
    if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() ||
        board[row][col] != player) {
      return false;
    }
    return true;
  }

 public:
  vector<vector<int>> board;

  /*
  187
  206
  345
  */
  const array<array<int, 2>, 8> dirs = {
      {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}}};
};
/*
Lessons:
1.  Actually solutio os much simpler that it seems to be at first.
  We just need to imagine that for each player we just need to keep track of the
  sum for each row, colum and diagnols.
2. how to keep track of right diagnoal?
  (size - col - 1 == row)
*/
class TicTacToe {
 public:
  /** Initialize your data structure here. */
  TicTacToe(int n) {
    // Don't call reseve as that allocates space but don't initialize the
    // elements
    // https://stackoverflow.com/questions/13029299/stdvectorresize-vs-stdvectorreserve
    p1.row_sum.resize(n);
    p1.col_sum.resize(n);
    p2.row_sum.resize(n);
    p2.col_sum.resize(n);
    p1.l2r_diag = 0;
    p1.r2l_diag = 0;
    p2.l2r_diag = 0;
    p2.r2l_diag = 0;
    size = n;
  }

  /** Player {player} makes a move at ({row}, {col}).
      @param row The row of the board.
      @param col The column of the board.
      @param player The player, can be either 1 or 2.
      @return The current winning condition, can be either:
              0: No one wins.
              1: Player 1 wins.
              2: Player 2 wins.
  */
  int move(int row, int col, int player) {
    move_count++;
    if (move_count > size * size) return 0;

    if (player == 1) {
      // PRINT("size << ", p1.row_sum.capacity(), " row ", row);
      p1.row_sum[row]++;
      p1.col_sum[col]++;
      if (row == col) p1.l2r_diag++;
      // Tricky to get we take example then it becomes easier.
      if (size - col - 1 == row) p1.r2l_diag++;
      if (p1.row_sum[row] == size || p1.col_sum[col] == size ||
          p1.l2r_diag == size || p1.r2l_diag == size)
        return player;
    } else if (player == 2) {
      p2.row_sum[row]++;
      p2.col_sum[col]++;
      if (row == col) p2.l2r_diag++;
      if (size - col - 1 == row) p2.r2l_diag++;
      if (p2.row_sum[row] == size || p2.col_sum[col] == size ||
          p2.l2r_diag == size || p2.r2l_diag == size)
        return player;
    }
    return 0;
  }

 private:
  struct Player_info {
    vector<int> row_sum;
    vector<int> col_sum;
    int l2r_diag; /* \  */
    int r2l_diag; /* / */
  } p1, p2;
  int move_count;
  int size;
};

void test_tick_tac_toe_348() {
  {
    /*
     Test case#1
    Input
    ["TicTacToe", "move", "move", "move", "move", "move", "move", "move"]
    [[3], [0, 0, 1], [0, 2, 2], [2, 2, 1], [1, 1, 2], [2, 0, 1], [1, 0, 2],
    [2, 1,1]] Output [null, 0, 0, 0, 0, 0, 0, 1]
    */
    TicTacToe_bfs ttt(3);
    CHECK(ttt.move(0, 0, 1), 0);
    CHECK(ttt.move(0, 2, 2), 0);
    CHECK(ttt.move(2, 2, 1), 0);
    CHECK(ttt.move(1, 1, 2), 0);
    CHECK(ttt.move(2, 0, 1), 0);
    CHECK(ttt.move(1, 0, 2), 0);
    CHECK(ttt.move(2, 1, 1), 1);
  }
  {
    /*
    ["TicTacToe","move","move","move","move","move","move","move","move"]
[[3],[1,1,1],[0,1,2],[0,0,1],[2,2,2],[0,2,1],[2,0,2],[1,0,1],[2,1,2]]
[null,0,0,0,0,0,0,0,2]
*/
    TicTacToe_bfs ttt(3);
    CHECK(ttt.move(1, 1, 1), 0);
    CHECK(ttt.move(0, 1, 2), 0);
    CHECK(ttt.move(0, 0, 1), 0);
    CHECK(ttt.move(2, 2, 2), 0);
    CHECK(ttt.move(0, 2, 1), 0);
    CHECK(ttt.move(2, 0, 2), 0);
    CHECK(ttt.move(1, 0, 1), 0);
    CHECK(ttt.move(2, 1, 2), 2);
  }
  {
    /*
     Test case#1
    Input
    ["TicTacToe", "move", "move", "move", "move", "move", "move", "move"]
    [[3], [0, 0, 1], [0, 2, 2], [2, 2, 1], [1, 1, 2], [2, 0, 1], [1, 0, 2],
    [2, 1,1]] Output [null, 0, 0, 0, 0, 0, 0, 1]
    */
    TicTacToe ttt(3);
    CHECK(ttt.move(0, 0, 1), 0);
    CHECK(ttt.move(0, 2, 2), 0);
    CHECK(ttt.move(2, 2, 1), 0);
    CHECK(ttt.move(1, 1, 2), 0);
    CHECK(ttt.move(2, 0, 1), 0);
    CHECK(ttt.move(1, 0, 2), 0);
    CHECK(ttt.move(2, 1, 1), 1);
  }
  {
    /*
    ["TicTacToe","move","move","move","move","move","move","move","move"]
[[3],[1,1,1],[0,1,2],[0,0,1],[2,2,2],[0,2,1],[2,0,2],[1,0,1],[2,1,2]]
[null,0,0,0,0,0,0,0,2]
*/
    TicTacToe ttt(3);
    CHECK(ttt.move(1, 1, 1), 0);
    CHECK(ttt.move(0, 1, 2), 0);
    CHECK(ttt.move(0, 0, 1), 0);
    CHECK(ttt.move(2, 2, 2), 0);
    CHECK(ttt.move(0, 2, 1), 0);
    CHECK(ttt.move(2, 0, 2), 0);
    CHECK(ttt.move(1, 0, 1), 0);
    CHECK(ttt.move(2, 1, 2), 2);
  }
  PRINT_MSG;
}