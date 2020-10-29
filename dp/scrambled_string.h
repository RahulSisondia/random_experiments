#pragma once

#include "../my_util.h"

bool scrambled_strings_top_down_util(string a, string b,
                                     unordered_map<string, bool>& dp) {
  if (a.length() != b.length()) return false;
  if (a.compare(b) == 0) return true;
  if (a.length() <= 1) return false;
  string t = a + "_" + b;
  if (dp.find(t) != dp.end()) return dp[t];
  int n = a.length();
  bool result = false;
  for (int k = 1; k <= n - 1; k++) {
    bool cond1, cond2;
    cond1 = cond2 = false;
    // Strings are not swapped
    if (scrambled_strings_top_down_util(a.substr(0, k), b.substr(0, k), dp) ==
            true &&
        scrambled_strings_top_down_util(a.substr(k, n - k), b.substr(k, n - k),
                                        dp) == true) {
      cond1 = true;
    }
    // Strings are swapped
    if (scrambled_strings_top_down_util(a.substr(0, k), b.substr(n - k, k),
                                        dp) == true &&
        scrambled_strings_top_down_util(a.substr(k, n - k), b.substr(0, n - k),
                                        dp) == true) {
      cond2 = true;
    }
    if (cond1 || cond2) {
      result = true;
      break;
    }
  }
  return dp[t] = result;
}

bool scrambled_strings_top_down(string a, string b) {
  unordered_map<string, bool> dp;
  return scrambled_strings_top_down_util(a, b, dp);
}

/*
• https://leetcode.com/problems/scramble-string/
• https://www.interviewbit.com/problems/scramble-string/
Given a string A, we may represent it as a binary tree by partitioning it to two
non-empty substrings recursively. Below is one possible representation of A =
“great”:

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t

To scramble the string, we may choose any non-leaf node and swap its two
children. For example, if we choose the node “gr” and swap its two children, it
produces a scrambled string “rgeat”. rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that “rgeat” is a scrambled string of “great”.
Similarly, if we continue to swap the children of nodes “eat” and “at”, it
produces a scrambled string “rgtae”. rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that “rgtae” is a scrambled string of “great”.

Given two strings A and B of the same length, determine if B is a scrambled
string of S.

Input Format:
The first argument of input contains a string A.
The second argument of input contains a string B.
Output Format:
Return an integer, 0 or 1:
    => 0 : False
    => 1 : True
Constraints:
1 <= len(A), len(B) <= 50
Examples:
Input 1:
    A = "we"
    B = "we"
Output 1:
    1
Input 2:
    A = "phqtrnilf"
    B = "ilthnqrpf"

Output 2:
    0

*/
void test_scrambled_strings() {
  CHECK(scrambled_strings_top_down("great", "rgtae"), true);
  CHECK(scrambled_strings_top_down("great", "egtar"), false);
  PRINT_MSG;
}