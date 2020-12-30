#include "../my_util.h"
/*
 https://www.techiedelight.com/single-source-shortest-paths-dijkstras-algorithm/
 This implementation is similar to the above except some minor diffs:
  - Represented Adjancency list differently.
  - Not using the distanc[] vector and relaxation, instead emulating the BFS and
    relying on BFS
 - (https://youtu.be/sD0lLYlGCJE)
*/
using P = pair<int, int>;  // Conecting Vertex, Weight
struct Edge {
  int parent;  // source
  int node;    // dest
  int weight;  // weight
};

map<int, P> shortest_path(std::vector<vector<P>> graph, int source) {
  map<int, P> result;  // node, {parent, weight}
  std::set<int> visited;
  priority_queue<Edge, vector<Edge>, function<bool(Edge, Edge)>> min_heap(
      [](const auto &e1, const auto &e2) { return e1.weight >= e2.weight; });
  min_heap.push({-1, source, 0});
  result[source] = {-1, 0};
  while (min_heap.empty() == false) {
    auto edge = min_heap.top();
    min_heap.pop();
    // if we need to find path specific to a target then check and break here
    if (visited.find(edge.node) != visited.end()) continue;
    // cout << edge.node << endl;
    for (auto nghbr : graph[edge.node]) {
      if (visited.find(nghbr.first) == visited.end()) {
        min_heap.push({edge.node, nghbr.first, nghbr.second + edge.weight});
      }
    }
    visited.emplace(edge.node);
    result[edge.node] = {edge.parent, edge.weight};
  }
  return result;
}

string path(map<int, P> results, int node) {
  if (results.find(node) == results.end()) return "";
  string str = path(results, results[node].first);
  if (str.empty())
    str += to_string(node);
  else
    str += "->" + to_string(node);
  return str;
}

void test_dijkstra() {
  /* clang-format off */
  /*                          7
                           +---------+
         10        2       V   9      |
     0 -------> 1 -------> 2 -------> 3
     |         ^ |         ^          ^
     |         | |         |8         | 2
     |         | |  4      +---------+
     |         | +------------+      |
     |3        +-----------+  |      |
     |              1      |  V      |
     +---------------------> 4 ------+
  */
  std::vector<vector<P>> graph = {
    {{1, 10}, {4, 3}},
    {{4, 4}, {2, 2}},
    {{3, 9}},
    {{2,7}},
    {{1, 1}, {2, 8}, {3, 2}}
  };

   map<int, P> results;
   results = shortest_path(graph, 0);
   assert(results[1].second == 4);
   assert(results[2].second == 6);
   assert(results[3].second == 5);
   assert(results[4].second == 3);
   assert(path(results, 1) == "0->4->1");
   assert(path(results, 2) == "0->4->1->2");
   assert(path(results, 3) == "0->4->3");
   assert(path(results, 4) == "0->4");
   PRINT_MSG;
  /* clang-format on */
}
