#include "01_knaspsack.h"
#include "equal_sum_partition.h"
#include "subset_sum.h"
#include "sum_diff.h"
#include "unbounded_knapsack.h"

int main() {
  zero_one_knapsack();
  is_subset_sum();
  is_equal_subset();
  count_subset_sum();
  min_subset_sum_diff();
  target_subset_sum();
  unbounded_knapsack();
  count_coin_change();
  min_coin_change_required();
  return 0;
}