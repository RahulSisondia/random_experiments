#include "../my_util.h"

int unbounded_knapsack_rec(vector<int> value, vector<int> weight, int W,
                           int n) {
  // If number of items are empty or bag has no capacity then we cannot keep any
  // item.
  if (n == 0 || W == 0) return 0;

  if (weight[n] <= W) {
    // If an item is included then it may be included again so keep the length
    // unchanged. Otherwise, change the length.
    return std::max(
        value[n] + unbounded_knapsack_rec(value, weight, W - weight[n], n),
        unbounded_knapsack_rec(value, weight, W, n - 1));
  } else {
    return unbounded_knapsack_rec(value, weight, W, n - 1);
  }
}

int unbounded_knapsack_for_loop(vector<int> value, vector<int> weight, int W,
                                int n) {
  // If number of items are empty or bag has no capacity then we cannot keep any
  // item.
  if (n == 0 || W == 0) return 0;
  int res = numeric_limits<int>::min();
  for (int i = n; i >= 0; --i) {
    if (weight[i] <= W) {
      res = std::max(res, value[i] + unbounded_knapsack_for_loop(
                                         value, weight, W - weight[i], i));
    }
  }
  return res;
}

int unbounded_knapsack_bottom_up(vector<int> value, vector<int> weight, int W,
                                 int n) {
  vector<vector<int>> matrix(n + 1, vector<int>(W + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= W; j++) {
      if (weight[i - 1] <= j) {
        matrix[i][j] = std::max((value[i - 1] + matrix[i][j - weight[i - 1]]),
                                matrix[i - 1][j]);
      } else {
        matrix[i][j] = matrix[i - 1][j];
      }
    }
  }
  return matrix.back().back();
}

void unbounded_knapsack() {
  std::vector<int> value = {1, 10, 3, 12};
  std::vector<int> weight = {1, 3, 5, 6};
  int capacity = 9;
  int n = value.size();
  CHECK(unbounded_knapsack_rec(value, weight, capacity, n - 1), 30);
  CHECK(unbounded_knapsack_for_loop(value, weight, capacity, n - 1), 30);
  CHECK(unbounded_knapsack_bottom_up(value, weight, capacity, n), 30);
  cout << "All unbounded knapsack tests passed." << endl;
}

// 0<-----------Coin Change # of ways-------------------------------------->0

/*
https://www.geeksforgeeks.org/coin-change-dp-7/
- Pay attention to the  bases cases.
*/
int count_coin_change_rec(vector<int> coins, int target, int n) {
  if (target == 0) return 1;
  if (n < 0 || target < 0) return 0;

  if (coins[n] <= target) {
    // If coin is included that it may be included again. i.e. n
    // Otherwise, it will not be included i.e. n-1
    return count_coin_change_rec(coins, target - coins[n], n) +
           count_coin_change_rec(coins, target, n - 1);
  } else {
    return count_coin_change_rec(coins, target, n - 1);
  }
}
/*
 It is cakewalk to convert the the recursive solution to top down DP i.e.
 memoization.

*/
int count_coin_change_top_down_util(vector<int> coins, int target, int n,
                                    vector<vector<int>>& dp) {
  if (target == 0) return 1;
  if (n < 0 || target < 0) return 0;
  int ret;
  if (dp[n][target] != -1) return dp[n][target];
  if (coins[n] <= target) {
    // If coin is included that means it may be included again. i.e. n
    // Otherwise, it will not be included i.e. n-1
    ret = count_coin_change_top_down_util(coins, target - coins[n], n, dp) +
          count_coin_change_top_down_util(coins, target, n - 1, dp);
  } else {
    ret = count_coin_change_top_down_util(coins, target, n - 1, dp);
  }
  dp[n][target] = ret;
  return ret;
}

int count_coin_change_top_down(vector<int> coins, int target, int n) {
  vector<vector<int>> matrix(n + 1, vector<int>(target + 1, -1));
  return count_coin_change_top_down_util(coins, target, n, matrix);
}

void count_coin_change() {
  vector<int> coins{1, 2, 3};
  int n = coins.size() - 1;
  CHECK(count_coin_change_rec(coins, 4, n), 4);
  CHECK(count_coin_change_top_down(coins, 4, n), 4);
  cout << "Coin Change problem tests passed\n";
}

//----------min number of coins changs required ---------------------------

int min_coin_change_required_rec(vector<int> coins, int target, int n) {
  // If target is 0 then we need no coins.
  if (target == 0) return 0;
  if (n < 0 || target < 0) return numeric_limits<int>::max();
  int ret;
  if (coins[n] <= target) {
    // If coin is included that means it may be included again. i.e. n ,
    // and count is increased by 1.
    // Otherwise, it will not be included i.e. n-1
    ret = min(1 + min_coin_change_required_rec(coins, target - coins[n], n),
              min_coin_change_required_rec(coins, target, n - 1));
  } else {
    ret = min_coin_change_required_rec(coins, target, n - 1);
  }
  return ret;
}

int min_coin_change_required_bottom_up(vector<int> coins, int target, int n) {
  // Initialize with max() -1 to avoid overflow later on due to adding +1 .
  vector<vector<int>> matrix(
      n + 1, vector<int>(target + 1, numeric_limits<int>::max() - 1));

  // If target is 0 then min number of coins required are 0
  for (int i = 0; i < n + 1; i++) matrix[i][0] = 0;

  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < target + 1; j++) {
      if (coins[i - 1] <= j) {
        matrix[i][j] =
            std::min((1 + matrix[i][j - coins[i - 1]]), matrix[i - 1][j]);
      } else {
        matrix[i][j] = matrix[i - 1][j];
      }
    }
  }
  return matrix.back().back();
}

void min_coin_change_required() {
  vector<int> coins{1, 2, 3, 5};
  CHECK(min_coin_change_required_rec(coins, 7, coins.size() - 1), 2);
  CHECK(min_coin_change_required_bottom_up(coins, 7, coins.size()), 2);
  PRINT_MSG;
}

/*
 https://www.geeksforgeeks.org/cutting-a-rod-dp-13/
 It is very similar to unbounded knapsack problem.
Once we make the first cut, we may consider
the two pieces as independent instances of the rod-cutting problem. The overall
optimal solution incorporates optimal solutions to the two related subproblems,
maximizing revenue from each of those two pieces. We say that the rod-cutting
problem exhibits optimal substructure: optimal solutions to a problem
incorporate optimal solutions to related subproblems, which we may solve
independently
*/
int cutting_rod(vector<int> price, int length, int cut) {
  if (length <= 0 || cut <= 0) {
    return 0;
  }
  int res;
  if (cut <= length)
    res = max(price[cut - 1] + cutting_rod(price, length - cut, cut),
              cutting_rod(price, length, cut - 1));
  else
    res = cutting_rod(price, length, cut - 1);
  return res;
}

void test_cutting_rod() {
  vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};
  CHECK(cutting_rod(price, price.size(), price.size()), 22);
  price = {1, 5, 8};
  CHECK(cutting_rod(price, price.size(), price.size()), 8);
  PRINT_MSG;
}