#include "tree_util.h"

void test_inorder_successor_with_parent() {
  bnode root = insert(nullptr, 20);
  root->left = insert(root, 9);
  root->right = insert(root, 25);
  root->left->left = insert(root->left, 5);
  root->left->right = insert(root->left, 12);
  root->left->right->left = insert(root->left->right, 11);
  root->left->right->right = insert(root->left->right, 14);
  // inorder_print(root);
  auto using_parent_ptr_in_btree = [&](bnode node) -> bnode {
    auto itr = node;
    // if there is right subtree then successor will be the leftmost element in
    // that subtree
    if (itr->right) {
      itr = itr->right;
      while (itr->left) {
        itr = itr->left;
      }
      return itr;
    }
    // Find the closed ancesstor whose left subtree conrtains the node
    // Bit tricky but visualalize it with the help of a tree.
    while (itr->parent && itr->parent->right == itr) {
      itr = itr->parent;
    }
    return itr->parent;
  };
  CHECK(using_parent_ptr_in_btree(search(root, 12))->data, 14);
  CHECK(using_parent_ptr_in_btree(search(root, 11))->data, 12);
  CHECK(using_parent_ptr_in_btree(search(root, 14))->data, 20);

  auto using_parent_ptr_in_bst = [&](bnode node) -> bnode {
    if (node == nullptr) return nullptr;
    auto itr = node;
    // if there is right subtree then successor will be the leftmost element in
    // that subtree
    if (itr->right) {
      itr = itr->right;
      while (itr->left) {
        itr = itr->left;
      }
      return itr;
    }
    /* The ancesstor that has key bigger than the current key will be successor
       since it is BST.
    */
    int key = itr->data;
    itr = itr->parent;
    while (itr && key > itr->data) {
      itr = itr->parent;
    }
    /*
      Note above strategy works only for BST. What if we were
      given a binary tree ? Therefore, a better strategy that wil work for BST
      and binary tree both will be as following:
        within inputNode's ancestor chain (starting from inputNode all the way
        up to the root), successorNode is the first parent that has a left child
        in that chain.
        while (ancestor != null AND child == ancestor.right):
        child = ancestor
        ancestor = child.parent
    */
    return itr;
  };
  CHECK(using_parent_ptr_in_bst(search(root, 12))->data, 14);
  CHECK(using_parent_ptr_in_bst(search(root, 11))->data, 12);
  CHECK(using_parent_ptr_in_bst(search(root, 14))->data, 20);
  PRINT_MSG;
}
