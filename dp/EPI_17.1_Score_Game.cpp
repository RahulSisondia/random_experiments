// EPI_17.1_Score_Game.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

void display(vector<int> p) {
  for (auto i : p) std::cout << i << " ";
  std::cout << endl;
}

// Printing the combinations is similar to
// https://www.geeksforgeeks.org/perfect-sum-problem-print-subsets-given-sum/
// https://ide.geeksforgeeks.org/cXJFjbuu9l
// with one subtle differece. In the problem above we don't print the repeating
// element while in our case we do.
void numOfCombinationsRec(const vector<vector<int>>& matrix,
                          const vector<int>& playscore, vector<int>& vect,
                          int i, int score) {
  if (i < 0) return;

  if (score == 0) {
    display(vect);
    return;
  }

  // If given sum can be achieved after ignoring current element.
  if (matrix[i][score]) {
    // Create a new vector to store path because it will be a different path
    vector<int> new_vect = vect;
    numOfCombinationsRec(matrix, playscore, new_vect, i - 1, score);
  }

  // If given sum can be achieved after considering current element.
  if (score >= playscore[i] && matrix[i][score - playscore[i]]) {
    vect.push_back(playscore[i]);
    numOfCombinationsRec(matrix, playscore, vect, i, score - playscore[i]);
  }
}

// Here we have used  2D array. There is another solution with 1D array as
// following
// https://www.geeksforgeeks.org/count-number-ways-reach-given-score-game/
//
int numOfCombinations(int score, const vector<int>& play_score) {
  vector<vector<int>> matrix(play_score.size(), vector<int>(score + 1, 0));
  for (int i = 0; i < matrix.size(); i++) {
    matrix[i][0] = 1;
    for (int j = 1; j < matrix[0].size(); j++) {
      int wo_play_score = 0, wth_play_score = 0;
      wo_play_score = (i > 0) ? matrix[i - 1][j] : 0;
      wth_play_score = (j >= play_score[i]) ? matrix[i][j - play_score[i]] : 0;
      matrix[i][j] = wo_play_score + wth_play_score;
    }
  }
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) cout << matrix[i][j] << " ";
    cout << endl;
  }
  cout << "Combinations \n";
  vector<int> p;
  numOfCombinationsRec(matrix, play_score, p, play_score.size() - 1, score);
  return matrix.back().back();
}

int main() {
  cout << "Total combinations : " << numOfCombinations(12, {2, 3, 7});
  return 1;
}
