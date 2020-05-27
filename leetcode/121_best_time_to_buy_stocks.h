#pragma once
/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
Say you have an array for which the ith element is the price of a given stock on
day i.

If you were only permitted to complete at most one transaction (i.e., buy one
and sell one share of the stock), design an algorithm to find the maximum
profit.

Note that you cannot sell a stock before you buy one.

Example 1:

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit =
6-1 = 5. Not 7-1 = 6, as selling price needs to be larger than buying price.
Example 2:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/

#include <iostream>
#include <limits>
#include <vector>

class Solution {
 public:
  int maxProfit(std::vector<int>& prices) {
    int max_profit_so_far = 0;
    int min_value = std::numeric_limits<int>::max();
    for (int i = 0; i < prices.size(); ++i) {
      int diff = prices[i] - min_value;
      max_profit_so_far = std::max(diff, max_profit_so_far);
      min_value = std::min(min_value, prices[i]);
    }
    return max_profit_so_far;
  }
};

void test_121() {
  Solution s;
  std::vector<int> prices = {7, 1, 5, 3, 6, 4};
  int ret = s.maxProfit(prices);
  if (ret != 5) std::cout << "Expected 5, Returned " << ret << std::endl;
  prices = {7, 2, 5, 6, 1, 3, 7};
  ret = s.maxProfit(prices);
  if (ret != 6) std::cout << "Expected 6, Returned " << ret << std::endl;
  prices = {};
  ret = s.maxProfit(prices);
  if (ret != 0) std::cout << "Expected 0, Returned " << ret << std::endl;
  prices = {7, 6, 5, 1};
  ret = s.maxProfit(prices);
  if (ret != 0) std::cout << "Expected 0, Returned " << ret << std::endl;
}
