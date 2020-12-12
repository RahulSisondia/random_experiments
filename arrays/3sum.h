#include "../my_util.h"

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result{};
    if (nums.size() < 3) return result;

    // Sort the array
    sort(nums.begin(), nums.end());
    size_t len = nums.size();
    int indexB, indexC;
    for (int indexA = 0; indexA < len - 2; indexA++) {
      // Optimization. Since it is sorted array, therefore positive intergers
      // cannot contribute to make the sum 0.
      if (nums[indexA] > 0) return result;

      // Ignore the repeating elements to avoid duplicate entry in the result
      // set.
      if (indexA > 0 && nums[indexA] == nums[indexA - 1]) continue;

      indexB = indexA + 1;
      indexC = int(len - 1);
      while (indexB < indexC) {
        int a = nums[indexA];
        int b = nums[indexB];
        int c = nums[indexC];

        if ((a + b + c) == 0) {
          result.push_back({a, b, c});
          indexB++;
          while (indexB < indexC && nums[indexB] == b) indexB++;
          indexC--;
          while (indexB < indexC && nums[indexC] == c) indexC--;
        } else if ((a + b + c) > 0) {
          indexC--;
        } else {
          indexB++;
        }
      }
    }

    return result;
  }
};

void test_three_sum() {
  Solution s;
  vector<int> nums{0, -2, -2, 0, 2, 4, 2};
  auto result = s.threeSum(nums);
  CHECK(result, {{-2, -2, 4}, {-2, 0, 2}});
  PRINT_MSG;
}
