#include "../my_util.h"

// https://leetcode.com/problems/k-th-symbol-in-grammar/
class Solution_779 {
 public:
  int kthGrammar(int N, int k) {
    if (N == 1) return 0;

    int mid = pow(2, N - 1) / 2;

    if (k <= mid) {
      return kthGrammar(N - 1, k);
    } else {
      return !(kthGrammar(N - 1, k - mid));
    }
  }
};

void kth_grammar_779() {
  Solution_779 s;
  CHECK(s.kthGrammar(2, 2), 1);
  CHECK(s.kthGrammar(1, 1), 0);
  CHECK(s.kthGrammar(3, 4), 0);
  CHECK(s.kthGrammar(30, pow(2, 29)), 1);
  PASSED_MSG;
}