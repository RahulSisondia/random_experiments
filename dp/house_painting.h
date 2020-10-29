#include "../my_util.h"

int paint_house_top_down_util(vector<vector<int>> m, int house,
                              int exclude_color, vector<vector<int>>& dp) {
  if (house == m.size()) return 0;
  int cost = 0;
  int temp_cost = numeric_limits<int>::max();
  for (int j = 0; j < m[0].size(); j++) {
    if (j != exclude_color) {
      if (dp[house + 1][j] != -1) return dp[house + 1][j];
      temp_cost = min(temp_cost, m[house][j] + paint_house_top_down_util(
                                                   m, house + 1, j, dp));
      dp[house + 1][j] = temp_cost;
    }
  }
  cost += temp_cost;
  return cost;
}

int paint_house_top_down(vector<vector<int>> m) {
  int cost = numeric_limits<int>::max();
  vector<vector<int>> dp(m.size() + 1, vector<int>(m[0].size() + 1, -1));
  int house = 0;
  for (int c = 0; c < m[0].size(); c++) {
    int temp_cost =
        m[house][c] + paint_house_top_down_util(m, house + 1, c, dp);
    cost = min(cost, temp_cost);
  }
  return cost;
}

int paint_house(vector<vector<int>> m, int house, int exclude_color) {
  if (house == m.size()) return 0;
  int cost = 0;
  int temp_cost = numeric_limits<int>::max();
  for (int j = 0; j < m[0].size(); j++) {
    if (j != exclude_color) {
      temp_cost = min(temp_cost, m[house][j] + paint_house(m, house + 1, j));
    }
  }
  cost += temp_cost;
  return cost;
}

/*
https://www.programcreek.com/2014/05/leetcode-paint-house-ii-java/
A builder is looking to build a row of N houses that can be of K different
colors. He has a goal of minimizing cost while ensuring that no two neighboring
houses are of the same color.

Given an N by K matrix where the nth row and kth column represents the cost to
build the nth house with kth color, return the minimum cost which achieves this
goal.

Approach: Seems like matrix chain multiplication.
*/
int paint_house(vector<vector<int>> m) {
  int cost = numeric_limits<int>::max();
  int house = 0;
  for (int c = 0; c < m[0].size(); c++) {
    int temp_cost = m[house][c] + paint_house(m, house + 1, c);
    cost = min(cost, temp_cost);
  }
  return cost;
}

int paint_house_new(vector<vector<int>> m, int house, int exclude_color) {
  if (house == m.size()) return 0;
  int cost = 0;
  int temp_cost = numeric_limits<int>::max();
  for (int j = 0; j < m[0].size(); j++) {
    if (exclude_color == -1 || j != exclude_color)
      temp_cost =
          min(temp_cost, m[house][j] + paint_house_new(m, house + 1, j));
  }

  cost += temp_cost;
  return cost;
}

// Handled the special case of first row in the same method.
int paint_house_new(vector<vector<int>> m) { return paint_house_new(m, 0, -1); }

void test_paint_house() {
  vector<vector<int>> m = {/*c0 c1 c2                                   */
                           {1, 2, 3},   // h0
                           {1, 1, 1},   // h1
                           {2, 3, 1},   // h2
                           {3, 3, 1}};  // h3

  CHECK(paint_house(m), 5);
  CHECK(paint_house_new(m), 5);
  CHECK(paint_house_top_down(m), 5);
  PRINT_MSG;
}