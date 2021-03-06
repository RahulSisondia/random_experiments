#include "../my_util.h"

int max_subarray_k_sum(const vector<int>& v, int k) {
  int left = 0, right = 0;
  int sum = 0;
  int max_sum = numeric_limits<int>::min();
  while (right < v.size()) {
    sum = sum + v[right];
    if (right - left + 1 < k) {
      right++;
    } else if (right - left + 1 == k) {
      max_sum = max(max_sum, sum);
      sum = sum - v[left];  // Exclude the element included earlier.
      // Now shift to the next window.
      left++;
      right++;
    }
  }
  return max_sum;
}
void test_max_subarray_k_sum() {
  CHECK(max_subarray_k_sum({100, 200, 300, 400}, 2), 700);
  PRINT_MSG;
}
/*
https://practice.geeksforgeeks.org/problems/first-negative-integer-in-every-window-of-size-k/0#
{12 -1 -7 8 -15 30 16 28} k = 3
output {-1 -1 -7 -15 -15 0}
*/
vector<int> find_first_negative_number_in_window(const vector<int>& v,
                                                 int k /* window size*/) {
  int left = 0, right = 0;
  list<int> negative_nums_list;
  vector<int> result;
  while (right < v.size()) {
    // Do some operation
    if (v[right] < 0) negative_nums_list.push_back(v[right]);

    if (right - left + 1 < k) {
      right++;  // Attempt to make the first window.
    } else if (right - left + 1 == k) {
      // Make the output.
      if (negative_nums_list.empty()) {
        result.push_back(0);
      } else {
        result.push_back(negative_nums_list.front());
      }
      // Now shift to the next window but we need to remove the element from the
      // list if it was added before.
      if (v[left] == negative_nums_list.front()) negative_nums_list.pop_front();
      left++;
      right++;
    }
  }
  return result;
}
void test_find_negative_number_in_window() {
  CHECK(find_first_negative_number_in_window({-8, 2, 3, -6, 10}, 2),
        {-8, 0, -6, -6});
  CHECK(
      find_first_negative_number_in_window({12, -1, -7, 8, -15, 30, 16, 28}, 3),
      {-1, -1, -7, -15, -15, 0});
  PRINT_MSG;
}

/*
https://practice.geeksforgeeks.org/problems/count-occurences-of-anagrams5839/1
        Input: txt = forxxorfxdofr , pat = for Output: 3
Explanation: for, orf and ofr appears in the txt, hence answer is 3.
*/
vector<string> find_all_anagrams(const string str, const string pattern) {
  unordered_map<char, int> fm;  // frequency map
  int left = 0, right = 0;
  vector<string> result;
  // Calculate the frquencies in the pattern.
  for (auto ch : pattern) {
    ++fm[ch];
  }
  // global counter. It keeps track of the window. If all
  // chars are included then its count befomes 0
  int gc = fm.size();
  int k = pattern.size();  // Window Size
  while (right < str.size()) {
    char ch = str[right];
    if (fm.find(ch) != fm.end()) {
      --fm[ch];
      if (fm[ch] == 0) gc--;
    }
    if (right - left + 1 < k) {
      right++;  // Make the first Window.
    } else if (right - left + 1 == k) {
      if (gc == 0) {
        result.push_back(str.substr(left, right - left + 1));
      }
      // Shift the window
      ch = str[left];
      if (fm.find(ch) != fm.end()) {
        ++fm[ch];
        // Goatchas : Don't forget the condition check.  Remember we need to
        // increase the count only when char is added first time in the map.
        if (fm[ch] == 1) ++gc;
      }
      left++;
      right++;
    }
  }
  return result;
}

vector<string> find_all_anagrams_better(const string str,
                                        const string pattern) {
  unordered_map<char, int> fm;  // frequency map
  int left = 0, right = 0;
  vector<string> result;
  // Calculate the frquencies in the pattern.
  for (auto ch : pattern) {
    ++fm[ch];
  }

  // global counter. It keeps track of the window. If all
  // chars are included then its count befomes 0.
  // We need to keep track of elcment when they are inserted first in the fm.
  // Therefore, it is OK to check the size of the map.
  int gc = fm.size();

  int k = pattern.size();  // Window Size
  while (right < str.size()) {
    char ch = str[right];
    if (fm.find(ch) != fm.end()) {
      --fm[ch];
      if (fm[ch] == 0) gc--;
    }
    if (right - left + 1 == k) {
      if (gc == 0) {
        result.push_back(str.substr(left, right - left + 1));
      }
      // Shift the window
      ch = str[left];
      if (fm.find(ch) != fm.end()) {
        ++fm[ch];
        // Goatchas : Don't forget he condition check.  Remember we need to
        // increase the count only when char is added first time in the map.
        if (fm[ch] == 1) ++gc;
      }
      left++;
    }
    right++;
  }
  return result;
}

