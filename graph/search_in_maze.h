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
  auto no_parent = std::pair<int, int>{INT_MAX, INT_MAX};
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
      auto node = std::pair<int, int>{row, col};
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
  // source [4,0]
  // target [0,4]
  /*clang-format on */ 
 
  // auto result = search_in_maze_bfs(maze);
  // for(auto p: result) {
  //   cout << "{" << p.first << ", " << p.second<< "},";
  // }
  CHECK(search_in_maze_dfs(maze), {{4, 0},{4, 1},{3, 1},{3, 2},{2, 2},{1, 2},{0, 2},{0, 3},{0, 4}});
  CHECK(search_in_maze_bfs(maze), {{4, 0},{4, 1},{3, 1},{3, 2},{2, 2},{1, 2},{0, 2},{0, 3},{0, 4}});
  PRINT_MSG;
}

/*
Shortest Cell Path
In a given grid of 0s and 1s, we have some starting row and column sr, sc and a target row and column tr, tc.
Return the length of the shortest path from sr, sc to tr, tc that walks along 1 values only.

Each location in the path, including the start and the end, must be a 1. Each subsequent location in 
the path must be 4-directionally adjacent to the previous location.

It is guaranteed that grid[sr][sc] = grid[tr][tc] = 1, and the starting and target positions are different.

If the task is impossible, return -1.

Examples:

input:
grid = [[1, 1, 1, 1], [0, 0, 0, 1], [1, 1, 1, 1]]
sr = 0, sc = 0, tr = 2, tc = 0
output: 8
(The lines below represent this grid:)
1111
0001
1111
*/

bool is_valid(const vector<vector<int>>& grid, const set<pair<int,int>>& visited, int row, int col) {
  if(row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || grid[row][col] == 0)
    return false; 
  if(visited.find({row, col}) != visited.end()) 
    return false;
  return true;
}

int shortestCellPath(const vector<vector<int>>& grid, int sr, int sc, int tr, int tc)
{
   struct Node {
    pair<int, int> p; 
    int count;
   };
   queue<Node> q; 
   set<pair<int,int>> visited; 
   pair<int, int> source = {sr, sc};
   pair<int, int> target = {tr, tc};
   vector<pair<int,int>> positions = {{0,-1}, {0,+1}, {-1,0}, {+1,0}};
   int path =-1;
   q.push({source, 0}); 
   visited.emplace(source);
   while(!q.empty()) {
     auto node = q.front(); 
     if(node.p == target) {
       path = node.count;
       break;
     }
     q.pop(); // Remove the node
     for(auto pos : positions) {
       int row = pos.first + node.p.first; 
       int col = pos.second + node.p.second; 
       pair<int, int> pr = {row,col};
       if(is_valid(grid, visited, row, col)) {
         q.push({pr, node.count+1});
         visited.emplace(pr);
       }
     }
   }
  return path;
}


void test_count_shortestCellPath() {
  /*
  ->[1], 1, 1, 1],
    [0, 0, 0, 1], 
  ->[1], 1, 1, 1]
  */
  CHECK(shortestCellPath({{1, 1, 1, 1}, {0, 0, 0, 1}, {1, 1, 1, 1}}, 0,0,2,0),8);
    /*
  ->[1], 1, 1, 1],
    [0, 0, 0, 1], 
  ->[1], 0, 1, 1]
  */
  CHECK(shortestCellPath({{1, 1, 1, 1}, {0, 0, 0, 1}, {1, 0, 1, 1}}, 0,0,2,0), -1);
  PRINT_MSG;
}