#pragma once
#include "tree_util.h"

struct st {
  int height = 0;
  int diameter = 0;
};
/*
Diameter is either of left diameter, right diameter, or left height,
right height +1. That means we would beed to calculate the height and
diameters of sub trees. That would be O(n^2) solution, as you can see
in the following
https://www.geeksforgeeks.org/dsa/diameter-of-a-binary-tree-in-on-a-new-method/
Instead, we could store the height of the subtrees while traversing them
as following :
https://www.techiedelight.com/find-diameter-of-a-binary-tree/

Similary, had we asked if the tree is height balanced then we would simply
store a bool flag instead of the diameter in the return value.
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