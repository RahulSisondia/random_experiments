#include "../my_util.h"
// https://leetcode.com/problems/find-peak-element/
// https://youtu.be/OINnBJTRrMU
int peak_element(vector<int> v) {
  int low = 0;
  int high = v.size() - 1;
  /*
    Notice the condition check it is <= because of we have high is the valid
    index.
  */
  while (low <= high) {
    int mid = low + (high - low) / 2;
    /*
      First check for the peak element where two neigbhors exist.
      In case we found where the middle element is greater than its neighbors
      then return that element. Otherwise, chances to find the peak element are
      in the side whervever the neighbor is greater than the middle element.
    */
    if (mid > 0 && mid < v.size() - 1) {
      if (v[mid] > v[mid - 1] && v[mid] > v[mid + 1]) {
        return v[mid];
      } else if (v[mid - 1] > v[mid]) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    } /*
      There is no left neighbor or there is only one element in the array.
      If the element is greater than return that.
     */
    else if (mid == 0) {
      if (v.size() == 1)
        return v.back();
      else if (v[mid] > v[mid + 1]) {
        return v[mid];
      } else {
        return v[mid + 1];
      }
    } /*
       There is no right neighbor. If the element is greater than return that.
      */
    else if (mid == v.size() - 1) {
      if (v[mid] > v[mid - 1]) {
        return v[mid];
      } else {
        return v[mid - 1];
      }
    }
  }
  return -1;
}

/*
 Brute force solution in O(n).  It return the element index though.
*/
int findPeakElement(vector<int> nums) {
  for (int i = 0; i < nums.size() - 1; i++) {
    if (nums[i] > nums[i + 1]) return i;
  }
  return nums.size() - 1;
}

/*
Recursive solution is so easy to implement:

If the middle element, midmid lies in an ascending sequence of numbers, or a
rising slope(found by comparing nums[i]nums[i] to its right neighbour), it
obviously implies that the peak lies towards the right of this element. Thus, we
reduce the search space to the right of midmid and perform the same process on
the right subarray.

In this way, we keep on reducing the search space till we eventually reach a
state where only one element is remaining in the search space. This single
element is the peak element.
*/
class Solution_162 {
 public:
  int findPeakElement(vector<int> nums) {
    return search(nums, 0, nums.size() - 1);
  }
  int search(vector<int>& nums, int l, int r) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (nums[mid] > nums[mid + 1]) return search(nums, l, mid);
    return search(nums, mid + 1, r);
  }
};

void test_peak_element() {
  CHECK(peak_element({1, 5, 8, 10, 12, 18, 15}), 18);
  CHECK(peak_element({1, 8, 5, 2, 1, 11, 15}), 8);
  CHECK(peak_element({9, 8, 5}), 9);
  CHECK(peak_element({1, 2, 3, 4, 5}), 5);
  CHECK(peak_element({1, 1, 1}), 1);
  CHECK(peak_element({1}), 1);
  CHECK(peak_element({1, 2}), 2);
  PRINT_MSG;
}