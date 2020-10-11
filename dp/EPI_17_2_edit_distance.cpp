// EPI_17,2_edit_distance.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_matrix(vector<vector<int>> matrix) {
  cout << endl << "Matrix : " << endl;
  for (int i = 0; i < matrix.size(); i++) {
    cout << endl;
    for (int j = 0; j < matrix[0].size(); j++) cout << matrix[i][j] << "  ";
  }
  cout << endl;
}

int edit_distance(const string &str1, const string &str2) {
  vector<vector<int>> matrix(str1.size(), vector<int>(str2.size(), 0));
  if (str1.empty()) return str2.size();
  if (str2.empty()) return str1.size();
  /*
     for i , j = 1
     M[i][j] = min( M[i-1][j-1], M[i][j-1], M[i-1][j-1]) + if (s1[i] != s2[j]) 1
   */
  if (str1[0] != str2[0]) matrix[0][0] = 1;

  for (int i = 1; i < str1.size(); i++) {
    matrix[i][0] = matrix[i - 1][0];
    if (str1[i] != str2[0]) {
      matrix[i][0] += 1;
    }
  }

  for (int j = 1; j < str2.size(); j++) {
    matrix[0][j] = matrix[0][j - 1];
    if (str1[j] != str2[0]) {
      matrix[0][j] += 1;
    }
  }

  for (int i = 1; i < str1.size(); i++)
    for (int j = 1; j < str2.size(); j++) {
      matrix[i][j] =
          min({matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1]});
      if (str1[i] != str2[j]) matrix[i][j] += 1;
    }
  print_matrix(matrix);
  return matrix.back().back();
}

int editDistDP(string str1, string str2, const int m, const int n) {
  // Create a table to store results of subproblems
  /*int **dp = new int*[m+1];
  for (auto i=0; i<m+1; i++)
  {
    dp[i]= new int[n + 1];
  }*/
  std::vector<std::vector<int>> dp(m + 1, vector<int>(n + 1));

  // Fill d[][] in bottom up manner
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      // If first string is empty, only option is to
      // isnert all characters of second string
      if (i == 0) dp[i][j] = j;  // Min. operations = j

      // If second string is empty, only option is to
      // remove all characters of second string
      else if (j == 0)
        dp[i][j] = i;  // Min. operations = i

      // If last characters are same, ignore last char
      // and recur for remaining string
      else if (str1[i - 1] == str2[j - 1])
        dp[i][j] = dp[i - 1][j - 1];

      // If last character are different, consider all
      // possibilities and find minimum
      else
        dp[i][j] = 1 + min({dp[i][j - 1],        // Insert
                            dp[i - 1][j],        // Remove
                            dp[i - 1][j - 1]});  // Replace
    }
  }

  return dp[m][n];
}

int main() {
  cout << edit_distance("Sundays", "saturday") << endl;
  cout << edit_distance("", "saturday") << endl;
  cout << edit_distance("Sundays", "") << endl;
  return 0;
}
