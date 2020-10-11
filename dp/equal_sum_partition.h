#pragma once
#include <algorithm>
#include <numeric>
#include <vector>

#include "subset_sum.h"

// This problem is just manifestation of the subset sum problem in different
// form.
bool is_equal_subset_rec(std::vector<int> item) {
  int sum = std::accumulate(item.begin(), item.end(), 0);
  if (sum % 2 != 0) return false;
  return is_subset_sum_rec(item, sum / 2, item.size() - 1);
}
void is_equal_subset() {
  std::vector<int> item = {1, 5, 11, 5};
  assert(is_equal_subset_rec(item) == true);
  cout << "Equal sum partision tests passed" << endl;
}
