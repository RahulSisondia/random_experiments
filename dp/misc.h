#pragma once

#include "../my_util.h"
/*
https://leetcode.com/problems/min-cost-climbing-stairs/
On a staircase, the i-th step has some non-negative cost cost[i] assigned (0
indexed).

Once you pay the cost, you can either climb one or two steps. You need to find
minimum cost to reach the top of the floor, and you can either start from the
step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.
Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping
cost[3].
*/

class Solution {
 public:
  vector<int> dp;
  int minCostClimbingStairs(const vector<int>& cost, int i) {
    if (i < 0) return 0;
    if (i == 0 || i == 1) return dp[i] = cost[i];

    if (dp[i]) return dp[i];
    return dp[i] = cost[i] + min(minCostClimbingStairs(cost, i - 1),
                                 minCostClimbingStairs(cost, i - 2));
  }
  int minCostClimbingStairs(const vector<int>& cost) {
    int size = cost.size();
    dp = vector<int>(size, 0);
    return min(minCostClimbingStairs(cost, size - 1),
               minCostClimbingStairs(cost, size - 2));
  }

  int min_cost_bottom_up(const vector<int>& cost) {
    int n = cost.size();
    vector<int> dp(n + 1, 0);
    if (n == 0) return 0;
    if (n == 1) return cost[0];
    dp[0] = cost[0];
    dp[1] = cost[1];
    for (int i = 2; i <= n; ++i) {
      dp[i] = min(dp[i - 1], dp[i - 2]) + (i == n ? 0 : cost[i]);
    }
    return dp[n];
  }
};

void test_sairecase_746() {
  Solution s;
  CHECK(s.minCostClimbingStairs({1, 100, 1, 1, 1, 100, 1, 1, 100, 1}), 6);
  CHECK(s.min_cost_bottom_up({1, 100, 1, 1, 1, 100, 1, 1, 100, 1}), 6);
  PRINT_MSG;
}

/*
https://leetcode.com/problems/dungeon-game/
The demons had captured the princess (P) and imprisoned her in the bottom-right
corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid.
Our valiant knight (K) was initially positioned in the top-left room and must
fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at
any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative
integers) upon entering these rooms; other rooms are either empty (0's) or
contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to
move only rightward or downward in each step.



Write a function to determine the knight's minimum initial health so that he is
able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be
at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

-2 (K)	-3	3
-5	-10	1
10	30	-5 (P)
*/
int dungeon_game(const vector<vector<int>>& v) {
  std::function<int(const vector<vector<int>>&, int, int, vector<vector<int>>&)>
      lambda = [&](const vector<vector<int>>& v, int i, int j,
                   vector<vector<int>>& dp) {
        if (i == v.size() || j == v[0].size()) return INT_MAX;
        if (i == v.size() - 1 && j == v[0].size() - 1) {
          if (v[i][j] < 0)
            return 1 - v[i][j];  //~ abs(v[i][j])+1
          else
            return 1;
        }
        if (dp[i][j] != INT_MAX) return dp[i][j];
        int down_min = lambda(v, i + 1, j, dp);
        int right_min = lambda(v, i, j + 1, dp);
        int min_so_far = min(down_min, right_min);
        int ret;
        if (v[i][j] >= min_so_far)
          return ret = 1;
        else
          ret = (min_so_far - v[i][j]);
        dp[i][j] = ret;
        return ret;
      };
  vector<vector<int>> dp(v.size(), vector<int>(v[0].size(), INT_MAX));
  int row = v.size();
  if (!row) return 1;
  return lambda(v, 0, 0, dp);
}

void test_dengeon_game_174() {
  vector<vector<int>> v = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
  PRINT(dungeon_game(v));
  PRINT(dungeon_game({{0, 0}}));
  PRINT_MSG;
}