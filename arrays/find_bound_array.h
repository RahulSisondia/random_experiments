#include "../my_util.h"

enum class Bound { LOWER, UPPPER };
int find_bound(vector<int> a, int si, int key, Bound bound) {
  int ei = a.size() - 1;
  int ans = -1;

  while (si <= ei) {
    int mid = (si + ei) / 2;

    if (a[mid] == key) {
      ans = mid;
      if (bound == Bound::LOWER)
        ei = mid - 1;
      else
        si = mid + 1;
    } else if (a[mid] > key) {
      ei = mid - 1;
    } else {
      si = mid + 1;
    }
  }

  return ans;
}

int count(vector<int> vect, int key) {
  int lb_index = find_bound(vect, 0, key, Bound::LOWER);
  int cnt = -1;
  if (lb_index != -1) {
    int ub_index = find_bound(vect, lb_index, key, Bound::UPPPER);
    if (lb_index == ub_index)
      cnt = 1;
    else
      cnt = ub_index - lb_index + 1;
  }
  return cnt;
}

void test_find_bound() {
  vector<int> vect = {1, 2, 2, 2, 2, 2, 3, 3, 3, 5, 5, 5};
  CHECK(count(vect, 1), 1);
  CHECK(count(vect, 2), 5);
  CHECK(count(vect, 3), 3);
  CHECK(count(vect, 10), -1);
  PRINT_MSG;
}
