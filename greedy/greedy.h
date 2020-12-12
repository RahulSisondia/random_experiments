#include "../my_util.h"

/*
values, weights
arr[] = {{60, 10}, {100, 20}, {120, 30}}
6, 5, 4
Knapsack Capacity, W = 50;



*/
double fractional_knapsack(const vector<int>& values,
                           const vector<int>& weights, int W) {
  struct Item {
    int value = 0;
    int weight = 0;
  };
  vector<Item> items(values.size());
  double result = 0;
  for (int i = 0; i < values.size(); i++) {
    // Don't call push_back. since we already have reserved the memory.
    items[i] = {values[i], weights[i]};
  }
  sort(items.begin(), items.end(), [](const Item& I1, const Item& I2) {
    double IPW1 = (double)I1.value / (double)I1.weight;
    double IPW2 = (double)I2.value / (double)I2.weight;
    // Sort in decreasing Order
    return IPW1 > IPW2;
  });
  int current_weight = 0;
  for (auto item : items) {
    if ((current_weight + item.weight) <= W) {
      current_weight += item.weight;
      result += item.value;
    } else {
      int remaining_weight = (W - current_weight);
      result += remaining_weight * ((double)item.value / (double)item.weight);
      break;
    }
  }
  return result;
}

void test_fractional_knapsack() {
  PRINT(fractional_knapsack({60, 100, 120}, {10, 20, 30}, 50));
  PRINT_MSG;
}