void test_find_all_anagrams() {
  CHECK(find_all_anagrams("forxxorfxdofr", "for"), {"for", "orf", "ofr"});
  CHECK(find_all_anagrams("ccbabd", "abbc"), {"cbab"});
  CHECK(find_all_anagrams("aabaabaa", "aaba"),
        {"aaba", "abaa", "aaba", "abaa"});
  CHECK(find_all_anagrams_better("forxxorfxdofr", "for"),
        {"for", "orf", "ofr"});
  PRINT_MSG;
}

/*
Given an array arr[] of size N and an integer K. Find the maximum for each and
every contiguous subarray of size K.

Example:

Input 1:
    A = [1, 3, -1, -3, 5, 3, 6, 7]
    B = 3
Output 1:
    C = [3, 3, 5, 5, 6, 7]

 If K > length of the array, return 1 element with the max of the array.
*/
vector<int> find_max_each_subarray(vector<int> v, int k) {
  int left = 0, right = 0;
  list<int> tlist;  // temporary list
  vector<int> result;
  // If subarray size is greater than array then return
  if (k > v.size()) {
    result.push_back(*max_element(v.begin(), v.end()) + 1);
    return result;
  }

  while (right < v.size()) {
    // Operation.
    {
      while (!tlist.empty() && tlist.front() < v[right]) {
        tlist.pop_front();
      }
      // We are maintaing list in descending order.
      tlist.push_back(v[right]);
    }
    if (right - left + 1 == k) {
      // Make the output.
      result.push_back(tlist.front());
      // Now shift to the next window but we need to remove the element from the
      // list if it was added before.
      if (v[left] == tlist.front()) tlist.pop_front();
      left++;
    }
    right++;
  }
  return result;
}

void test_find_max_each_subarray() {
  CHECK(find_max_each_subarray({1, 3, -1, -3, 5, 3, 6, 7}, 3),
        {3, 3, 5, 5, 6, 7});
  CHECK(find_max_each_subarray({1, 3, -1, -3, 5, 3, 6, 7}, 9), {8});
  CHECK(find_max_each_subarray({12, -1, -7, 8, -15, 30, 16, 28}, 3),
        {12, 8, 8, 30, 30, 30});
  PRINT_MSG;
}

/*
Problem Description:
Given an array containing N positive integers and an integer K. Your task is to
find the length of the longest Sub-Array with sum of the elements equal to the
given value K.
For Input: 4 1 1 1 2 3 5, K = 5
your output is: 4
*/
int largest_subarray_sum_k(const vector<int>& v, int k) {
  int left = 0;
  int right = 0;
  int max_size = INT_MIN;
  int sum = 0;
  while (right < v.size()) {
    sum = sum + v[right];
    if (sum == k) {
      max_size = max(max_size, right - left + 1);
    }
    // Shrink the window from the left side if some has become more than the
    // target K
    while (sum > k) {
      sum = sum - v[left];
      left++;
    }
    right++;
  }
  return max_size;
}

/*
 This algorithm is given at
 https://www.techiedelight.com/find-maximum-length-sub-array-having-given-sum/
 It also kind of maintains a sliding window but using map.
 This also doesn't work for negative numbers. :-()
*/
int largest_subarray_sum_k_II(const vector<int>& v, int k) {
  unordered_map<int, int> mp;
  int sum = 0;
  int max_len = 0;
  int end_index = 0;
  for (int i = 0; i < v.size(); i++) {
    sum += v[i];

    if (mp.find(sum) == mp.end()) {
      mp[sum] = i;
    }
    if (mp.find(sum - k) != mp.end() && max_len < i - mp[sum - k]) {
      max_len = i - mp[sum - k];
      end_index = i;
    }
  }

  // PRINTV(vector<int>{v.begin() + (end_index - max_len) + 1,
  //                    v.begin() + end_index + 1});
  return max_len;
}
void test_largest_subarray_sum_k() {
  vector<int> v = {4, 1, 1, 1, 2, 3, 5};
  CHECK(largest_subarray_sum_k(v, 5), 4);
  CHECK(largest_subarray_sum_k_II(v, 5), 4);
  CHECK(largest_subarray_sum_k({10, 5, 2, 7, 1, 9}, 7), 2);
  CHECK(largest_subarray_sum_k({5, 6, -5, 5, 3, 5, 3, -2, 0}, 8), 4);
  // PRINT(largest_subarray_sum_k({-5, -6, -5, 5, 3, 5, 3, -2, 0}, -16));
  // PRINT(largest_subarray_sum_k_II({-5, -6, -5, 5, 3, 5, 3, -2, 0}, -16));
  PRINT_MSG;
}

