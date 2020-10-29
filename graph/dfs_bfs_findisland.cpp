// FineIsland.cpp : https://www.geeksforgeeks.org/find-number-of-islands/
// Implemented DFS and BFS iterative and recursive versions.
// Count number of disconnected graphs
// Also demonstrate to traverse in the maze.

#include <array>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// A function to check if a given cell (row, col) can be included in DFS
int isSafe(const vector<vector<int>> M, size_t row, size_t col,
           const vector<vector<bool>> &visited) {
  // row number is in range, column number is in range and value is 1
  // and not yet visited
  return (row >= 0) && (row < M.size()) && (col >= 0) && (col < M[0].size()) &&
         (M[row][col] && !visited[row][col]);
}

// A utility function to do DFS for a 2D boolean matrix. It only considers
// the 8 neighbours as adjacent vertices
void DFS_util(const vector<vector<int>> M, int row, int col,
              vector<vector<bool>> &visited, int &count) {
  // These arrays are used to get row and column numbers of 8 neighbours
  // of a given cell
  constexpr static int rowNbr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  constexpr static int colNbr[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  // Mark this cell as visited
  visited[row][col] = true;
  count++;
  // Recur for all connected neighbours
  for (int k = 0; k < 8; ++k)
    if (isSafe(M, row + rowNbr[k], col + colNbr[k], visited)) {
      DFS_util(M, row + rowNbr[k], col + colNbr[k], visited, count);
    }
}

void DFS_util_stk(const vector<vector<int>> M, int row, int col,
                  vector<vector<bool>> &visited, int &count) {
  // These arrays are used to get row and column numbers of 8 neighbours
  // of a given cell
  constexpr static int rowNbr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  constexpr static int colNbr[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  vector<std::pair<int, int>> stk;
  stk.emplace_back(row, col);
  // Mark this cell as visited
  visited[row][col] = true;
  int temp_row, temp_col;
  while (!stk.empty()) {
    auto ret = stk.back();
    stk.pop_back();
    count++;
    for (int k = 0; k < 8; ++k) {
      temp_row = ret.first + rowNbr[k];
      temp_col = ret.second + colNbr[k];
      if (isSafe(M, temp_row, temp_col, visited)) {
        stk.emplace_back(temp_row, temp_col);
        visited[temp_row][temp_col] = true;
      }
    }
  }
}

void BFS_util_que(const vector<vector<int>> M, int row, int col,
                  vector<vector<bool>> &visited, int &count) {
  // These arrays are used to get row and column numbers of 8 neighbours
  // of a given cell
  constexpr static int rowNbr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  constexpr static int colNbr[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  queue<std::pair<int, int>> q;
  q.emplace(row, col);
  // Mark this cell as visited
  visited[row][col] = true;
  int temp_row, temp_col;
  while (!q.empty()) {
    auto ret = q.front();
    q.pop();
    count++;
    for (int k = 0; k < 8; ++k) {
      temp_row = ret.first + rowNbr[k];
      temp_col = ret.second + colNbr[k];
      if (isSafe(M, temp_row, temp_col, visited)) {
        q.emplace(temp_row, temp_col);
        visited[temp_row][temp_col] = true;
      }
    }
  }
}

// The main function that returns count of islands in a given boolean
// 2D matrix
int countIslands(vector<vector<int>> M) {
  // Make a bool array to mark visited cells.
  // Initially all cells are unvisited
  vector<vector<bool>> visited(M.size(), vector<bool>(M[0].size(), 0));

  // Initialize count as 0 and travese through the all cells of
  // given matrix
  int count = 0, max_count = std::numeric_limits<int>::min();
  int island_number = 0;
  for (int i = 0; i < M.size(); ++i)
    for (int j = 0; j < M[0].size(); ++j)
      if (M[i][j] && !visited[i][j])  // If a cell with value 1 is not
      {                               // visited yet, then new island found
        // Visit all cells in this island using DFS recursively
        // DFS_util(M, i, j, visited, count);

        // Visit all cells in this island using DFS iteratively
        // DFS_util_stk(M, i, j, visited, count);

        // Visit all cells in this island using BFS iteratively
        BFS_util_que(M, i, j, visited, count);
        if (max_count < count) max_count = count;
        count = 0;
        ++island_number;  // and increment island count
      }
  std::cout << "Max Island size : " << max_count << "\n";
  return island_number;
}

// Driver program to test above function
int main() {
  vector<vector<int>> M{{1, 1, 0, 0, 0},
                        {0, 1, 0, 1, 1},
                        {1, 0, 0, 1, 1},
                        {0, 0, 0, 1, 0},
                        {1, 0, 1, 0, 1}};
  printf("Number of islands is: %d\n", countIslands(M));
  return 0;
}
