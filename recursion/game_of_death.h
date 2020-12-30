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
/*
There are n people standing in a circle (numbered clockwise 1 to n) waiting to
be executed. The counting begins at point 1 in the circle and proceeds around
the circle in a fixed direction (clockwise). In each step, a certain number of
people are skipped and the next person is executed. The elimination proceeds
around the circle (which is becoming smaller and smaller as the executed people
are removed), until only the last person remains, who is given freedom. Given
the total number of persons n and a number k which indicates that k-1 persons
are skipped and kth person is killed in circle. The task is to choose the place
in the initial circle so that you are the last one remaining and so survive.
Consider if n = 5 and k = 2, then the safe position is 3.
Firstly, the person at position 2 is killed, then person at position 4 is
killed, then person at position 1 is killed. Finally, the person at position 5
is killed. So the person at position 3 survives.
*/
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