#pragma once
#include "../my_util.h"

/**
 * https://www.youtube.com/watch?v=-GtpxG6l_Mc&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go&index=10
 * https://www.geeksforgeeks.org/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum/
 */
int min_subset_sum_diff_rec_util(vector<int> item, int sum_total,
                                 int sum_current, int n) {
  if (n == 0) {
    // If we have reached last element.  Sum of one
    // subset is sumCalculated, sum of other subset is
    // sumTotal-sumCalculated.  Return absolute difference
    // of two sums.
    return abs((sum_total - sum_current) - sum_current);
  }
  // For every item arr[i], we have two choices
  // (1) We do not include it first set
  // (2) We include it in first set
  // We return minimum of two choices
  return min(min_subset_sum_diff_rec_util(item, sum_total,
                                          item[n - 1] + sum_current, n - 1),
             min_subset_sum_diff_rec_util(item, sum_total, sum_current, n - 1));
}

int min_subset_sum_diff_rec(vector<int> item) {
  int sum_total = accumulate(item.begin(), item.end(), 0);
  return min_subset_sum_diff_rec_util(item, sum_total, 0, item.size() - 1);
}

void min_subset_sum_diff() {
  std::vector<int> item = {3, 1, 4, 2, 2, 1};
  assert(min_subset_sum_diff_rec(item) == 1);
  cout << "All min subset diff tests passed\n";
}

int target_subset_sum_rec_util(vector<int> item, int target, int sum_total,
                               int sum_current, int n) {
  if (n == 0) {
    // If we have reached last element.  Sum of one
    // subset is sumCalculated, sum of other subset is
    // sumTotal-sumCalculated.
    // If the absolute difference if equal to the target then return 1,
    //  otherwise 0
    if (abs((sum_total - sum_current) - sum_current) == target)
      return 1;
    else
      return 0;
  }
  if (n < 0) return 0;
  // For every item arr[i], we have two choices
  // (1) We do not include it first set
  // (2) We include it in first set
  // We return the sum of the result return by each subset.
  //
  return (
      target_subset_sum_rec_util(item, target, sum_total,
                                 item[n - 1] + sum_current, n - 1) +
      target_subset_sum_rec_util(item, target, sum_total, sum_current, n - 1));
}

int target_subset_sum_rec(vector<int> item, int target) {
  int sum_total = accumulate(item.begin(), item.end(), 0);
  return target_subset_sum_rec_util(item, target, sum_total, 0,
                                    item.size() - 1);
}

void target_subset_sum() {
  std::vector<int> item = {3, 1, 3, 5};
  int target = 6;
  assert(target_subset_sum_rec(item, target) == 2);
  assert(target_subset_sum_rec({1, 1, 1, 1, 1}, 3) == 5);
  cout << "All Target sum tests passed\n";
}