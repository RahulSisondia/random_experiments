#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

#include "../my_util.h"
using namespace std;

bool is_subset_sum_rec(vector<int> item, int target, int n) {
  if (target == 0) return true;
  if (n < 0 || target < 0) return false;
  if (item[n] <= target) {
    return (is_subset_sum_rec(item, target - item[n], n - 1) ||
            is_subset_sum_rec(item, target, n - 1));
  } else {
    return is_subset_sum_rec(item, target, n - 1);
  }
}

bool is_subset_top_down_util(vector<int> item, int target, int n,
                             vector<vector<int>> matrix) {
  if (target == 0) return true;
  if (n < 0 || target < 0) return false;

  // If the result is already cached then use that.
  if (matrix[n][target] != -1) {
    return matrix[n][target];
  }
  if (item[n] <= target) {
    matrix[n][target] = ((is_subset_sum_rec(item, target - item[n], n - 1) ||
                          is_subset_sum_rec(item, target, n - 1)));
  } else {
    matrix[n][target] = is_subset_sum_rec(item, target, n - 1);
  }
  return matrix[n][target];
}

/*
 - Problem is like 01 knapsack but it has to return only bool.
   the only way to store the result in int 2D matrix.
*/
bool is_subset_top_down(vector<int> item, int target, int n) {
  vector<vector<int>> matrix(n + 1, vector<int>(target + 1, -1));
  return is_subset_top_down_util(item, target, n, matrix);
}

/*
  - Tabulation version :
    - Only thing to pay attention to, is the initilization of
      base conditions.
*/
bool is_subset_bottom_up(vector<int> item, int target, int n) {
  if (target < 0) return false;
  vector<vector<bool>> matrix(n + 1, vector<bool>(target + 1, false));
  // Empty set is possible if there is 0 target.
  matrix[0][0] = true;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= target; j++) {
      if (j == 0)
        matrix[i][j] = true;  // Empty set is possible if there is 0 target.
      else if (item[i - 1] <= j)
        matrix[i][j] = matrix[i - 1][j] || matrix[i - 1][j - item[i - 1]];
      else
        matrix[i][j] = matrix[i - 1][j];
    }
  }
  return matrix.back().back();
}

void is_subset_sum() {
  std::vector<int> item = {2, 3, 7, 8, 10};
  sort(item.begin(), item.end());
  int n = item.size() - 1;
  assert(is_subset_sum_rec(item, 11, n) == true);
  assert(is_subset_sum_rec(item, 6, n) == false);
  assert(is_subset_sum_rec(item, 0, n) == true);
  assert(is_subset_sum_rec(item, 10, n) == true);
  assert(is_subset_sum_rec(item, 20, n) == true);
  assert(is_subset_top_down(item, 11, n) == true);
  assert(is_subset_top_down(item, 6, n) == false);
  assert(is_subset_top_down(item, 0, n) == true);
  assert(is_subset_top_down(item, 10, n) == true);
  assert(is_subset_top_down(item, 20, n) == true);
  assert(is_subset_bottom_up(item, 11, n + 1) == true);
  assert(is_subset_bottom_up(item, 6, n + 1) == false);
  assert(is_subset_bottom_up(item, 0, n + 1) == true);
  assert(is_subset_bottom_up(item, 10, n + 1) == true);
  assert(is_subset_bottom_up(item, 20, n + 1) == true);
  assert(is_subset_bottom_up(item, -6, n + 1) == false);

  cout << "All subset sum tests passed" << endl;
}

// >8------------------------------------------------------->8

/*
  Differences are :
   - base conditions changed.
   - We add the results of sub problems.
 */
int count_subset_sum_rec(vector<int> item, int target, int n) {
  if (target == 0)
    return 1;  // There could nullsubset as well.
  else if (n < 0 || target < 0)
    return 0;
  else if (item[n] <= target) {
    return (count_subset_sum_rec(item, target - item[n], n - 1) +
            count_subset_sum_rec(item, target, n - 1));
  } else {
    return count_subset_sum_rec(item, target, n - 1);
  }
}

/*
  Differences are :
   - base conditions changed.
   - We add the results of sub problems.
 */
int count_subset_sum_top_down_util(vector<int> item, int target, int n,
                                   vector<vector<int>> dp) {
  if (target == 0)
    return 1;
  else if (n < 0 || target < 0)
    return 0;
  else if (dp[n][target] != -1)
    return dp[n][target];

  if (item[n] <= target) {
    dp[n][target] = (count_subset_sum_rec(item, target - item[n], n - 1) +
                     count_subset_sum_rec(item, target, n - 1));
  } else {
    dp[n][target] = count_subset_sum_rec(item, target, n - 1);
  }
  return dp[n][target];
}

int count_subset_sum_top_down(vector<int> item, int target, int n) {
  vector<vector<int>> matrix(n + 1, vector<int>(target + 1, -1));
  return count_subset_sum_top_down_util(item, target, n, matrix);
}
/*
  - Tabulation version :
    - Only thing to pay attention to, is the initilization of
      base conditions.
*/
int count_subset_bottom_up(vector<int> item, int target, int n) {
  if (target < 0) return 0;
  vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
  // Empty set is possible if there is 0 target.
  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= target; j++) {
      if (j == 0)
        dp[i][j] = 1;  // Empty set is possible if target is 0.
      else if (item[i - 1] <= j)
        dp[i][j] = dp[i - 1][j] /* Exclude */ +
                   dp[i - 1][j - item[i - 1]] /* Include */;
      else
        dp[i][j] = dp[i - 1][j];
    }
  }
  return dp.back().back();
}

void count_subset_sum() {
  std::vector<int> item = {2, 3, 5, 6, 8, 10};
  sort(item.begin(), item.end());
  int n = item.size() - 1;
  CHECK(count_subset_sum_rec(item, 35, n), 0);
  CHECK(count_subset_sum_rec(item, 6, n), 1);
  CHECK(count_subset_sum_rec(item, 34, n), 1);
  CHECK(count_subset_sum_rec(item, 5, n), 2);
  CHECK(count_subset_sum_rec(item, 10, n), 3);
  CHECK(count_subset_sum_top_down(item, 35, n), 0);
  CHECK(count_subset_sum_top_down(item, 6, n), 1);
  CHECK(count_subset_sum_top_down(item, 34, n), 1);
  CHECK(count_subset_sum_top_down(item, 5, n), 2);
  CHECK(count_subset_sum_top_down(item, 10, n), 3);
  CHECK(count_subset_bottom_up(item, 35, n), 0);
  CHECK(count_subset_bottom_up(item, 6, n), 1);
  CHECK(count_subset_bottom_up(item, 34, n + 1), 1);
  CHECK(count_subset_bottom_up(item, 5, n + 1), 2);
  CHECK(count_subset_bottom_up(item, 10, n + 1), 3);
  cout << "All Count subset sum tests passed" << endl;
}