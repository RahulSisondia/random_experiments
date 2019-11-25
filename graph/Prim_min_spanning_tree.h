#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>

using namespace std;

// Weight, Neighbour
typedef pair<long long, int> PII;

vector<bool> visisted;

// Adjancy list
vector<vector<PII>> adj;

long long prim(int x) {
  priority_queue<PII, vector<PII>, greater<PII>> Q;
  int y;
  long long minimumCost = 0;
  PII p;
  Q.emplace(0, 1);
  while (!Q.empty()) {
    // Select the edge with minimum weight
    p = Q.top();
    Q.pop();
    x = p.second;
    // Checking for cycle
    if (visisted[x] == true)
      continue;
    minimumCost += p.first;
    visisted[x] = true;
    for (int i = 0; i < adj[x].size(); ++i) {
      y = adj[x][i].second;
      if (visisted[y] == false)
        Q.push(adj[x][i]);
    }
  }
  return minimumCost;
}
