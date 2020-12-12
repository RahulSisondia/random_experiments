#pragma once
#include "../my_util.h"

struct Node {
  int data = 0;
  shared_ptr<Node> left = nullptr;
  shared_ptr<Node> right = nullptr;
  shared_ptr<Node> parent = nullptr;
  Node(int data) : data(data) {}
};

using bnode = shared_ptr<Node>;

shared_ptr<Node> insert(shared_ptr<Node> root, int key) {
  if (root == nullptr) {
    root = make_shared<Node>(key);
    return root;
  }
  shared_ptr<Node> temp;
  if (key < root->data) {
    temp = insert(root->left, key);
    root->left = temp;
    temp->parent = root;
  } else {
    temp = insert(root->right, key);
    root->right = temp;
    temp->parent = root;
  }
  return temp;
}

shared_ptr<Node> search(shared_ptr<Node> node, int key) {
  if (node == nullptr) return nullptr;
  if (node->data == key)
    return node;
  else if (node->data < key)
    return search(node->right, key);
  else
    return search(node->left, key);
}

void inorder_print(shared_ptr<Node> node) {
  if (!node) return;

  inorder_print(node->left);
  std::cout << node->data << " ";
  inorder_print(node->right);
}

void postorder_print(shared_ptr<Node> root) {
  if (!root) return;
  postorder_print(root->left);
  postorder_print(root->right);
  std::cout << root->data << " ";
}
void preorder_print(shared_ptr<Node> root) {
  if (!root) return;
  std::cout << root->data << " ";
  preorder_print(root->left);
  preorder_print(root->right);
}

class Binary_tree {
 public:
  Binary_tree();
  ~Binary_tree();
  void insert(int key);
  void inorder_print();
  void postorder_print();
  void preorder_print();
  void level_order_print();
  void level_order_print_by_counting();
  void level_order_preferred();
  void spiral_level_order_print_by_counting();
  void spiral_level_order_print_using_two_stack();
  void spiral_level_order_preferred();

 private:
  void insert(int key, shared_ptr<Node> leaf);
  shared_ptr<Node> m_root = nullptr;
};
