#include "../my_util.h"

// Sort the input array, the array is assumed
// to have values in {0, 1, 2}
void sort012(vector<int>& a) {
  int lo = 0;
  int hi = a.size() - 1;
  int mid = 0;

  while (mid <= hi) {
    switch (a[mid]) {
      case 0:
        std::swap(a[lo++], a[mid++]);
        break;
      case 1:
        mid++;
        break;
      case 2:
        std::swap(a[mid], a[hi--]);
        break;
    }
  }
}

// Driver Code
void test_dutch_national_flag() {
  std::vector<int> v = {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1};
  sort012(v);
  CHECK(v, {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2});
  PRINT_MSG;
}
