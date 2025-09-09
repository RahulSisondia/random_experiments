/*
 * Matrix Chain Multiplication (mcm)
 */

#include "../my_util.h"

/*
 If n =1 then there is one matrix, thus there is only one way to
 parenthesize. Otherwise it is recurrence from k=1 to n-1 for each k,
 P(K) P(n-k). It grows as  Ω(4^n/n^3/2). This could be simplified as
 Ω(2^n) which is exponential.
*/
int mcm_rec(vector<int> dims, int i, int j) {
  // i cannot be greater than j of course.
  // if i == j means only 1 dimension which invalid case as well.
  if (i >= j) return 0;
  int res = numeric_limits<int>::max();
  for (int k = i; k < j; k++) {
    //  Enable to debug
    // cout << "i: " << i << " j: " << j << " k: " << k << endl;
    int temp_res =
        mcm_rec(dims, i, k) /* cost of multiplying matrices from i to k */
        +
        mcm_rec(dims, k + 1, j) /* cost of multiplying matrices from k+1 to j */
        + (dims[i - 1] * dims[k] * dims[j])
        /* clang-format off
        cost of multiplying the previous two matrices.
        10*20*30*40*50
            i  k     j
          Suppose i, k, j  are positioned as above.
          (10*20, 20*30) * (30*40, 40*50) => (10*30) * (30*50) =>
          (10 * 30 * 50).
            i-1   k   j
        clang-format on */
        ;
    /* Keep track of the minimal cost so far */
    res = min(res, temp_res);
  }
  return res;
}

/**
  dp: to keep track of cost
  pmat : to keep track of position of k so that we can print where to put
  brackets.
*/
int mcm_top_down_util(vector<int> dims, int i, int j, vector<vector<int>>& dp,
                      vector<vector<int>>& pmat) {
  if (i >= j) return 0;
  int res = numeric_limits<int>::max();
  if (dp[i][j] != -1) return dp[i][j];
  for (int k = i; k < j; k++) {
    int temp_res =
        mcm_top_down_util(dims, i, k, dp,
                          pmat) /* cost of multiplying matrices from i to k */
        +
        mcm_top_down_util(dims, k + 1, j, dp,
                          pmat) /* cost of multiplying matrices from k+1 to j */
        + (dims[i - 1] * dims[k] *
           dims[j]) /* cost of multiplying the previous two matrices  */;

    /* Keep track of the minimal cost so far */
    res = min(res, temp_res);
    dp[i][j] = res;
    pmat[i][j] = k;

    // Uncomment to see matrices
    /* if (i == 1 && j == 4) {
      PRINT(pmat);
      PRINT(dp);
    } */
  }
  return res;
}
/*

*/
void print_parathesis(vector<int>& dims, vector<vector<int>>& pmat, int i,
                      int j) {
  if (i > j)
    return;
  else if (i == j)
    cout << "M" << i;
  else {
    cout << "(";
    print_parathesis(dims, pmat, i, pmat[i][j]);
    cout << " ";
    print_parathesis(dims, pmat, pmat[i][j] + 1, j);
    cout << ")";
  }
}

int mcm_top_down(vector<int> dims, int i, int j) {
  // It's fine to keep the length as dims.size() since we passed the j as
  // dims.size()-1.
  vector<vector<int>> dp(dims.size(), vector<int>(dims.size(), -1));
  vector<vector<int>> pmat(dims.size(), vector<int>(dims.size(), 0));
  int res = mcm_top_down_util(dims, i, j, dp, pmat);
  print_parathesis(dims, pmat, 0, dims.size() - 1);
  cout << endl;
  return res;
}

/*
TODO
  https://youtu.be/_WncuhSJZyA
  https://www.techiedelight.com/matrix-chain-multiplication/
*/
int mcm_bottom_up(vector<int> dims) {
  vector<vector<int>> dp(dims.size(), vector<int>(dims.size(), 0));
  for (int i = 1; i < dims.size(); i++) {
    for (int j = 1; j < dims.size(); j++) {
    }
  }
  return dp.back().back();
}