/*
Longest K unique characters substring
Given a string you need to print the size of the longest possible substring that
has exactly k unique characters. If there is no possible substring print -1.
Example
For the string aabacbebebe and k = 3 the substring will be cbebebe with
length 7.
*/
/*
 We could optimize by removing the first condition and moving right++ out but I
 think it will be good to start with this template and improve later on.
*/
int longest_unique_k_chars(const string& str, int k) {
  unordered_map<char, int> mp;
  int max_len = numeric_limits<int>::min();
  int left = 0, right = 0;
  while (right < str.size()) {
    ++mp[str[right]];
    if (mp.size() < k) {
      right++;
    } else if (mp.size() == k) {
      max_len = max(max_len, (right - left + 1));
      right++;
    } else {
      while (mp.size() > k) {
        char ch = str[left];
        --mp[ch];
        if (mp[ch] == 0) mp.erase(ch);
        left++;
      }
      right++;
    }
  }
  return max_len;
}

void test_longest_unique_k_chars() {
  CHECK(longest_unique_k_chars("aabacbebebe", 3), 7);
  PRINT_MSG;
}

/*
3. Longest Substring Without Repeating Characters
Given a string s, find the length of the longest substring without repeating
characters.

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a
substring. Example 4:

Input: s = ""
Output: 0
*/
int longest_unique_substring_length(string str) {
  int left = 0;
  int right = 0;
  unordered_set<char> dict;
  size_t max_length = 0;
  while (right < str.size()) {
    if (dict.find(str[right]) == dict.end()) {
      dict.emplace(str[right]);
      max_length = max(max_length, dict.size());
      right++;
    } else {
      dict.erase(str[left]);
      left++;
    }
  }
  return max_length;
}

int longest_unique_substring_length_II(const string& str) {
  unordered_map<char, int> mp;
  int max_len = 0;
  int left = 0, right = 0;
  int k;
  while (right < str.size()) {
    ++mp[str[right]];
    k = (right - left + 1);
    if (mp.size() == k) {
      max_len = max(max_len, k);
    } else {
      while (mp.size() < k) {
        char ch = str[left];
        --mp[ch];
        if (mp[ch] == 0) mp.erase(ch);
        left++;
        k--;  // increasing left meaning window size is shrinked.
      }
      if (mp.size() == k) {
        max_len = max(max_len, k);
      }
    }
    right++;
  }
  return max_len;
}

void test_longest_unique_substring_length() {
  CHECK(longest_unique_substring_length("abcabcbb"), 3);
  CHECK(longest_unique_substring_length(" "), 1);
  CHECK(longest_unique_substring_length(""), 0);
  CHECK(longest_unique_substring_length("aab"), 2);
  CHECK(longest_unique_substring_length("pwwkew"), 3);
  CHECK(longest_unique_substring_length_II("abcabcbb"), 3);
  CHECK(longest_unique_substring_length_II(" "), 1);
  CHECK(longest_unique_substring_length_II(""), 0);
  CHECK(longest_unique_substring_length_II("aab"), 2);
  CHECK(longest_unique_substring_length_II("pwwkew"), 3);
  PRINT_MSG;
}

/*
https://leetcode.com/problems/maximum-product-subarray/
• At a first glance this looks variable size sliding window
    .In fact it is variation of Kadane's algorithm.  The difference is that even
a min negative product encountered earlier could contribute to the max product.
• At any element we have three choices to determine the max product
        • Only current element
        • Current element* current_min
        • Current element* current_max
• We can find the solution using these choices easily.
*/
int longest_max_product(const vector<int>& nums) {
  if (nums.empty()) return -1;

  int current_min = nums[0];
  int current_max = nums[0];
  int ans = nums[0];
  int choice1;
  int choice2;
  for (int i = 1; i < nums.size(); i++) {
    choice1 = current_min * nums[i];
    choice2 = current_max * nums[i];
    current_min = min({nums[i], choice1, choice2});
    current_max = max({nums[i], choice1, choice2});
    ans = max(ans, current_max);
  }
  return ans;
}

void test_longest_max_product() {
  CHECK(longest_max_product({2, 3, -2, 4}), 6);
  CHECK(longest_max_product({-2, 0, -1}), 0);
  PRINT_MSG;
}

