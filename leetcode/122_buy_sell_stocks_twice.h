#pragma once
/*
“Say you have an array for which the ith element is the price of a given stock
on day i. Design an algorithm to find the maximum profit. You may complete as
many transactions as you like (ie, buy one and sell one share of the stock
multiple times). However, you may not engage in multiple transactions at the
same time (ie, you must sell the stock before you buy again).”
*/

#include <iostream>
#include <limits>
#include <vector>

class Solution_122 {
 public:
  int maxProfit(std::vector<int>& prices) {
    int max_profit = 0;
    for (int i = 1; i < prices.size(); ++i) {
      int diff = prices[i] - prices[i - 1];
      if (diff > 0) max_profit += diff;
    }
    return max_profit;
  }
};

void test_122() {
  Solution_122 s;

  std::vector<int> prices = {7, 1, 5, 3, 6, 4};
  int ret = s.maxProfit(prices);
  if (ret != 7) std::cout << "Expected 7, Returned " << ret << std::endl;

  prices = {7, 2, 5, 6, 1, 3, 7};
  ret = s.maxProfit(prices);
  if (ret != 10) std::cout << "Expected 10, Returned " << ret << std::endl;

  prices = {};
  ret = s.maxProfit(prices);
  if (ret != 0) std::cout << "Expected 0, Returned " << ret << std::endl;

  prices = {7, 6, 5, 1};
  ret = s.maxProfit(prices);
  if (ret != 0) std::cout << "Expected 0, Returned " << ret << std::endl;

  prices = {3, 3, 5, 0, 0, 3, 1, 4};
  ret = s.maxProfit(prices);
  if (ret != 8) std::cout << "Expected 8, Returned " << ret << std::endl;
  std::cout << "test_122 passed" << std::endl;
}
