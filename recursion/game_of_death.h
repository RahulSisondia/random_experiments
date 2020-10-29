#include "../my_util.h"

void josephus_problem_util(vector<int> vect, int k, int index, int& res) {
  if (vect.size() == 1) {
    res = vect[0];
    return;
  }

  index = (index + k) % (vect.size());
  vect.erase(vect.begin() + index);
  josephus_problem_util(vect, k, index, res);
  // Cool, there is no induction code required here to make above hypothesis
  // work. Recuding the size of array is sufficient.
}

int josephus_problem(int N, int k) {
  int index = 0;
  vector<int> vect;
  int res = 0;
  // Give people permanent number in the initial circle.
  for (int i = 0; i < N; i++) {
    vect.push_back(i + 1);
  }
  // The index in the array will be one less.
  josephus_problem_util(vect, --k, index, res);
  return res;
}

void test_game_of_death() {
  CHECK(josephus_problem(5, 2), 3);
  PRINT_MSG;
}