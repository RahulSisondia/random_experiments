#pragma once
#include <queue>
#include <vector>
using namespace std;

struct InteratorCurrentEnd {
  bool operator>(InteratorCurrentEnd& that) { return *current > *that.current; }

  vector<int>::const_iterator current;
  vector<int>::const_iterator end;
};

vector<int> MergeSortedArrays(const vector<vector<int>> sorted_arrays) {
  priority_queue<InteratorCurrentEnd, vector<InteratorCurrentEnd>, greater<>>
      min_heap;
  for (const vector<int>& sorted_array : sorted_arrays) {
    if (!sorted_array.empty()) {
      min_heap.emplace(
          InteratorCurrentEnd{sorted_array.cbegin(), sorted_array.cend()});
    }
  }
}
