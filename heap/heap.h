#include "../my_util.h"

/*
Given an array of n elements, where each element is at most k away from its
target position, devise an algorithm that sorts in O(n log k) time. For example,
let us consider k is 2, an element at index 7 in the sorted array, can be at
indexes 5, 6, 7, 8, 9 in the given array.

Example:
Input : arr[] = {6, 5, 3, 2, 8, 10, 9}
k = 3
Output : arr[] = {2, 3, 5, 6, 8, 9, 10}
*/
vector<int> sort_nearly_sorted(vector<int> v, int k) {
  priority_queue<int, vector<int>, std::greater<>> minheap;
  vector<int> result;
  for (auto num : v) {
    minheap.push(num);
    if (minheap.size() > k + 1) {
      result.push_back(minheap.top());
      minheap.pop();
    }
  }
  while (!minheap.empty()) {
    result.push_back(minheap.top());
    minheap.pop();
  }
  return result;
}

void test_sort_nearly_sorted() {
  CHECK(sort_nearly_sorted({6, 5, 3, 2, 8, 10, 9}, 3), {2, 3, 5, 6, 8, 9, 10});
  PRINT_MSG;
}

/*
Given an unsorted array and two numbers x and k, find k closest values to x.
Input : arr[] = {10, 2, 14, 4, 7, 6}, x = 5, k = 3
*/
vector<int> find_closest_elements(const vector<int>& arr, int k, int x) {
  using pr = pair<int, int>;
  priority_queue<pr, vector<pr>, std::less<>> pq;  // max heap
  for (auto num : arr) {
    pair<int, int> p = {abs(x - num), num};
    pq.push(p);
    if (pq.size() > k) {
      pq.pop();
    }
  }
  vector<int> result;
  while (!pq.empty()) {
    result.push_back(pq.top().second);
    pq.pop();
  }
  sort(result.begin(), result.end());
  return result;
}

void test_k_closet_element() {
  vector<int> v = {1, 2, 3, 4, 5};
  CHECK(find_closest_elements(v, 4, 3), {1, 2, 3, 4});
  vector<int> v1 = {10, 2, 14, 4, 7, 6};
  CHECK(find_closest_elements(v1, 3, 5), {4, 6, 7});
  PRINT_MSG;
}