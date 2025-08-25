#include "../my_util.h"
/*
https://leetcode.com/problems/word-ladder/

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
  /* node, distance from source */
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

/*
126. Word Ladder II .
Given two words (beginWord and endWord), and a dictionary's word list, find all
shortest transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a
transformed word. Note:

Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]
*/
/*
 Learnings :
 Since we had to print paths so I imagined that we would need to apply recursion
 + backtracking. As a result I ended up printing all the paths which is wrong
 for this problem.
*/
class Solution_all_paths {
 public:
  vector<vector<string>> findLadders(string beginWord, string endWord,
                                     const vector<string>& wordList) {
    for (auto str : wordList) {
      dict.emplace(str);
    }
    current.reserve(dict.size());
    current.push_back(beginWord);
    target = endWord;
    findLadders(beginWord);
    return result;
  }

 private:
  set<string> dict;
  vector<vector<string>> result;
  vector<string> current;
  string target;

  void findLadders(string source) {
    if (source == target) {
      result.push_back(current);
    }
    for (int i = 0; i < source.size(); i++) {
      char prev_ch = source[i];
      for (int j = 0; j < 26; j++) {
        source[i] = 'a' + j;
        if (dict.count(source) > 0) {
          current.push_back(source);
          dict.erase(source);
          findLadders(source);
          current.pop_back();
          dict.emplace(source);
        }
        source[i] = prev_ch;
      }
    }
  }
};

/*

Given two words (beginWord and endWord), and a dictionary's word list, find all
shortest transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a
transformed word. Note:

Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]

Learning:-----
The key is word "shortest sequence" that indicates we need to apply BFS.
But how do we apply BFS. This question takes the understanding of BFS to new
level. In the previous problem we stored the count in the queue. But this time
we need to store the entire path in the queue.
1. We could store the entire path in the queue.
2. How we iterate the chars in the loop.
3. We would need local visited for every path.
  We can't just remove the words from the dict.
*/
class Solution_126 {
 public:
  vector<vector<string>> findLadders(string beginWord, string endWord,
                                     const vector<string>& wordList) {
    vector<vector<string>> result;
    unordered_set<string> dict(wordList.begin(), wordList.end());
    queue<vector<string>> q;
    q.push({beginWord});
    // result.empty() is just an optimization.
    while (!q.empty() && result.empty()) {
      unordered_set<string> visited;
      // Evaluate all childrens i.e. paths, ladders
      /*
        Gotcha :
        We have to pre-calculate the size of q
        since it is getting changed in the loop.
        we could endup in the infinite loop.
       */
      int size = q.size();
      for (int i = 0; i < size; i++) {
        vector<string> path = q.front();
        q.pop();
        vector<string> words = expand(path.back(), dict, visited);
        for (auto word : words) {
          path.push_back(word);

          if (word == endWord) {
            result.push_back(path);
          } else {
            q.push(path);
          }

          path.pop_back();
        }
      }
      for (auto word : visited) {
        dict.erase(word);
      }
    }
    return result;
  }

  vector<string> expand(string& source, unordered_set<string>& dict,
                        unordered_set<string>& visited) {
    vector<string> words;
    for (int i = 0; i < source.size(); i++) {
      char prev_ch = source[i];
      for (char ch = 'a'; ch <= 'z'; ch++) {
        source[i] = ch;
        if (dict.count(source)) {
          words.push_back(source);
          visited.emplace(source);
        }
      }
      source[i] = prev_ch;
    }
    return words;
  }
};

void test_find_ladders_126() {
  Solution_126 s;
  CHECK(s.findLadders("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}),
        {{"hit", "hot", "dot", "dog", "cog"},
         {"hit", "hot", "lot", "log", "cog"}});
  Solution_all_paths s2;
  CHECK(
      s2.findLadders("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}),
      {{"hit", "hot", "dot", "lot", "log", "cog"},
       {"hit", "hot", "dot", "lot", "log", "dog", "cog"},
       {"hit", "hot", "dot", "dog", "cog"},
       {"hit", "hot", "dot", "dog", "log", "cog"},
       {"hit", "hot", "lot", "dot", "dog", "cog"},
       {"hit", "hot", "lot", "dot", "dog", "log", "cog"},
       {"hit", "hot", "lot", "log", "cog"},
       {"hit", "hot", "lot", "log", "dog", "cog"}});
  PRINT_MSG;
}