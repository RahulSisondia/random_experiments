#pragma once
#include "../my_util.h"

using namespace std;

int knapsack_rec(vector<int> value, vector<int> weight, int W, int n) {
  if (n == 0 || W == 0) return 0;

  if (weight[n] <= W) {
    return std::max(
        value[n] + knapsack_rec(value, weight, W - weight[n], n - 1),
        knapsack_rec(value, weight, W, n - 1));
  } else {
    return knapsack_rec(value, weight, W, n - 1);
  }
}

/*
 We can write the recursion using for loop as well.
 Sets including item are formed when we pass the value i = n. sets for excluding
 items are formed for the values of i > n.
 TODO: Try to write the for loop in incresing order rather decreasing order.
*/
int knapsack_rec_loop(vector<int> value, vector<int> weight, int W, int n) {
  if (n == 0 || W == 0) return 0;

  int max_val = std::numeric_limits<int>::min();
  for (int i = n; i >= 0; i--) {
    if (weight[i] <= W) {
      max_val = max(
          max_val,
          (value[i] + knapsack_rec_loop(value, weight, W - weight[i], i - 1)));
    }
  }
  return max_val;
}

int knapsack_top_down_util(vector<int> &value, vector<int> &weight, int W,
                           int n, vector<vector<int>> &dp) {
  if (n == 0 || W == 0) return 0;

  if (dp[n][W] != -1) return dp[n][W];
  if (weight[n] <= W) {
    dp[n][W] =
        std::max(value[n] + knapsack_rec(value, weight, W - weight[n], n - 1),
                 knapsack_rec(value, weight, W, n - 1));
  } else {
    dp[n][W] = knapsack_rec(value, weight, W, n - 1);
  }
  return dp[n][W];
}

/*
  DP using Memoization:
  - Vector has to be initilized first. Notice the size of vector.
  - There are n rows and W columns initialized with invalid value -1.
  - We just store the temporary results.
 */
int knapsack_top_down(vector<int> value, vector<int> weight, int W, int n) {
  vector<vector<int>> temp(n + 1, std::vector<int>(W + 1, -1));
  return knapsack_top_down_util(value, weight, W, n, temp);
}

/**
 Key learnings :
  - Tranforming the recursive version to tabulation is possible but you need to
    careful on the usage and indices. size of n is the actual size rather index
    of last element.
  - Since matrix has additonal row/column to fullfil the base condition of
    recursion therefore, we size of the matrix is [n+1][W+1] and notice that we
    access the relevant weight from n-1 index.
                        w --->
                   | 0  1  2  3  4  5  6  7  8  9
    pi   wi       -----------------------------------
                0 | 0  0  0  0  0  0  0  0  0  0
    1   1   n   1 | 0  1  1  1  1  1  1  1  1  1
    10  3   |   2 | 0  1  1  10 11 11 11 11 11 11
    3   5   |   3 | 0  1  1  10 11 11 11 11 11 11
    12  6   V   4 | 0  1  1  10 11 11 12 13 13 22
https://youtu.be/8LusJS5-AGo?t=378
*/
int knapsack_bottom_up(vector<int> value, vector<int> weight, int W, int n) {
  vector<vector<int>> matrix(n + 1, std::vector<int>(W + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int w = 1; w <= W; w++) {
      if (weight[i - 1] <= w) {
        matrix[i][w] = std::max((value[i - 1] /* Included the item */ +
                                 /* For the remaining weight we need to look at
                                    previous row to fetch the remaining cost */
                                 matrix[i - 1][w - weight[i - 1]]),
                                /* We don't chose the current element */
                                matrix[i - 1][w]);
      } else {
        matrix[i][w] = matrix[i - 1][w];
      }
    }
  }
  return matrix.back().back();
}

void zero_one_knapsack() {
  std::vector<int> value = {1, 10, 3, 12};
  std::vector<int> weight = {1, 3, 5, 6};
  int capacity = 9;
  int n = value.size();
  CHECK(knapsack_rec(value, weight, capacity, n - 1), 22);
  CHECK(knapsack_rec_loop(value, weight, capacity, n - 1), 22);
  CHECK(knapsack_rec_loop({60, 100, 120}, {{10, 20, 30}}, 50, 3 - 1), 220);
  CHECK(knapsack_top_down(value, weight, capacity, n - 1), 22);
  CHECK(knapsack_bottom_up(value, weight, capacity, n), 22);
  cout << "All 01 knapsack tests passed." << endl;
}