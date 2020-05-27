#pragma once
/*
Problem from PRAMP. need to find out the minumum path from root to leaf in the
ternary tree/graph.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int cost;
  vector<Node *> children;
  Node *parent;
  void set(int c, vector<Node *> chldrn, Node *parents) {
    cost = c;
    children = chldrn;
    parent = parents;
  }
};

void getCheapestCost(Node *rootNode, int current_sum, int &min) {
  if (rootNode == nullptr) {
    return;
  }

  if (rootNode->children.size() == 0) {
    min = std::min(min, current_sum);
    return;
  }
  cout << "rootNode " << rootNode->cost << "  current_sum " << current_sum
       << endl;
  for (int i = 0; i < rootNode->children.size(); i++) {
    getCheapestCost(rootNode->children[i],
                    rootNode->children[i]->cost + current_sum, min);
  }
  return;
}

int getCheapestCost(Node *rootNode) {
  int min = numeric_limits<int>::max();
  getCheapestCost(rootNode, rootNode->cost, min);
  return min;
}

void test_path_sum() {
  Node root, node5, node6, node3, node4, node1, node10, node8, node_1, node_2;
  root.set(0, {&node5, &node3, &node6}, nullptr);
  node5.set(5, {&node4}, &root);
  node3.set(3, {&node10}, &root);
  node6.set(6, {&node1, &node8}, &root);
  node1.set(1, {&node_1}, &node6);
  node4.set(4, {}, &node5);
  node10.set(10, {}, &node3);
  node8.set(8, {}, &node6);
  node_1.set(-1, {&node_2}, &node1);
  node_2.set(-2, {}, &node_1);
  cout << getCheapestCost(&root);
}