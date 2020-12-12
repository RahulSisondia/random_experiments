#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Combinations {
 public:
  void combineHelper(vector<int> &current, int n, int k,
                     vector<vector<int>> &ans) {
    if (k == 0) {
      vector<int> newEntry = current;
      reverse(newEntry.begin(), newEntry.end());
      ans.push_back(newEntry);
      return;
    }
    if (n == 0 || n < k) return;
    // We have 2 options here. We can either include n or not.
    // Option 1 : Do not include n.
    combineHelper(current, n - 1, k, ans);
    // Option 2 : Include n.
    current.push_back(n);
    combineHelper(current, n - 1, k - 1, ans);
    current.pop_back();
    return;
  }

  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> ans;
    vector<int> current;
    combineHelper(current, n, k, ans);
    sort(ans.begin(), ans.end());
    return ans;
  }
};

class Combinations_cp {
 public:
  void combine_util(int n, int k, int index, vector<vector<int>> &result,
                    vector<int> &current) {
    if (current.size() == k) {
      result.push_back(current);
      return;
    }
    // Almost same as from the IB solution above. The only difference is that :
    // For ith iteration the number is included and for i+1 th iteration onwards
    // number is exluded.
    for (auto i = index; i <= n; ++i) {
      current.push_back(i);
      // cout << "pushed index : " << i << endl;
      combine_util(n, k, i + 1, result, current);
      current.pop_back();
      // cout << "popped index : " << i << endl;
    }
  }

  vector<vector<int>> combine(int A, int B) {
    vector<vector<int>> result;
    vector<int> current;
    combine_util(A, B, 1, result, current);
    return result;
  }
};

void test_combinations() {
  Combinations c;
  CHECK(c.combine(3, 2), {{1, 2}, {1, 3}, {2, 3}});
  Combinations_cp cp;
  CHECK(cp.combine(3, 2), {{1, 2}, {1, 3}, {2, 3}});
  PRINT_MSG;
}