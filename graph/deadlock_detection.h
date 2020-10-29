#pragma once
#include "graph_util.h"

vector<Vertex> build_graph(vector<Vertex> v) {
  /*
   A  ---> B  ---> C ---> D
                   ^      |
                   |      |
                   + <----+
  */
  v[0].add_edge(&v[1]);
  v[1].add_edge(&v[2]);
  v[2].add_edge(&v[3]);
  // v[3].add_edge(&v[1]);  // Cycle detection test
  v[4].add_edge(&v[5]);
  v[5].add_edge(&v[1]);
  v[1].add_edge(&v[4]);  // Cycle detection test
  return v;
}

/*
  This is iterative DFS program based on the following approach.
  It does the two things -
  1. it detects the cycle
  2. Prints the nodes in the topological order as well.

  https://stackoverflow.com/questions/46506077/how-to-detect-cycles-in-a-directed-graph-using-the-iterative-version-of-dfs
  One option is to push each node twice to the stack along the information if
  you're entering or exiting it. When you pop a node from stack you check if
  you're entering or exiting. In case of enter color it gray, push it to stack
  again and advance to neighbors. In case of exit just color it black.
*/

bool isdeadlock(vector<Vertex> graph) {
  enum state { ENTER, EXIT };

  // Notice, that we have taken the vertex pointer.
  // Since, we need to update the vertices color.
  stack<pair<Vertex*, state>> s;
  // Vertex& v = graph.front();
  vector<string> topological;
  for (auto& c : graph) {
    if (c.indegree == 0) s.emplace(&c, ENTER);
  }

  while (!s.empty()) {
    auto v = s.top();
    s.pop();
    if (v.second == EXIT) {
      v.first->color = Vertex::Color::Black;
      cout << "EXIT : " << v.first->node << endl;
      topological.emplace_back(v.first->node);
    } else {
      cout << "ENTER : " << v.first->node << endl;
      v.first->color = Vertex::Color::Gray;
      s.emplace(v.first, EXIT);
      for (auto edge : v.first->edges) {
        if (edge->color == Vertex::Color::White) {
          s.emplace(edge, ENTER);
        } else if (edge->color == Vertex::Color::Gray) {
          cout << "Found cycle : " << edge->node << endl;
          return true;
        }
      }
    }
  }
  cout << "No Cycle found so here is the topological order " << endl;
  std::for_each(topological.begin(), topological.end(),
                [](auto a) { cout << a << endl; });
  return false;
}


void test_deadlock_detection() {
  Vertex a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
  vector<Vertex> vs{a, b, c, d, e, f};
  auto g = build_graph(vs);
  print_graph(g);
  cout << isdeadlock(g);
}