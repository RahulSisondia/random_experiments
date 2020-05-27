#pragma once
/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
Say you have an array for which the ith element is the price of a given stock on
day i.

Design an algorithm to find the maximum profit. You may complete at most two
transactions.

Note: You may not engage in multiple transactions at the same time (i.e., you
must sell the stock before you buy again).

Example 1:

Input: [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit =
3-0 = 3. Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit =
4-1 = 3. Example 2:

Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit =
5-1 = 4. Note that you cannot buy on day 1, buy on day 2 and sell them later, as
you are engaging multiple transactions at the same time. You must sell before
buying again. Example 3:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/
#include <iostream>
#include <limits>
#include <vector>

class Solution {
 public:
  /*
   Compute during forward and backward iterations.
   Forward iteration will keep track of first txn and backward
   iteration will keep track of second txn.
   While doing the backward iteration keep track of final value rather
   running a loop again.
  */
  int maxProfit(std::vector<int>& prices) {
    std::vector<int> l2r(prices.size(), 0);
    int min_value = std::numeric_limits<int>::max();
    int total_profit = 0;
    for (int i = 0; i < prices.size(); i++) {
      min_value = std::min(min_value, prices[i]);
      int diff = prices[i] - min_value;
      total_profit = std::max(total_profit, diff);
      l2r[i] = total_profit;
    }
    int max_value = std::numeric_limits<int>::min();
    for (int i = int(prices.size() - 1); i > 0; i--) {
      max_value = std::max(max_value, prices[i]);
      int diff = max_value - prices[i];
      total_profit = std::max(total_profit, l2r[i - 1] + diff);
    }
    return total_profit;
  }
};

/*
3, 3, 5, 0, 0, 3, 1, 4

         V
0, 0, 2, 2, 2, 3, 3, 4
4, 4, 4, 4, 4, 3, 3, 0
            ^
------------------------
*/

void test_123() {
  Solution s;
  std::vector<int> prices = {7, 1, 5, 3, 6, 4};
  int ret = s.maxProfit(prices);
  if (ret != 7) std::cout << "Expected 7, Returned " << ret << std::endl;
  prices = {7, 2, 5, 6, 1, 3, 7};
  ret = s.maxProfit(prices);
  if (ret != 10) std::cout << "Expected 10, Returned " << ret << std::endl;
  prices.clear();
  ret = s.maxProfit(prices);
  if (ret != 0) std::cout << "Expected 0, Returned " << ret << std::endl;
  prices = {7, 6, 5, 1};
  ret = s.maxProfit(prices);
  if (ret != 0) std::cout << "Expected 0, Returned " << ret << std::endl;
  prices = {3, 3, 5, 0, 0, 3, 1, 4};
  ret = s.maxProfit(prices);
  if (ret != 8) std::cout << "Expected 8, Returned " << ret << std::endl;
}
