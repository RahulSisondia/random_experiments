#include "../my_util.h"
/*
This is text justification problem.
We calculate the minimum cost recursively.
If we observe carefully it is nothing but the  matrix chain multiplication
pattern.
*/
int word_wrap_rec(const vector<int>& v, int w /* width */, int i) {
  // first base condition - if index gets beyond the array 'l' , then return 0;
  if (i > v.size() - 1) {
    return 0;
  }
  // second base condition - if index is the last word i.e there is only one
  // word left in the array to be inserted in the line then return the cost if
  // added in that line.
  if (i == v.size() - 1) {
    return (w - v[i]) * (w - v[i]) * (w - v[i]);
  }
  int cost = INT_MAX;
  // Here , we try to select words from the array and apply word_wrap on the
  // rest of the array. From index to last element, we iteratvely select first,
  // or first two and so on.
  for (int k = i; k < v.size(); k++) {
    // Calculate the width including all words from i to k
    int current_width = 0;
    for (int j = i; j <= k; j++) {
      current_width = current_width + v[j];
    }
    // Adding the space between the words choses. If 2 words are chosen , there
    // is one space and so on
    current_width = current_width + k - i;
    // If current width is legitimate then only we evalaute this partition.
    if (current_width <= w) {
      int current_cost =
          (w - current_width) * (w - current_width) * (w - current_width);
      int next_cost = word_wrap_rec(v, w, k + 1);
      cost = min(cost, current_cost + next_cost);
    }
  }
  return cost;
}

int word_wrap_rec(const vector<string>& words, int w /* width */) {
  vector<int> lengths;
  for (auto word : words) {
    lengths.push_back(word.size());
  }
  return word_wrap_rec(lengths, w, 0);
}

int word_wrap_rec(const vector<int>& lengths, int w /* width */) {
  return word_wrap_rec(lengths, w, 0);
}

/**************************************/

int word_wrap_top_down(const vector<int>& v, int w /* width */, int i,
                       unordered_map<string, int>& dp) {
  // first base condition - if index gets beyond the array 'l' , then return 0;
  if (i > v.size() - 1) {
    return 0;
  }
  // second base condition - if index is the last word i.e there is only one
  // word left in the array to be inserted in the line then return the cost if
  // added in that line.
  if (i == v.size() - 1) {
    return (w - v[i]) * (w - v[i]) * (w - v[i]);
  }
  int cost = INT_MAX;
  string key = to_string(i) + "_" + to_string(v.size() - 1);
  if (dp.find(key) != dp.end()) {
    return dp[key];
  }
  // Here , we try to select words from the array and apply word_wrap on the
  // rest of the array. From index to last element, we iteratvely select first,
  // or first two and so on.
  for (int k = i; k < v.size(); k++) {
    // Calculate the width including all words from i to k
    int current_width = 0;
    for (int j = i; j <= k; j++) {
      current_width = current_width + v[j];
    }
    // Adding the space between the words choses. If 2 words are chosen , there
    // is one space and so on
    current_width = current_width + k - i;
    // If current width is legitimate then only we evalaute this partition.
    if (current_width <= w) {
      int current_cost =
          (w - current_width) * (w - current_width) * (w - current_width);
      int next_cost = word_wrap_top_down(v, w, k + 1, dp);
      cost = min(cost, current_cost + next_cost);
    }
  }
  dp[key] = cost;
  return cost;
}

int word_wrap_top_down(const vector<int>& lengths, int w /* width */) {
  unordered_map<string, int> dp;
  int num = word_wrap_top_down(lengths, w, 0, dp);
  return num;
}
/**********************************************************************/

void test_word_wrap() {
  CHECK(word_wrap_rec({3, 2, 2, 5}, 6), 29);
  CHECK(word_wrap_rec({6, 3, 5, 2, 4}, 10), 92);
  CHECK(word_wrap_top_down({3, 2, 2, 5}, 6), 29);
  CHECK(word_wrap_top_down({6, 3, 5, 2, 4}, 10), 92);
  PRINT_MSG;
}
