// Prim_Min_Spanning_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Prim_min_spanning_tree.h"
#include <iostream>

/*
4 5
1 2 7
1 4 6
4 2 9
4 3 8
2 3 6

Legend:

4 - vertices
5 - edges
1  2  7  ===>  edge from 1 to 2 with weight 7.

            9
      +--------------+
      |              |
   7  +    6      8  +
1 --- 2 ----- 3 -----4
+					           +
|		    6	           |
+--------------------+

    ||  Min Spanning Tree (19)
    V


   7      6
1 --- 2 ----- 3		   4
+					          +
|		6			          |
+--------------------+
*/

void build_graph() {
  int nodes, edges, x, y;
  long long weight;
  cin >> nodes >> edges;
  adj.resize(nodes);
  for (int i = 0; i < edges; ++i) {
    cin >> x >> y >> weight;
    adj[x].push_back(make_pair(weight, y));
    adj[y].push_back(make_pair(weight, x));
  }

  //int nodes = 4, edges = 5;
  //adj.resize(nodes);

  //adj[0].emplace_back(7,1 );
  //adj[1].emplace_back(7,0);

  //adj[0].emplace_back(6, 3);
  //adj[3].emplace_back(6, 0);

  //adj[3].emplace_back(9, 1);
  //adj[1].emplace_back(9, 3);

  //adj[3].emplace_back(8, 2);
  //adj[2].emplace_back(8, 3);

  //adj[1].emplace_back(6, 2);
  //adj[2].emplace_back(6, 1);

  // Initialize the Visited Array as per the number of vertices
  visited.resize(adj.size());
  fill(visited.begin(), visited.end(), false);
}
int main() {
  // Selecting 1 as the starting node
  build_graph();
  auto minimumCost = prim(1);
  cout << minimumCost << endl;
  return 0;
}