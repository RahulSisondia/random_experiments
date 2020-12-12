#include "../my_util.h"
/*
EPI 19.7
Shortest Word Edit Path
Given two words source and target, and a list of words words, find the length of
the shortest series of edits that transforms source to target.

Each edit must change exactly one letter at a time, and each intermediate word
(and the final target word) must exist in words.

If the task is impossible, return -1.

Examples:

source = "bit", target = "dog"
words = ["but", "put", "big", "pot", "pog", "dog", "lot"]

output: 5
explanation: bit -> but -> put -> pot -> pog -> dog has 5 transitions.
source = "no", target = "go"
words = ["to"]

output: -1
*/
int transform_string(const string& source, const string& target,
                     vector<string> words) {
  unordered_set<string> dict;
  for (auto word : words) {
    dict.emplace(word);
  }
  queue<pair<string, int>> q;
  q.push({source, 0});
  dict.erase(source);
  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    string str = p.first;
    if (str == target) return p.second;
    for (int i = 0; i < str.size(); i++) {
      for (int j = 0; j < 26; j++) {
        str[i] = 'a' + j;
        auto it(dict.find(str));
        if (it != dict.end()) {
          q.push({str, p.second + 1});  // Increase the distance
          dict.erase(str);
        }
        str = p.first;  // Restore the string for next iteration.
      }
    }
  }
  return -1;
}

void test_transform_string() {
  CHECK(transform_string("bit", "dog",
                         {"but", "put", "big", "pot", "pog", "dog", "lot"}),
        5);
  CHECK(transform_string("bit", "ddddd",
                         {"but", "put", "big", "pot", "pog", "dog", "lot"}),
        -1);
  PRINT_MSG;
}