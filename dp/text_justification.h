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

/*
68. Text Justification
Given an array of words and a width maxWidth, format the text such that each
line has exactly maxWidth characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as
you can in each line. Pad extra spaces ' ' when necessary so that each line has
exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the
number of spaces on a line do not divide evenly between words, the empty slots
on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is
inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters
only. Each word's length is guaranteed to be greater than 0 and not exceed
maxWidth. The input array words contains at least one word.


Example 1:

Input: words = ["This", "is", "an", "example", "of", "text", "justification."],
maxWidth = 16 Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
*/
class Solution_76 {
 public:
  vector<string> fullJustify(const vector<string>& words, int L) {
    vector<string> ans, vs;
    string str;

    int len = 0;
    for (int i = 0; i < words.size(); ++i) {
      if (len /* words len*/ + vs.size() /* spaces */ + words[i].size() <= L) {
        // vs not full, need to get more words in the line
        vs.push_back(words[i]);
        len += words[i].size();
      } else {
        // vs full, get the whole line
        if (vs.size() == 1) {
          // just one word, the left justify
          str = vs[0];
          str.append(L - str.size(), ' ');
          ans.push_back(str);
        } else if (vs.size() > 1) {
          /* the first "mod" words get "div+1" spaces
           the remaining words get "div" spaces
           We now have words len. And the spaces to inserts are (L-len).
           Interesting part is how to distribute these spaces.
           by div, we can be sure that each word will get 'div' spaces prefix.
           but if there still remainins spaces then we equally distribute them
           before first few words.
           For instance:
           We have 4 words. The word length is 15. That means we shall have
           23-15 = 8 spaces to add. How do we add them ?
           23 -15/3 = 2 (div)
           23-15 % 3 = 2 (mod)
           If we just add 2(div) spaces prefix before 3
           words then we will remain with 2 space. So the strategy is to allot
           the spaces as 2+1 2+1 2
          */
          int div = (L - len) / (vs.size() - 1);
          int mod = (L - len) % (vs.size() - 1);
          str = vs[0];
          for (int j = 1; j < vs.size(); ++j) {
            if (j <= mod)
              str.append(div + 1, ' ');  // one more space
            else
              str.append(div, ' ');
            str += vs[j];
          }
          ans.push_back(str);
        }

        vs.clear();
        vs.push_back(words[i]);
        len = words[i].size();
      }
    }

    // the last line, left justified and no extra space is inserted between
    // words
    str = vs[0];
    for (int j = 1; j < vs.size(); ++j) str += ' ' + vs[j];
    str.append(L - str.size(), ' ');
    ans.push_back(str);
    return ans;
  }
};

void test_justification() {
  Solution_76 s;
  CHECK(
      s.fullJustify(
          {"This", "is", "an", "example", "of", "text", "justification."}, 16),
      {"This    is    an", "example  of text", "justification.  "});

  PRINT_MSG;
}