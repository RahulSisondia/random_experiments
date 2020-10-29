#include "../my_util.h"

// https://youtu.be/3RhGdmoF_ac
// Just tweaked standard binary search a little bit.
// If low , high crossed each other then the value must be min of their abs diff
// with the key.
int find_min_diff_with_given_key(vector<int> v, int key) {
  int low = 0;
  int high = v.size() - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (v[mid] == key)
      return 0;  // If key is present then abs diff will be 0
    else if (v[mid] < key) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  int diff;
  if (low > v.size() - 1)
    /* Edge case
                  +++ k= 15  +++
         |        |
         V        V
         11      14
              low, high
     */
    diff = abs(v[high] - key);
  else if (high < 0)
    /* Edge case
+++ k= 10  +++
        |        |
        V        V
        11      14
    low, high
    */
    diff = abs(v[low] - key);
  else
    /**
         + k= 12  +
         |        |
         V        V
         11      14
        high     low
    **/
    diff = min(abs(v[low] - key), abs(v[high] - key));
  return diff;
}

void test_find_min_diff_with_given_key() {
  CHECK(find_min_diff_with_given_key({1, 5, 8, 10, 11, 12, 15, 18}, 19), 1);
  CHECK(find_min_diff_with_given_key({1, 5, 8, 10, 11, 12, 15, 18}, 19), 1);
  CHECK(find_min_diff_with_given_key({1, 5, 8, 10, 11, 12, 15, 18}, 17), 1);
  CHECK(find_min_diff_with_given_key({1, 5, 8, 10, 11, 12, 15, 18}, 2), 1);
  CHECK(find_min_diff_with_given_key({2, 5, 8, 10, 11, 12, 15, 18}, 1), 1);

  PRINT_MSG;
}

////// Allocate minimum number of pages//////////////////////////////////////

bool is_valid(vector<int> pages, int k, int limit) {
  int student = 1;
  int sum = 0;
  for (auto pg : pages) {
    sum += pg;
    if (sum > limit) {
      student++;
      sum = pg;
    }
    if (student > k) return false;
  }
  return true;
}

int allocate_pages(vector<int> pages, int s /* students */) {
  int start = *std::max_element(pages.begin(), pages.end());
  int end = std::accumulate(pages.begin(), pages.end(), 0);
  int res = numeric_limits<int>::min();
  while (start < end) {
    int mid = start + (end - start) / 2;
    if (is_valid(pages, s, mid)) {
      /* Since result is valid that means there is scope we could do better.
       * Therefore, go left on the number line. */
      res = mid;
      end = mid - 1;
    } else {
      /*
       It was too tight consraint. We have to increase the range. Therefore, go
       right on the number line.
      */
      start = mid + 1;
    }
  }
  return res;
}

/*
https://www.geeksforgeeks.org/allocate-minimum-number-pages/
https://youtu.be/2JSQIhPcHQg
very insteresting problem :
        Input : pages[] = {12, 34, 67, 90}
        m = 2
Output : 113
Explanation:
There are 2 number of students. Books can be distributed
in following fashion :
  1) [12] and [34, 67, 90]
      Max number of pages is allocated to student
      2 with 34 + 67 + 90 = 191 pages
  2) [12, 34] and [67, 90]
      Max number of pages is allocated to student
      2 with 67 + 90 = 157 pages
  3) [12, 34, 67] and [90]
      Max number of pages is allocated to student
      1 with 12 + 34 + 67 = 113 pages
        Of the 3 cases, Option 3 has the minimum pages = 113.


Approach:
Imagine we are given pages {10, 20, 30, 40} and two students have to read. Total
number of pages to. Read = 100. We have to allocate pages from this total.  That
means on the number line that will be the high value. The low value could be
from any of the book but better to choose from the book that has max pages. In
the image below for illustration purpose the low is taken as 0. We can now
calculate the mid = low + (high -low)/2. We can now apply BS. We have a
constraint that each student cannot read more than  mid pages.  We can
distribute the books and keep track of the distribution.
*/
void test_allocate_pages() {
  CHECK(allocate_pages({12, 34, 67, 90}, 2), 113);
  // Notice it is not sorted array.
  CHECK(allocate_pages({10, 30, 20, 40}, 2), 60);
  CHECK(allocate_pages({10, 30, 20, 40}, 3), 40);

  PRINT_MSG;
}