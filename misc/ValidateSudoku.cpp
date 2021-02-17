// ValidateSudoku.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <iostream>
using namespace std;

bool isValidSudoku(vector<vector<char>>& board) {
	vector<short> col(9, 0);
	vector<short> block(9, 0);
	vector<short> row(9, 0);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != '.') {
				int idx = 1 << (board[i][j] - '0');
				if (row[i] & idx || col[j] & idx || block[i / 3 * 3 + j / 3] & idx)
					return false;
				row[i] |= idx;
				col[j] |= idx;
				block[i / 3 * 3 + j / 3] |= idx;
			}
		}
	}
	return true;
}


int main()
{
  vector<vector<char>> matrix = {
      {'5', '3', '4', '6', '7', '8', '9', '1', '2'},
	  {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
      {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
	  {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
      {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
      {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
      {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
	  {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
      {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

  std::cout << isValidSudoku(matrix);

  return 0;
}

