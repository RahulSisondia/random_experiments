// https://youtu.be/_Lf1looyJMU
// https://www.geeksforgeeks.org/maximum-size-sub-matrix-with-all-1s-in-a-binary-matrix/
/*
Given a binary matrix, find out the maximum size square sub-matrix with all 1s.

0, 1, 1, 0, 1},
1, 1, 0, 1, 0},
{0, 1, 1, 1, 0},  <-----
{1, 1, 1, 1, 0},
{1, 1, 1, 1, 1},  <-----
{0, 0, 0, 0, 0}
*/

#include "../my_util.h"

int max_sub_square_rec_util(vector<vector<int>> v, int i, int j) {
  if (i == 0 || j == 0) {
    if (v[i][j]) return 1;
    return 0;
  }

  int m1 = max_sub_square_rec_util(v, i - 1, j);
  int m2 = max_sub_square_rec_util(v, i - 1, j - 1);
  int m3 = max_sub_square_rec_util(v, i, j - 1);

  int m = min({m1, m2, m3});
  if (v[i][j]) return m + 1;

  return m;
}

int max_sub_square_rec(vector<vector<int>> v) {
  return max_sub_square_rec_util(v, v.size() - 1, v[0].size() - 1);
}

int max_sub_square_memoize_util(vector<vector<int>> v, int i, int j,
                                vector<vector<int>> dp) {
  if (i == 0 || j == 0) {
    if (v[i][j]) return 1;
    return 0;
  }

  if (dp[i][j] != -1) return dp[i][j];
  int m1 = max_sub_square_memoize_util(v, i - 1, j, dp);
  int m2 = max_sub_square_memoize_util(v, i - 1, j - 1, dp);
  int m3 = max_sub_square_memoize_util(v, i, j - 1, dp);

  int m = min({m1, m2, m3});
  if (v[i][j]) m = m + 1;
  return dp[i][j] = m;
}

int max_sub_square_memoize(vector<vector<int>> v) {
  vector<vector<int>> dp(v.size() + 1, vector<int>(v[0].size() + 1, -1));
  for (int i = 0; i < v.size(); i++) dp[i][0] = 0;
  for (int j = 0; j < v[0].size(); j++) dp[0][j] = 0;
  return max_sub_square_memoize_util(v, v.size() - 1, v[0].size() - 1, dp);
}

void test_max_sub_square() {
  // clang-format off
  vector<vector<int>> v = {
      {0, 0, 1, 1, 1}, {1, 0, 1, 1, 1}, {0, 1, 1, 1, 1}, {1, 0, 1, 1, 1}};
  // clang-format on

  CHECK(max_sub_square_rec(v), 3);
  CHECK(max_sub_square_memoize(v), 3);
  PRINT_MSG;
}