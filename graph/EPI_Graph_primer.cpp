// EPI_Graph_primer.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "19.4_Deadlock_detection.h"
#include "Team_Game.h"

void print_matrix(vector<vector<int>> matrix) {
  cout << endl << "Matrix : " << endl;
  for (int i = 0; i < matrix.size(); i++) {
    cout << endl;
    for (int j = 0; j < matrix[0].size(); j++) cout << matrix[i][j] << "  ";
  }
  cout << endl;
}

int main() {
  /*vector<Match_result> mr{
      {"A", "B"}, {"B", "C"}, {"C", "A"}, {"D", "E"}, {"A", "D"}};
  cout << can_team_A_beat_team_B(mr, "C", "B") << endl;
  cout << can_team_A_beat_team_B(mr, "B", "A") << endl;
  cout << can_team_A_beat_team_B(mr, "A", "D") << endl;
  cout << can_team_A_beat_team_B(mr, "A", "E") << endl;
  cout << can_team_A_beat_team_B(mr, "B", "D") << endl;
  cout << can_team_A_beat_team_B(mr, "E", "C") << endl;*/

  dl::Vertex a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
  vector<dl::Vertex> vs{a, b, c, d, e, f};
  auto g = dl::build_graph(vs);
  dl::print_graph(g);
  cout << dl::isdeadlock(g);
  return 0;
}
