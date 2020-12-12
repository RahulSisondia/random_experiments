#pragma once
#include "../my_util.h"

class Merge_sort {
 public:
  void merge(vector<int> &vect, vector<int> &v1, vector<int> &v2) {
    int i1 = 0, i2 = 0;
    vect.clear();
    while (i1 < v1.size() && i2 < v2.size()) {
      if (v1[i1] < v2[i2]) {
        vect.push_back(v1[i1]);
        i1++;
      } else {
        vect.push_back(v2[i2]);
        i2++;
      }
    }
    while (i1 < v1.size()) {
      vect.push_back(v1[i1]);
      i1++;
    }
    while (i2 < v2.size()) {
      vect.push_back(v2[i2]);
      i2++;
    }
  }

  void sort(vector<int> &vect) {
    if (vect.size() < 2) return;
    auto middle = vect.size() / 2;
    vector<int> v1{vect.begin(), vect.begin() + middle};
    vector<int> v2{vect.begin() + middle, vect.end()};
    sort(v1);
    sort(v2);
    merge(vect, v1, v2);
  }
};

void test_merge_sort() {
  vector<int> vect{4, 2, 4, 1, 0, 10, 8};
  Merge_sort ms;
  ms.sort(vect);
  CHECK(vect, {0, 1, 2, 4, 4, 8, 10});
  PRINT_MSG;
}

class Count_inversion {
 public:
  void merge(vector<int> &vect, vector<int> &v1, vector<int> &v2,
             int &count_inversion) {
    int i1 = 0, i2 = 0;
    vect.clear();
    while (i1 < v1.size() && i2 < v2.size()) {
      if (v1[i1] < v2[i2]) {
        vect.push_back(v1[i1]);
        i1++;
      } else {
        vect.push_back(v2[i2]);
        i2++;
        // If v1[i1] > v2[i2] that means v2[i2] will form inversion pair for
        // remaining elements in the v1[i1]
        count_inversion += (v1.size() - i1);
      }
    }
    while (i1 < v1.size()) {
      vect.push_back(v1[i1]);
      i1++;
    }
    while (i2 < v2.size()) {
      vect.push_back(v2[i2]);
      i2++;
    }
  }

  void sort(vector<int> &vect, int &count_inversion) {
    if (vect.size() < 2) return;
    auto middle = vect.size() / 2;
    vector<int> v1{vect.begin(), vect.begin() + middle};
    vector<int> v2{vect.begin() + middle, vect.end()};
    sort(v1, count_inversion);
    sort(v2, count_inversion);
    merge(vect, v1, v2, count_inversion);
  }
};

void test_count_inversion() {
  vector<int> vect{8, 4, 2, 1};
  Count_inversion ci;
  int count = 0;
  ci.sort(vect, count);
  CHECK(count, 6);
  PRINT_MSG;
}