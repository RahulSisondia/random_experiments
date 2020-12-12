#ifndef PCH_H
#define PCH_H

#include "../my_util.h"

struct Subarray {
  int start = -1;
  int end = -1;
};

vector<string> file_smallest_sub_array(vector<string> parapraph,
                                       unordered_set<string> keywords) {
  Subarray result{-1, -1};
  unordered_map<string, int> keywords_to_cover;
  for (const string &keyword : keywords) {
    ++keywords_to_cover[keyword];
  }

  int remaining_to_cover = keywords.size();
  for (int left = 0, right = 0; right < parapraph.size(); right++) {
    // cout << "left :" << left << " right : " << right << endl;
    if (keywords.count(parapraph[right]) &&
        --keywords_to_cover[parapraph[right]] >= 0) {
      --remaining_to_cover;
    }

    while (remaining_to_cover == 0) {
      if ((result.start == -1 && result.end == -1) ||
          (right - left < result.end - result.start)) {
        result.start = left;
        result.end = right;
      }

      if (keywords.count(parapraph[left]) &&
          ++keywords_to_cover[parapraph[left]] > 0) {
        ++remaining_to_cover;
      }
      ++left;
    }
  }
  vector<string> r;
  int index = result.start;
  while (index <= result.end) {
    r.push_back(parapraph[index++]);
  }
  return r;
}

void test_sliding_window() {
  CHECK(file_smallest_sub_array(
            {"apple", "banana", "apple", "apple", "dog", "cat", "apple", "dog",
             "banana", "apple", "cat", "dog"},
            {"banana", "cat"}),
        {"banana", "apple", "cat"});
  PRINT_MSG;
}
#endif  // PCH_H
