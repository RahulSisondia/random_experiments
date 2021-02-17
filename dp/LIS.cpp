#include <limits.h>

#include "../my_util.h"
using namespace std;

/*
  https://courses.engr.illinois.edu/cs473/sp2011/Lectures/08_handout.pdf
  https://www.techiedelight.com/longest-increasing-subsequence-using-dynamic-programming/
*/
int lis_rec(vector<int> v, int i, int prev) {
  // Base case: nothing is remaining
  if (i == v.size()) return 0;

  // case 1: exclude the current element and process the
  // remaining elements
  int excl = lis_rec(v, i + 1, prev);

  // case 2: include the current element if it is greater
  // than previous element in LIS
  int incl = 0;
  if (v[i] > prev) incl = 1 + lis_rec(v, i + 1, v[i]);

  // return maximum of above two choices
  return max(incl, excl);
}

int lis_top_down_util(vector<int> v, int i, int prev,
                      map<pair<int, int>, int>& dp) {
  // Base case: nothing is remaining
  if (i == v.size()) return 0;

  if (dp.find({i, prev}) != dp.end()) return dp[{i, prev}];
  // case 1: exclude the current element and process the
  // remaining elements
  int excl = lis_top_down_util(v, i + 1, prev, dp);

  // case 2: include the current element if it is greater
  // than previous element in LIS
  int incl = 0;
  if (v[i] > prev) incl = 1 + lis_top_down_util(v, i + 1, v[i], dp);

  // return maximum of above two choices
  int result = max(incl, excl);
  pair<int, int> p = {i, prev};
  dp.emplace(p, result);
  return result;
}
/*
- I misunderstood thinking that only one variable is changing but there are two
  variables getting changed i.e. index and prev . Therefore, we need 2D matrix.
- But, we can't use 2D. It leads to complicated code and out of bound issues.
  therefore, we choose a map that has key as pair (index, prev).
- Using bottom up approach it is possible to solve this problem in 1D array but
  it is difficult to do so in memoization. Seems it is not possible to do this
  with 1D array .
  https://stackoverflow.com/questions/42350612/1d-memoization-in-recursive-solution-of-longest-increasing-subsequence
*/
int lis_top_down(vector<int> v, int i, int prev) {
  map<pair<int, int>, int> dp;
  return lis_top_down_util(v, 0, prev, dp);
}

// main function
int main() {
  CHECK(lis_rec({10, 22, 9, 33}, 0, INT_MIN), 3);
  CHECK(lis_rec({0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15}, 0,
                INT_MIN),
        6);
  CHECK(lis_top_down({0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15}, 0,
                     INT_MIN),
        6);
  CHECK(lis_top_down({10, 22, 9, 33}, 0, INT_MIN), 3);
  PRINT_MSG;
  return 0;
}