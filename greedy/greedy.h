#include "../my_util.h"

/*
values, weights
arr[] = {{60, 10}, {100, 20}, {120, 30}}
6, 5, 4
Knapsack Capacity, W = 50;



*/
double fractional_knapsack(const vector<int>& values,
                           const vector<int>& weights, int W) {
  struct Item {
    int value = 0;
    int weight = 0;
  };
  vector<Item> items(values.size());
  double result = 0;
  for (int i = 0; i < values.size(); i++) {
    // Don't call push_back. since we already have reserved the memory.
    items[i] = {values[i], weights[i]};
  }
  sort(items.begin(), items.end(), [](const Item& I1, const Item& I2) {
    double IPW1 = (double)I1.value / (double)I1.weight;
    double IPW2 = (double)I2.value / (double)I2.weight;
    // Sort in decreasing Order
    return IPW1 > IPW2;
  });
  int current_weight = 0;
  for (auto item : items) {
    if ((current_weight + item.weight) <= W) {
      current_weight += item.weight;
      result += item.value;
    } else {
      int remaining_weight = (W - current_weight);
      result += remaining_weight * ((double)item.value / (double)item.weight);
      break;
    }
  }
  return result;
}

void test_fractional_knapsack() {
  PRINT(fractional_knapsack({60, 100, 120}, {10, 20, 30}, 50));
  PRINT_MSG;
}

/* 759. Employee Free Time

We are given a list schedule of employees, which represents the working time
for each employee.

Each employee has a list of non-overlapping Intervals, and these intervals are
in sorted order.

Return the list of finite intervals representing common, positive-length free
time for all employees, also in sorted order.

(Even though we are representing Intervals in the form [x, y], the objects
inside are Intervals, not lists or arrays.
For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and
schedule[0][0][0] is not defined).  Also, we wouldn't include intervals like
[5, 5] in our answer, as they have zero length.

Example 1:

Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation: There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
Example 2:

Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]
*/

// Definition for an Interval.
class Interval {
public:
  int start;
  int end;

  Interval() {}

  Interval(int _start, int _end) {
    start = _start;
    end = _end;
  }

  bool operator==(const Interval &other) const {
    return start == other.start && end == other.end;
  }
};

class Solution_759 {
public:
  vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
    vector<Interval> intervals;
    for (auto temp : schedule) {
      intervals.insert(intervals.end(), temp.begin(), temp.end());
    }

    sort(intervals.begin(), intervals.end(),
         [](const auto &v1, const auto &v2) {
           // Sort the start time in the increasing order .
           return v1.start < v2.start;
         });

    vector<Interval> merged;
    merged.push_back(intervals[0]);

    for (int i = 1; i < intervals.size(); i++) {
      if (intervals[i].start > merged.back().end) {
        merged.push_back(intervals[i]);
      } else
        merged.back().end = max(merged.back().end, intervals[i].end);
    }

    // Find the gap
    vector<Interval> result;
    for (int i = 0; i < merged.size() - 1; i++) {
      int start = merged[i].end;     // pick end time
      int end = merged[i + 1].start; // pick start time
      result.emplace_back(start, end);
    }
    return result;
  }
};

void test_employee_free_time() {
  Solution_759 s;
  // TODO: Make it compile
  // CHECK(s.employeeFreeTime({{{1, 2}, {5, 6}}, {{1, 3}}, {{4, 10}}}), {{3,
  // 4}});
}