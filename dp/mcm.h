/*
 * Matrix Chain Multiplication (mcm)
 */

#include "../my_util.h"

/*
 complexity is exponential i.e. Ω(4^n/n^3/2)
*/
int mcm_rec(vector<int> dims, int i, int j) {
  // i cannot be greater than j of course.
  // if i == j means same dimension which invalid case as well.
  if (i >= j) return 0;
  int res = numeric_limits<int>::max();
  for (int k = i; k < j; k++) {
    //  Enable to debug
    // cout << "i: " << i << " j: " << j << " k: " << k << endl;
    int temp_res =
        mcm_rec(dims, i, k) /* cost of multiplying matrices from i to k */
        +
        mcm_rec(dims, k + 1, j) /* cost of multiplying matrices from k+1 to j */
        + (dims[i - 1] * dims[k] *
           dims[j]) /* cost of multiplying the previous two matrices  */;
    /* Keep track of the minimal cost so far */
    res = min(res, temp_res);
  }
  return res;
}

/**
  dp: to keep track of cost
  pmat : to keep track of position of k so that we can pring where to put
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
    // if (i == 1 && j == 4) {
    //   print_matrix(pmat);
    //   print_matrix(dp);
    // }
  }
  return res;
}
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
  // Passing both index to check palindrome is much easier than calculting the
  // inclusive length
  // if (i == j || is_palindrome(str.substr(i, j - i + 1)) == true) return 0;

  if (i == j || is_palindrome(str, i, j) == true) return 0;

  int res = numeric_limits<int>::max();
  for (int k = i; k <= j - 1; k++) {
    int temp_res =
        min_palindromic_partitioning_rec(str, i, k) /* left partition */
        + 1 /* cost of cutting left and right partitions */
        + min_palindromic_partitioning_rec(str, k + 1,

                                           j) /* right partition */;
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