void mcm() {
  vector<int> dims{40, 20, 30, 10, 30};
  /*
   * dims = {d0, d1, d2, d3, d4,...}
   * Matrices :
   * { (do x d1) = M1, (d1 x d2) = M2, ( d2 x d3) = M3, (d3 x d4) = M4, ...}.
   * If I have been given 5 dims then I can form only 4 matrices out it.
   * Starting from 1st matrix i.e (do x d1). Therefore, pass 1 and 4
   */
  CHECK(mcm_rec(dims, 1, dims.size() - 1), 26000);
  CHECK(mcm_top_down(dims, 1, dims.size() - 1), 26000);
  cout << "Matrix Chain Multiplication tests passed.\n";
}

/*--------------- Palindromic Partitioning -----------------------*/

bool is_palindrome(string X, int i, int j) {
  // count_ops++;
  while (i <= j) {
    if (X[i++] != X[j--]) return false;
  }
  return true;
}

bool is_palindrome(string X) {
  // count_ops++;
  int i = 0;
  int j = X.length() - 1;
  while (i <= j) {
    if (X[i++] != X[j--]) return false;
  }
  return true;
}

int min_palindromic_partitioning_rec(string str, int i, int j) {
  // Passing both index to check palindrome is much easier than calculating the
  // inclusive length
  // if (i == j || is_palindrome(str.substr(i, j - i + 1)) == true) return 0;

  if (i == j || is_palindrome(str, i, j) == true) return 0;

  int res = numeric_limits<int>::max();
  for (int k = i; k <= j - 1; k++) {
    int temp_res =
        min_palindromic_partitioning_rec(str, i, k) /* left partition */
        + 1 /* cost of cutting left and right partitions */
        + min_palindromic_partitioning_rec(str, k + 1, j) /* right partition */;
    res = min(res, temp_res);
    count_ops++;
    // Uncomment to debug
    // cout << " i : " << i << " j: " << j << " k: " << k
    //      << " temp_res: " << temp_res << " res: " << res << endl;
  }
  return res;
}

int min_palindromic_partitioning_mem_util(string str, int i, int j,
                                          vector<vector<int>>& dp) {
  if (i == j || is_palindrome(str, i, j) == true) return 0;

  if (dp[i][j] != -1) return dp[i][j];

  int res = numeric_limits<int>::max();
  for (int k = i; k <= j - 1; k++) {
    int temp_res = min_palindromic_partitioning_mem_util(
                       str, i, k, dp) /* left partition */
                   + 1 /* cost of cutting left and right partitions */
                   + min_palindromic_partitioning_mem_util(
                         str, k + 1, j, dp) /* right partition */;
    res = min(res, temp_res);
    count_ops++;
  }
  dp[i][j] = res;
  return res;
}

int min_palindromic_partitioning_memo(string str, int i, int j) {
  vector<vector<int>> dp(str.length(), vector<int>(str.length(), -1));
  count_ops = 0;
  return min_palindromic_partitioning_mem_util(str, i, j, dp);
}

int min_palindromic_partitioning_mem_util_opt(string str, int i, int j,
                                              vector<vector<int>>& dp) {
  if (i == j) return 0;

  if (dp[i][j] != -1) return dp[i][j];

  /* We check for this base only if this subprpoblem was not evaluated before */
  if (is_palindrome(str, i, j) == true) return 0;

  int res = numeric_limits<int>::max();
  for (int k = i; k <= j - 1; k++) {
    int temp;
    // We now look the values for left & right partitions in the cache before
    // evaluating them.
    {
      /* left partition. */
      if (dp[i][k] != -1)
        temp = dp[i][k];
      else
        temp = min_palindromic_partitioning_mem_util_opt(str, i, k, dp);
    }
    temp += 1; /* cost of cutting left and right partitions */
    {
      /* right partition */;
      if (dp[k + 1][j] != -1)
        temp += dp[k + 1][j];
      else
        temp += min_palindromic_partitioning_mem_util_opt(str, k + 1, j, dp);
    }
    count_ops++;
    res = min(res, temp);
  }
  dp[i][j] = res;
  return res;
}

int min_palindromic_partitioning_memo_opt(string str, int i, int j) {
  vector<vector<int>> dp(str.length(), vector<int>(str.length(), -1));
  count_ops = 0;
  return min_palindromic_partitioning_mem_util_opt(str, i, j, dp);
}