/*
https://leetcode.com/problems/minimum-window-substring/
Given two strings s and t, return the minimum window in s which will contain all
the characters in t. If there is no such window in s that covers all characters
in t, return the empty string "".

Note that If there is such a window, it is guaranteed that there will always be
only one unique minimum window in s.

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Example 2:

Input: s = "a", t = "a"
Output: "a"
*/
class Solution_76 {
 public:
  string minWindow(string s, string t) {
    unordered_map<char, int> fm;
    for (auto ch : t) {
      fm[ch]++;
    }
    string result;
    int matched = 0;
    int k = t.size();
    int min_len = INT_MAX;
    int len = 0;
    int start_index = -1;
    for (int left = 0, right = 0; right < s.size(); right++) {
      if (fm.count(s[right])) {
        fm[s[right]]--;
        if (fm[s[right]] >= 0)  // First difference with anagram problem.  >
          matched++;
      }

      while (matched == k) {
        len = right - left + 1;
        if (min_len > len) {
          min_len = len;
          // Also keep track of the starting index of the substr
          start_index = left;
        }
        // Shrink the window
        if (fm.find(s[left]) != fm.end()) {
          /* Since we shall remove the element from left, decrease the matched
           * count. This is important to add the check: Due to char repeation in
           * the source string, map may containt -ve values. Keep on shrinking
           * the window unless the count of a particual char becomes 0 */
          if (fm[s[left]] == 0) {
            matched--;
          }
          fm[s[left]]++;  // Remove the left char from the window.
        }
        left++;
      }
    }
    if (start_index != -1) {
      result = s.substr(start_index, min_len);
    }
    return result;
  }
};

void test_smallest_window_containing_substring() {
  Solution_76 s;
  CHECK(s.minWindow("aabdec", "abc"), std::string("abdec"));
  CHECK(s.minWindow("aabdecc", "abcc"), std::string("abdecc"));
  CHECK(s.minWindow("abdabca", "abc"), std::string("abc"));
  CHECK(s.minWindow("adcad", "abc"), std::string(""));
  CHECK(s.minWindow("aa", "aa"), std::string("aa"));
  PRINT_MSG;
}

/*
30. Substring with Concatenation of All Words.

You are given a string s and an array of strings words of the same length.
Return all starting indices of substring(s) in s that is a concatenation of each
word in words exactly once, in any order, and without any intervening
characters.

You can return the answer in any order.

Example 1:

Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar"
respectively. The output order does not matter, returning [9,0] is fine too.
*/
/*
 Interesting problem.  The first intution is to solve by recursion.
 In fact here is the recursive solution :
 https://duncan-mcardle.medium.com/leetcode-problem-30-substring-with-concatenation-of-all-words-javascript-2030111694e5

 We need to observe carefully the inputs. If they are in the form of substr
 then chances are sliding window technique will apply.
 It also gives different perspective since we we don't use the left pointer
 here. Instead substr are formed using the dictionay words. We also need another
 map the keep track if the words are visisited or not.

  O(N * M * Len)O(N∗M∗Len)
*/
class Solution_30 {
 public:
  vector<int> findSubstring(const string s, const vector<string>& words) {
    unordered_map<string, int> fm;  // Frequency Map
    int words_count = 0;
    for (auto word : words) {
      fm[word]++;
      words_count++;
    }
    int word_len = words[0].size();
    vector<int> result;
    //"wordgoodgoodgoodbestword"
    for (int r = 0 /* right */; r <= s.size() - word_len * words_count; r++) {
      unordered_map<string, int> visited;
      for (int wi = 0 /* word index */; wi < words_count; wi++) {
        int index = r + wi * word_len;
        string word = s.substr(index, word_len);
        if (fm.count(word) == 0) break;  // Not found.
        visited[word]++;
        if (visited[word] > fm[word]) break;  // found more than desired

        if (wi + 1 == words_count) {
          result.push_back(r);
        }
      }
    }
    return result;
  }
};

void test_substring_with_concatenation() {
  Solution_30 sol;
  CHECK(sol.findSubstring("barfoothefoobarman", {"foo", "bar"}), {0, 9});
  CHECK(sol.findSubstring("barfoothefoobarman", {"foo", "baz"}), {});
  CHECK(sol.findSubstring("barfoothefoobarman", {"baz"}), {});
  CHECK(sol.findSubstring("catfoxcat", {"cat", "fox"}), {0, 3});
  CHECK(sol.findSubstring("c", {"c"}), {0});
  CHECK(sol.findSubstring("wordgoodgoodgoodbestword",
                          {"word", "good", "best", "word"}),
        {});
  PRINT_MSG;
}