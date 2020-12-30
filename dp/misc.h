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
  CHECK(dungeon_game(v), 7);
  CHECK(dungeon_game({{0, 0}}), 1);
  PRINT_MSG;
}

/*
Deletion Distance
The deletion distance of two strings is the minimum number of characters you
need to delete in the two strings in order to get the same string. For instance,
the deletion distance between "heat" and "hit" is 3:

By deleting 'e' and 'a' in "heat", and 'i' in "hit", we get the string "ht" in
both cases. We cannot get the same string from both strings by deleting 2
letters or fewer. Given the strings str1 and str2, write an efficient function
deletionDistance that returns the deletion distance between them. Explain how
your function works, and analyze its time and space complexities.

Examples:

input:  str1 = "dog", str2 = "frog"
output: 3

input:  str1 = "some", str2 = "some"
output: 0

input:  str1 = "some", str2 = "thing"
output: 9

input:  str1 = "", str2 = ""
output: 0
*/

/*
clang-format off
- How much is the complexity? Lets try to draw recursion tree.
                              dog, frog   ------------------------------------>  2^0 
              1 og,frog                            1 dog,rog ----------------->  2^1
     2 g,frog           2 og,rog          2 og,rog           2 dog, og ------->  2^2
3, "",frog  3 g,rog  3 g, rog  3 og,og  3 g,rog 3 og,og   3,og,og    3 dog, og -> 2^3

It shows that complexity will be of of 2^n. 
- What will the complexity after adding the memoization? 
After the memoization the complexity will be number of unique subproblems + calling cost of cached subproblems. 
The latter will be constant of course. 
Question boils down to how many unique subproblems are there ?  
If we look at above recursion tree can observe that unique subproblems will be number of substrings. 
In this case they are m*n. Since there is no loop in the recursion code therefore the complexity will be 
O(m*n*C)
C is the cost of cached subproblems calls cost. 

clang-format on
*/
int deletionDistance(const string& str1, const string& str2, int i, int j,
                     unordered_map<string, int>& memo) {
  string key = to_string(i) + "|" + to_string(j);

  if (memo.count(key)) return memo[key];

  if (i == str1.size() || j == str2.size()) {
    if (i == str1.size() && j == str2.size()) {
      memo[key] = 0;
      return memo[key];
    }
    memo[key] = max(str1.size() - i, str2.size() - j);
    return memo[key];
  }

  int count;
  if (str1[i] != str2[j]) {
    count = 1 + min(deletionDistance(str1, str2, i + 1, j, memo),
                    deletionDistance(str1, str2, i, j + 1, memo));
  } else {
    count = deletionDistance(str1, str2, i + 1, j + 1, memo);
  }

  memo[key] = count;
  return memo[key];
}

int deletionDistance(const string& str1, const string& str2) {
  unordered_map<string, int> memo;
  return deletionDistance(str1, str2, 0, 0, memo);
}

void test_deletion_distance_pramp() {
  CHECK(deletionDistance("dog", "frog"), 3);
  PRINT_MSG;
}
/*
55. Jump Game
Given an array of non-negative integers nums, you are initially positioned at
the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.
*/
/*
 Recursive logic is correct but for some reason memoization doesn't hit.
 TODO: investigate later on.
*/
class Solution_55 {
 public:
  bool canJump(const vector<int>& nums) {
    int len = nums.size();
    if (len == 0) return false;
    vector<bool> dp(len, false);
    return can_jump(nums, 0, dp);
  }

 private:
  // 0,1
  bool can_jump(const vector<int>& nums, int i, vector<bool>& dp) {
    if (i >= nums.size() - 1) {
      dp[i] = i;
      return true;
    }

    if (dp[i]) {
      PRINT("dp[i] ", dp[i]);
      return true;
    }

    for (int j = 1; j <= nums[i]; j++) {
      if (can_jump(nums, i + j, dp)) {
        dp[i] = true;
        return true;
      }
    }
    return false;
  }
};

/*
Based on greedy approach
Idea is that we keep track of max reachable distance so far.
The moment we reach to the target then we are done.
If we increase the value of i but could sofar reach jump that is less than i
then we cannot continue.
*/
class Solution_33_greedy {
 public:
  bool canJump(const vector<int>& nums) {
    int reached_so_far = 0;
    int target = nums.size() - 1;
    for (int i = 0; i < nums.size(); i++) {
      if (reached_so_far >= target) return true;
      if (reached_so_far < i) return false;
      reached_so_far = max(reached_so_far, nums[i] + i);
    }
    return false;
  }
};

void test_can_jump() {
  Solution_55 s;
  Solution_33_greedy sg;
  CHECK(s.canJump({2, 3, 1, 4, 4, 2, 3, 4, 3, 2}), true);
  CHECK(sg.canJump({2, 3, 1, 4, 4, 2, 3, 4, 3, 2}), true);
  CHECK(s.canJump({0}), true);
  CHECK(s.canJump({0, 1}), false);
  CHECK(s.canJump({2, 0, 0}), true);
  CHECK(s.canJump({0, 0, 2}), false);

  PRINT_MSG;
}