void test_palindromic_partitioning() {
  string str("ababbbabbababa");  // abab| bb | abba | baba
  CHECK(min_palindromic_partitioning_rec(str, 0, str.size() - 1), 3);
  CHECK(min_palindromic_partitioning_memo(str, 0, str.size() - 1), 3);
  CHECK(min_palindromic_partitioning_memo_opt(str, 0, str.size() - 1), 3);

  // clang-format off
  /*
  Number of operations stats:

  Without counting palindrome operations:
    Number of operations in recursive soln : 255224
    Number of operations in memo soln : 362
    Number of operations in optimized mem soln : 362

  Counting palindrome operations:
    Number of operations in recursive soln : 432371 -  255224 = 177147 (is_palindromeis called)
    Number of operations in memo soln : 935  - 362 = 573  (ispalindrome is called)
    Number of operations in optimized mem soln : 460 - 362 = 98 (is palindrome is called)
  */
  // clang-format on
  str = "geeksforgeeks";  // g | ee | k | s | f | o | r | g | ee | k | s
  // count_ops = 0;
  CHECK(min_palindromic_partitioning_rec(str, 0, str.size() - 1), 10);
  // cout << "Number of operations in recursive soln : " << count_ops << endl;

  // count_ops = 0;
  CHECK(min_palindromic_partitioning_memo(str, 0, str.size() - 1), 10);
  // cout << "Number of operations in memo soln : " << count_ops << endl;

  // count_ops = 0;
  CHECK(min_palindromic_partitioning_memo_opt(str, 0, str.size() - 1), 10);
  // cout << "Number of operations in optimized mem soln : " << count_ops <<
  // endl;

  str = "nitin";
  CHECK(min_palindromic_partitioning_rec(str, 0, str.size() - 1), 0);
  CHECK(min_palindromic_partitioning_memo(str, 0, str.size() - 1), 0);
  CHECK(min_palindromic_partitioning_memo_opt(str, 0, str.size() - 1), 0);

  PRINT_MSG;
}
/*
https://leetcode.com/problems/burst-balloons/
You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with
a number on it represented by an array nums. You are asked to burst all the
balloons.

If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1]
coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if
there is a balloon with a 1 painted on it.

Return the maximum coins you can collect by bursting the balloons wisely.



Example 1:

Input: nums = [3,1,5,8]
Output: 167
Explanation:
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167

This is similar to mcm. Only hard part part is to get the calculations of
bursting balloons right
// 1,3,2,3,4,5,6,7,1
//   ^     ^     ^
//   i     k     j
*/
int burst_balloon(vector<int> v, int i, int j, vector<vector<int>>& dp) {
  if (i > j) return 0;
  if (i == j) {
    dp[i][j] = v[i - 1] * v[i] * v[i + 1];
    return dp[i][j];
  }
  if (dp[i][j] != -1) {
    return dp[i][j];
  }
  int res = numeric_limits<int>::min();
  for (int k = i; k <= j; k++) {
    int left_cost = burst_balloon(v, i, k - 1, dp);
    int right_cost = burst_balloon(v, k + 1, j, dp);
    /*
    Cost of bursting remaining balloons +
    Cost bursting the left side i to k- 1 balloons +
    Cost bursting the right side k+1 to j balloons
    */
    int cost = v[k] * v[i - 1] * v[j + 1] + left_cost + right_cost;
    res = max(res, cost);
  }
  dp[i][j] = res;
  return res;
}
int burst_balloon(vector<int> v) {
  int size = v.size();
  v.insert(v.begin(), 1);
  v.push_back(1);
  vector<vector<int>> dp(v.size(), vector<int>(v.size(), -1));
  // Original array will be at these positions
  return burst_balloon(v, 1, size, dp);
}
void test_burst_balloon() {
  vector<int> v = {3, 1, 5, 8};
  CHECK(burst_balloon(v), 167);
  PRINT_MSG;
}

