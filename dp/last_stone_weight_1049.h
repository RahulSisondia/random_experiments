#include "../my_util.h"
#include "sum_diff.h"
/*
https://leetcode.com/problems/last-stone-weight-ii/
We have a collection of rocks, each rock has a positive integer weight.

Each turn, we choose any two rocks and smash them together.  Suppose the stones
have weights x and y with x <= y.  The result of this smash is:

If x == y, both stones are totally destroyed;
If x != y, the stone of weight x is totally destroyed, and the stone of weight y
has new weight y-x. At the end, there is at most 1 stone left.  Return the
smallest possible weight of this stone (the weight is 0 if there are no stones
left.)



Example 1:

Input: [2,7,4,1,8,1]
Output: 1
Explanation:
We can combine 2 and 4 to get 2 so the array converts to [2,7,1,8,1] then,
we can combine 7 and 8 to get 1 so the array converts to [2,1,1,1] then,
we can combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we can combine 1 and 1 to get 0 so the array converts to [1] then that's the
optimal value.
*/

/*
Initially I thought that it is greedy problem so approached in the similar
fashion but that didn't work. Following are the greedy approaches.
*/

// Following is Geedy strategy which of course doesn't work.
class Solution_greedy_1 {
 public:
  int lastStoneWeightII(vector<int>& stones) {
    priority_queue<int> q;
    for (int s : stones) q.push(s);
    while (q.size() > 1) {
      int x = q.top();
      q.pop();
      int y = q.top();
      q.pop();
      if (x == y) continue;
      q.push(abs(x - y));
    }
    return q.empty() ? 0 : q.top();
  }
};

// Following is Geedy strategy which of course doesn't work.
class Solution_greedy_2 {
 public:
  int lastStoneWeightII(vector<int>& stones) {
    sort(stones.rbegin(), stones.rend());
    int first = stones[0];
    for (int i = 1; i < stones.size(); i++) {
      first = abs(first - stones[i]);
    }
    return first;
  }
};

/*
 Then I wrote the recursive solution.  That works but gives TLE.
 Even after applying the DP. May be I am doing that wrong.
 But think it about it. Isn't it the min_subset diff problem ?

 The main issue here is that, if you go and write down the expression for the
problem like: V = [a, b, c, d, e]

Assuming steps to one solution are:
x = a-b, then y=c-d, then z=x-e, then S=y-z.

That is the same thing as saying:
S= (c-d)-(x-e) = (c-d)-((a-b)-e) = (c+b+e)-(d+a)

When S is the minimun possible value. And you can rearrange any other
combination like this.

Which reduces this problem to finding whichever subset of V with the maximum
somatorium is still smaller than the half of the total.
*/
class Solution_rec {
 public:
  void solve(const vector<int>& v, vector<bool>& visited, int index,
             int current_min, int& final_min) {
    if (index >= v.size()) {
      final_min = min(current_min, final_min);
      return;
    }

    for (int i = 0; i < v.size(); i++) {
      if (visited[i]) continue;
      current_min = abs(current_min - v[i]);
      visited[i] = true;
      solve(v, visited, index + 1, current_min, final_min);
      current_min = current_min + v[i];
      visited[i] = false;
    }
  }

  int lastStoneWeightII(vector<int>& stones) {
    int final_min = INT_MAX;
    vector<bool> visited(stones.size(), false);
    solve(stones, visited, 0, 0, final_min);
    return final_min;
  }
};

void test_stone_game_1049() {
  /*
  {2,7,4,1,8,1}
  {1,3,4,3,5,4}
  {2,4,3,8}
  {1,2,3,4}
  */
  Solution_rec s_rec;
  vector<int> v = {2, 7, 4, 1, 8, 1};
  CHECK(s_rec.lastStoneWeightII(v), 1);
  CHECK(min_subset_sum_diff_rec(v), 1);
  v = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 14, 23, 37, 61, 98};
  PRINT(min_subset_sum_diff_rec(v));
  PRINT_MSG;
}
