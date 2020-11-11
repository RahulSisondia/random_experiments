#include "../my_util.h"

/*
On the first row, we write a 0. Now in every subsequent row, we look at the
previous row and replace each occurrence of 0 with 01, and each occurrence of 1
with 10.

Given row N and index K, return the K-th indexed symbol in row N. (The values of
K are 1-indexed.) (1 indexed).

Examples:
Input: N = 1, K = 1
Output: 0

Input: N = 2, K = 1
Output: 0

Input: N = 2, K = 2
Output: 1

Input: N = 4, K = 5
Output: 1

Explanation:
row 1: 0
row 2: 01
row 3: 0110
row 4: 01101001

*/
class Solution_779 {
 public:
  int kthGrammar(int N, int K) {
    if (N == 1 || K == 1) return 0;
    int mid = pow(2, N - 1) / 2;
    if (K <= mid) {
      return kthGrammar(N - 1, K);
    } else {
      return !kthGrammar(N - 1, K - mid);
    }
  }
};

void test_kth_symbol() {
  Solution_779 s;
  CHECK(s.kthGrammar(4, 5), 1);
}