/*
Given a non-empty string s and a dictionary wordDict containing a list of
non-empty words, determine if s can be segmented into a space-separated sequence
of one or more dictionary words.

Note:

The same word in the dictionary may be reused multiple times in the
segmentation. You may assume the dictionary does not contain duplicate words.
Example 1:

Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen
apple". Note that you are allowed to reuse a dictionary word.

Also have a look next problem - https://leetcode.com/problems/word-break-ii/
*/
class Solution_139 {
 public:
  bool wordBreak(const string s, const vector<string>& wordDict) {
    for (auto word : wordDict) {
      dict.emplace(word);
    }
    int n = s.size();
    vector<int> dp(n + 1, -1);
    return word_break(s, dp);
  }

 private:
  unordered_set<string> dict;
  bool word_break(string s, vector<int>& dp) {
    if (s.empty()) return true;
    int n = s.size();
    if (dp[n] != -1) return dp[n];
    bool ret = false;
    for (int i = 0; i < s.size(); i++) {
      if (dict.count(s.substr(0, i + 1)) && word_break(s.substr(i + 1), dp)) {
        ret = true;
        break;
      }
    }
    dp[n] = ret ? 1 : 0;
    return ret;
  }
};

void test_word_break() {
  Solution_139 s;
  CHECK(s.wordBreak("applepenapple", {"apple", "pen"}), true);
  PRINT_MSG;
}

/*
Given a non-empty string s and a dictionary wordDict containing a list of
non-empty words, add spaces in s to construct a sentence where each word is a
valid dictionary word. Return all such possible sentences.

Note:

The same word in the dictionary may be reused multiple times in the
segmentation. You may assume the dictionary does not contain duplicate words.
Example 1:

Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]
Example 2:

Input:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
Output:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
Explanation: Note that you are allowed to reuse a dictionary word.
Example 3:

Input:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
Output:
[]
*/
/*

class Solution_brute_force {
 public:
  vector<string>  wordBreak(const string s, const vector<string>& wordDict) {

    if(s.empty()) return result;

    for (auto word : wordDict) {
      dict.emplace(word);
    }

    vector<string> current;
    word_break(s, 0, current);
    return result;
  }

 private:
  unordered_set<string> dict;
  vector<string> result;
  void word_break(const string& s, int pos, vector<string>& current) {

    if (pos == s.size()) {
        string res;
        for(int i=0; i< current.size()-1; i++) {
            res += current[i] + " ";
        }
        res += current.back();
        result.push_back(res);
        return;
    }

    for (int i = pos; i < s.size(); i++) {
      string lstr = s.substr(pos, i-pos+1);
       //cout << "substr " << lstr << endl;
      if (dict.count(lstr)){
         // cout << " found " << lstr << endl;
          current.push_back(lstr);
          word_break(s, i+1, current);
          current.pop_back();
      }
    }
  }
};

  We were solving the subproblems repeatedly in the above bruteforce solution.
  for instance :
  "catsanddog"  -->  (1) cat|s|anddog  (2) cats|anddog
   here we solve anddog two times.
   how about we cache the subproblem results.

   dog -> dog
   anddog -> and, dog

  Learnings:
  Recursive Solution gives TLE. But realize that we are solving the
  subproblems repeatedly in the above bruteforce solution.
  for instance :
  "catsanddog"  -->  (1) cat|s|anddog  (2) cats|anddog
   here we solve anddog two times.
   how about we cache the subproblem results.

   dog -> dog
   anddog -> and, dog

*/
class Solution_140 {
 public:
  vector<string> wordBreak(const string s, const vector<string>& wordDict) {
    if (s.empty()) return vector<string>{};

    for (auto word : wordDict) {
      dict.emplace(word);
    }
    return word_break(s);
  }

 private:
  unordered_set<string> dict;
  unordered_map<string, vector<string>> dp;

  vector<string> word_break(string s) {
    if (dp.count(s)) return dp[s];

    vector<string> result;

    if (dict.count(s)) result.push_back(s);

    for (int len = 1; len < s.size(); len++) {
      string lstr = s.substr(0, len);
      if (dict.count(lstr)) {
        auto words = word_break(s.substr(len));
        for (auto word : words) {
          result.push_back(lstr + " " + word);
        }
      }
    }
    dp[s] = result;
    return result;
  }
};

void test_word_break_II() {
  Solution_140 s;
  CHECK(s.wordBreak("catsanddog", {"cat", "cats", "and", "sand", "dog"}),
        {{"cat sand dog"}, {"cats and dog"}});
  PRINT_MSG;
}