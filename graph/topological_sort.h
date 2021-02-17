#include "../my_util.h"
/*
 This is Topological sort using iterative approach.
*/
vector<int> topological_sort_indegree(vector<vector<int>> graph) {
  vector<int> result;
  vector<int> indegree(graph.size(), 0);

  // If a node has an incomming edge then increase its indegree count.
  for (int i = 0; i < graph.size(); i++) {
    for (int j = 0; j < graph[i].size(); j++) {
      indegree[graph[i][j]]++;
    }
  }
  vector<int> set;
  // Start by adding all nodes with indegree 0 to the list.
  for (int i = 0; i < indegree.size(); i++) {
    if (indegree[i] == 0) set.push_back(i);
  }

  while (!set.empty()) {
    int node = set.back();
    set.pop_back();
    result.push_back(node);
    for (int i = 0; i < graph[node].size(); i++) {
      indegree[graph[node][i]]--;
      if (indegree[graph[node][i]] == 0) set.push_back(graph[node][i]);
    }
  }
  return result;
}

void dfs(vector<vector<int>>& graph, int node, unordered_set<int>& visited,
         vector<int>& result) {
  visited.emplace(node);
  // Visit all children of the current node.
  for (int i = 0; i < graph[node].size(); i++) {
    if (visited.find(graph[node][i]) == visited.end())
      dfs(graph, graph[node][i], visited, result);
  }
  // Once we processed all children then add the current node as result.
  result.push_back(node); 
}

vector<int> topological_sort_dfs(vector<vector<int>> graph) {
  vector<int> result;
  unordered_set<int> visited;
  // Visit all nodes in the gaph
  for (int i = 0; i < graph.size(); i++) {
    if (visited.find(i) == visited.end()) dfs(graph, i, visited, result);
  }
  reverse(result.begin(), result.end());
  return result;
}

void test_topological_sort() {
  /* clang-format off */  
  /*
      5 -----> 1 --+--> 2
               ^   |
               |   +---> 4 <----------- 3
               |   |                    +
               |   +--------------+     |
               |                  |     |
      8--------+------> 0--+      V     |
                        ^  +----> 6     |
                        |               |
                        |               |
                        +---------------+
      7
  */
  /* Adjacency list */
  vector<vector<int>> graph = {{6}, 
                               {2, 4, 6},
                               {},
                               {0, 4}, 
                               {},
                               {1},
                               {},
                               {}, 
                               {1, 0}};
  /* clang-format off */
  // PRINT_VECTOR(topological_sort_indegree(graph));
  CHECK(topological_sort_indegree(graph), {8, 7, 5, 1, 2, 3, 4, 0, 6});
  CHECK(topological_sort_dfs(graph), {8, 7, 5 ,3, 1, 4, 2, 0, 6 });
  PRINT_MSG;
}