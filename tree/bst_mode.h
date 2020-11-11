#include "tree_util.h"

/*
https://stackoverflow.com/questions/17630434/most-frequent-element-in-a-binary-search-tree
Ex: Given the following tree...

        2
       / \
      1   2
return 2.

Ex: Given the following tree...

         7
        / \
      4     9
     / \   / \
    1   4 8   9
               \
                9
return 9.
*/

void BST_mode_util(shared_ptr<Node> root, shared_ptr<Node> prev, int &count,
                   int &max_count, int &result_node) {
  if (root == nullptr) return;
  BST_mode_util(root->left, prev, count, max_count, result_node);
  if (prev != nullptr && prev->data == root->data) {
    count++;
  } else {
    prev = root;
    count = 1;
  }
  if (count > max_count) {
    result_node = root->data;
    max_count = count;
  }

  BST_mode_util(root->right, prev, count, max_count, result_node);
}

pair<int, int> BST_mode(shared_ptr<Node> root) {
  int max_count = -1;
  shared_ptr<Node> prev = nullptr;
  int count = 0;
  int result_node;
  BST_mode_util(root, prev, count, max_count, result_node);
  return {result_node, max_count};
}

void test_BST_mode() {
  shared_ptr<Node> root = make_shared<Node>(7);
  root->left = make_shared<Node>(4);
  root->left->left = make_shared<Node>(1);
  root->left->right = make_shared<Node>(4);
  root->right = make_shared<Node>(9);
  root->right->left = make_shared<Node>(8);
  root->right->right = make_shared<Node>(9);
  root->right->right->right = make_shared<Node>(9);
  CHECK(BST_mode(root), pair{9, 3});
  PRINT_MSG;
}