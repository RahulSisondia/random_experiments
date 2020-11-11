#pragma once
/*
 EPI 19.1 Search in a Maze.
 - Learn to print paths. Using DFS and BFS based algorithms.
 it is much more natuaral to use DFS to find the paths since the implemention is
 easier. We don't need additional DS unlike BFS. Have a look:
- Learn to traverse in the matrix with the given directions.
- Note the BFS gives us the shortest path. If it is asked to find the shortest
  path then it makes sense to use BFS based traversal.
*/
#include "../my_util.h"

bool is_valid(vector<vector<bool>>& maze, int row, int col,
              vector<vector<bool>>& visited) {
  if (row < 0 || row >= maze.size() || col < 0 || col >= maze[0].size() ||
      visited[row][col]) {
    return false;
  }
  return true;
}

bool search_in_maze_dfs_util(vector<vector<bool>>& maze,
                             vector<pair<int, int>>& path,
                             pair<int, int> source, pair<int, int> target,
                             vector<vector<bool>>& visited) {
  if (source == target) return true;
  visited[source.first][source.second] = true;
  static const vector<pair<int, int>> directions{
      {-1, 0}, {+1, 0}, {0, -1}, {0, +1}};
  for (auto dir : directions) {
    auto row = source.first + dir.first;
    auto col = source.second + dir.second;
    if (is_valid(maze, row, col, visited)) {
      path.push_back({row, col});
      if (search_in_maze_dfs_util(maze, path, {row, col}, target, visited))
        return true;
      path.pop_back();  // Backtrack the unsuccessfull path.
    }
  }
  return false;
}

vector<pair<int, int>> search_in_maze_dfs(vector<vector<bool>> maze) {
  vector<pair<int, int>> path;
  // Consider the inaccessible paths in the maze as visited.
  vector<vector<bool>> visited = maze;
  pair<int, int> source = {4, 0};
  pair<int, int> target = {0, 4};
  path.push_back(source);  // We have to push the source node first.
  if (search_in_maze_dfs_util(maze, path, source, target, visited) == false)
    path.clear();
  return path;
}

/*
 Similar to Dijksatra's Algorithm. We need to take to additional datastructure
 to track the parent node.
*/
vector<pair<int, int>> search_in_maze_bfs(vector<vector<bool>> maze) {
  using P = pair<int, int>;
  vector<P> path;
  vector<vector<bool>> visited = maze;
  P source = {4, 0};
  P target = {0, 4};
  static const vector<pair<int, int>> directions{
      {-1, 0}, {+1, 0}, {0, -1}, {0, +1}};
  map<P, P> parent;
  queue<P> q;
  q.push(source);
  visited[source.first][source.second] = true;
  auto no_parent = pair{INT_MAX, INT_MAX};
  parent.emplace(source, no_parent);
  bool target_found = false;
  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    if (p == target) {
      target_found = true;
      break;
    }
    for (auto d : directions) {
      auto row = p.first + d.first;
      auto col = p.second + d.second;
      auto node = pair{row, col};
      if (is_valid(maze, row, col, visited)) {
        visited[row][col] = true;
        parent.emplace(node, p);
        q.emplace(node);
      }
    }
  }
  if (target_found) {
    while (parent[target] != no_parent) {
      path.push_back(target);
      target = parent[target];
    }
    // Add source vertex
    path.push_back(target);
    // We got the paths from target to source. Reverse it.
    reverse(path.begin(), path.end());
  }
  return path;
}

void test_search_in_maze() {
  /* clang-format off */
  vector<vector<bool>> maze =
  {
   {0, 1, 0, 0, 0},
   {0, 1, 0, 0, 1},
   {0, 1, 0, 0, 0}, 
   {1, 0, 0, 1, 0}, 
   {0, 0, 0, 0, 0} 
  };
  /*clang-format on */ 
 
  // auto result = search_in_maze_bfs(maze);
  // for(auto p: result) {
  //   cout << "{" << p.first << ", " << p.second<< "},";
  // }
  CHECK(search_in_maze_dfs(maze), {{4, 0},{4, 1},{3, 1},{3, 2},{2, 2},{1, 2},{0, 2},{0, 3},{0, 4}});
  CHECK(search_in_maze_bfs(maze), {{4, 0},{4, 1},{3, 1},{3, 2},{2, 2},{1, 2},{0, 2},{0, 3},{0, 4}});
  PRINT_MSG;
}


