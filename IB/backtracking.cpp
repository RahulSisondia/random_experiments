// IB.cpp : This file contains the 'main' function. Program execution begins and
// ends there.
//

#include "EPI16.7_Palindrome_decomposition.h"
#include "N_queens.h"
#include "combinations.h"
#include "permute.h"
#include "subset.h"
#include <iostream>

using namespace std;

template <typename t> void print_matrix(const vector<vector<t>> &matrix) {
  cout << endl << "Matrix : " << endl;
  for (auto i = 0; i < matrix.size(); i++) {
    cout << endl;
    for (auto j = 0; j < matrix[i].size(); j++)
      cout << matrix[i][j] << "  ";
  }
  cout << endl;
}

int main() {
  // vector<int> vect{1, 2, 3};
  // Subset_cp s;
  // print_matrix(s.subsets(vect));

  Combinations c;
  print_matrix(c.combine(3,2));
  Combinations_cp cp;
  print_matrix(cp.combine(3, 2));

  // Permute<string> p;
  // vector<string> s_vect{"A", "B", "C"};
  // print_matrix(p.permute(s_vect));

  //Palindrome_decompositon pd;
  //print_matrix(pd.decompositon("aba"));

  //print_matrix(NQueens(4));

  return 0;
}
