#pragma once
#include "tree_util.h"

struct st {
  int height = 0;
  int diameter = 0;
};
/*
https://www.techiedelight.com/find-diameter-of-a-binary-tree/
*/
st diameter(shared_ptr<Node> root) {
  if (root == nullptr) return {};
  auto lst = diameter(root->left);
  auto rst = diameter(root->right);
  st result;
  result.height = max(lst.height, rst.height) + 1;
  result.diameter =
      max({lst.height + rst.height + 1, lst.diameter, rst.diameter});
  return result;
}

void test_diameter() {
  {
    /*
          1
         / \
       2     3
        \   / \
         4 5   6
          / \    \
         7  8     9

    */
    shared_ptr<Node> root = make_shared<Node>(1);
    root->left = make_shared<Node>(2);
    root->right = make_shared<Node>(3);
    root->left->right = make_shared<Node>(4);
    root->right->left = make_shared<Node>(5);
    root->right->right = make_shared<Node>(6);
    root->right->left->left = make_shared<Node>(7);
    root->right->left->right = make_shared<Node>(8);
    CHECK(diameter(root).diameter, 6);
  }
  {
    shared_ptr<Node> root = make_shared<Node>(1);
    root->right = make_shared<Node>(2);
    root->right->left = make_shared<Node>(3);
    root->right->right = make_shared<Node>(4);
    root->right->left->left = make_shared<Node>(5);
    root->right->left->right = make_shared<Node>(6);
    root->right->right->right = make_shared<Node>(7);
    CHECK(diameter(root).diameter, 5);
  }

  PRINT_MSG;
}