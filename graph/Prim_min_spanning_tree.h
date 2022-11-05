#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <string>

using namespace std;

// Weight, Neighbour
typedef pair<long long, int> PII;

vector<bool> visited;

// Adjancy list
vector<vector<PII>> adj;
/*
  Returns the cost of the minimul spanning tree.
*/
long long prim(int x) {
  // Min heap, that compares the weights first if they are equal,
  // then it compares the neighbour.
  priority_queue<PII, vector<PII>, greater<PII>> Q;
  string path;
  string weights;
  int y;
  long long minimumCost = 0;
  int numVisited = 0;
  PII p;
  Q.emplace(0, x);  // Initial weight is 0 to reach vertex 1.
  while (!Q.empty()) {
    // Return the edge with minimum weight
    p = Q.top();
    Q.pop();
    x = p.second;
    // Checking for cycle
    if (visited[x] == true) continue;
    minimumCost += p.first;
    numVisited++;
    path += std::to_string(p.second) + "  ";

    visited[x] = true;
    for (int i = 0; i < adj[x].size(); ++i) {
      y = adj[x][i].second;
      if (visited[y] == false) Q.push(adj[x][i]);
    }
  }
  if (numVisited != adj.size()) throw "There is forest";
  return minimumCost;
}
