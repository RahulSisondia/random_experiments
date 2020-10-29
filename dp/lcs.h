#include "../my_util.h"

/*
  https://www.geeksforgeeks.org/longest-common-substring-dp-29/
  - Pass the length of the both strings.
*/
int count_lcs_rec(string s1, string s2, int l1, int l2) {
  if (l1 == 0 || l2 == 0) return 0;
  int count;
  /*
   if both character matches then count is increased by 1.
   else check in two other possibilities.
  */
  if (s1[l1 - 1] == s2[l2 - 1]) {
    count = 1 + count_lcs_rec(s1, s2, l1 - 1, l2 - 1);
  } else {
    count = max(count_lcs_rec(s1, s2, l1 - 1, l2),
                count_lcs_rec(s1, s2, l1, l2 - 1));
  }
  return count;
}

int count_lcs_top_down_util(string s1, string s2, int l1, int l2,
                            vector<vector<int>>& matrix) {
  int ans;
  // If value already exists then use that.
  if (matrix[l1][l2] != -1) {
    return matrix[l1][l2];
  }
  // Base condition
  if (l1 <= 0 || l2 <= 0) {
    ans = 0;
  }
  /*
   if both character matches then count is increased by 1.
   else check in two other possibilities.
  */
  else if (s1[l1 - 1] == s2[l2 - 1]) {
    ans = 1 + count_lcs_top_down_util(s1, s2, l1 - 1, l2 - 1, matrix);
  } else {
    ans = max(count_lcs_top_down_util(s1, s2, l1 - 1, l2, matrix),
              count_lcs_top_down_util(s1, s2, l1, l2 - 1, matrix));
  }
  matrix[l1][l2] = ans;
  return ans;
}

int count_lcs_top_down(string s1, string s2, int l1, int l2) {
  vector<vector<int>> matrix(l1 + 1, vector<int>(l2 + 1, -1));
  return count_lcs_top_down_util(s1, s2, l1, l2, matrix);
}

int count_lcs_bottom_up(string s1, string s2, int l1, int l2) {
  vector<vector<int>> matrix(l1 + 1, vector<int>(l2 + 1, 0));
  for (int i = 1; i <= l1; i++) {
    for (int j = 1; j <= l2; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        matrix[i][j] = 1 + matrix[i - 1][j - 1];
      } else {
        matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1]);
      }
    }
  }
  return matrix.back().back();
}

/*
 https://www.geeksforgeeks.org/printing-longest-common-subsequence/
  - We could use the matrix got using top_down.
  - Don't try to play or simplify the code wrt indices. Keep it simple.
*/
string print_lcs(string s1, string s2, int l1, int l2) {
  vector<vector<int>> matrix(l1 + 1, vector<int>(l2 + 1, -1));
  int count = count_lcs_top_down_util(s1, s2, l1, l2, matrix);
  string res;
  res.reserve(count);
  int i = l1;
  int j = l2;

  // Enable for debugging
  // print_matrix(matrix);

  while (i != 0 && j != 0) {
    if (s1[i - 1] == s2[j - 1]) {
      res.push_back(s1[i - 1]);
      i--;
      j--;
    } else if (matrix[i - 1][j] > matrix[i][j - 1]) {
      i--;
    } else
      j--;
  }
  reverse(res.begin(), res.end());
  return res;
}

void lcs() {
  string s1 = "abcdxyz";
  string s2 = "xyzabcd";
  CHECK(count_lcs_rec(s1, s2, s1.length(), s2.length()), 4);
  CHECK(count_lcs_top_down(s1, s2, s1.length(), s2.length()), 4);
  CHECK(count_lcs_bottom_up(s1, s2, s1.length(), s2.length()), 4);
  CHECK<string>(print_lcs(s1, s2, s1.length(), s2.length()), "abcd");
  s1 = "marvin";
  s2 = "panic";
  CHECK<string>(print_lcs(s1, s2, s1.length(), s2.length()), "an");
  cout << "cound LCS tests passed" << endl;
}

//----------longest common substring-----------------------------

/*
The recursive method for finding longest common substring is:
Given A and B as two strings, let m as the last index for A, n as the last index
for B.

    if A[m] == B[n] increase the result by 1.
    if A[m] != B[n] :
      compare with A[m -1] and B[n] or
      compare with A[m] and B[n -1]
    with result reset to 0.

We now have res as an argument.
*/
int longest_common_sub_string_rec(string s1, string s2, int l1, int l2,
                                  int res) {
  if (l1 == 0 || l2 == 0) return 0;
  if (s1[l1 - 1] == s2[l2 - 1]) {
    res = longest_common_sub_string_rec(s1, s2, l1 - 1, l2 - 1, 1 + res);
  } else {
    /*
      Compare the result for other two possibilities by resetting the result
      calculated so far to 0. Return the max of all three possibilities.
    */
    res = max({res, longest_common_sub_string_rec(s1, s2, l1 - 1, l2, 0),
               longest_common_sub_string_rec(s1, s2, l1, l2 - 1, 0)});
  }
  return res;
}

int longest_common_sub_string_bottom_up(string s1, string s2, int l1, int l2) {
  vector<vector<int>> matrix(l1 + 1, vector<int>(l2 + 1, 0));
  int res = numeric_limits<int>::min();
  for (int i = 1; i <= l1; i++) {
    for (int j = 1; j <= l2; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        matrix[i][j] = 1 + matrix[i - 1][j - 1];
        res = max(res, matrix[i][j]);
      } else {
        matrix[i][j] = 0;
      }
    }
  }
  return res;
}
/*
Algo varies a bit. In this case we  don't rely on the last value in the matrix.
The result could be anywhere in the matrix. Therefore we store The max result
found so far. Observe carefully both version.
*/
void longest_common_sub_string() {
  string s1 = "zxxabcdezy";
  string s2 = "yzabcdezx";
  CHECK(longest_common_sub_string_rec(s1, s2, s1.length(), s2.length(), 0), 6);
  CHECK(longest_common_sub_string_bottom_up(s1, s2, s1.length(), s2.length()),
        6);
  CHECK(count_lcs_rec(s1, s2, s1.length(), s2.length()), 7);
  PRINT_MSG;
}