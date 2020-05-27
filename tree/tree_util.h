#pragma once
#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>

using namespace std;

namespace util {

struct Node {
  int data = 0;
  Node *left = nullptr;
  Node *right = nullptr;
  Node(int data) : data(data) {}
};

class Binary_tree {
 public:
  Binary_tree();
  ~Binary_tree();

  void insert(int key);
  Node *search(int key);
  void destroy_tree();
  void inorder_print();
  void postorder_print();
  void preorder_print();
  void level_order_print();
  void level_order_print_by_counting();
  void spiral_level_order_print_by_counting();
  void spiral_level_order_print_using_two_stack();

 private:
  void destroy_tree(Node *leaf);
  void insert(int key, Node *leaf);
  Node *search(int key, Node *leaf);
  void inorder_print(Node *leaf);
  void postorder_print(Node *leaf);
  void preorder_print(Node *leaf);
  Node *root = nullptr;
};

Binary_tree::Binary_tree() : root(nullptr) {}
Binary_tree::~Binary_tree() { destroy_tree(); }

void Binary_tree::insert(int key, Node *leaf) {
  if (key < leaf->data) {
    if (leaf->left)
      insert(key, leaf->left);
    else
      leaf->left = new Node(key);
  } else {
    if (leaf->right)
      insert(key, leaf->right);
    else
      leaf->right = new Node(key);
  }
}

void Binary_tree::insert(int key) {
  if (root)
    insert(key, root);
  else
    root = new Node(key);
}

void Binary_tree::destroy_tree(Node *leaf) {
  if (leaf) {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}

void Binary_tree::destroy_tree() { destroy_tree(root); }

Node *Binary_tree::search(int key, Node *leaf) {
  if (!leaf) return nullptr;
  if (leaf->data == key)
    return leaf;
  else if (leaf->data < key)
    return search(key, leaf->right);
  else
    return search(key, leaf->left);
}

Node *Binary_tree::search(int key) { return search(key, root); }

void Binary_tree::inorder_print(Node *leaf) {
  if (!leaf) return;

  inorder_print(leaf->left);
  std::cout << leaf->data << " ";
  inorder_print(leaf->right);
}

void Binary_tree::inorder_print() {
  std::cout << "inorder :\n";
  inorder_print(root);
  std::cout << "\n";
}
void Binary_tree::postorder_print() {
  std::cout << "postorder :\n";
  postorder_print(root);
  std::cout << "\n";
}
void Binary_tree::postorder_print(Node *leaf) {
  if (!leaf) return;
  postorder_print(leaf->left);
  postorder_print(leaf->right);
  std::cout << leaf->data << " ";
}

void Binary_tree::preorder_print() {
  std::cout << "preorder :\n";
  preorder_print(root);
  std::cout << "\n";
}
void Binary_tree::preorder_print(Node *leaf) {
  if (!leaf) return;
  std::cout << leaf->data << " ";
  preorder_print(leaf->left);
  preorder_print(leaf->right);
}

void Binary_tree::level_order_print() {
  std::cout << "level_order_print\n ";
  if (!root) return;
  std::queue<Node *> q;
  std::vector<int> result;
  q.emplace(root);
  while (!q.empty()) {
    auto node = q.front();
    result.emplace_back(node->data);
    q.pop();
    if (node->left) q.emplace(node->left);
    if (node->right) q.emplace(node->right);
  }
  std::for_each(result.begin(), result.end(),
                [](const auto &a) { cout << a << " "; });
  std::cout << "\n";
}

void Binary_tree::level_order_print_by_counting() {
  std::cout << "level_order_print_by_counting\n";
  if (!root) return;
  std::queue<Node *> q;
  std::vector<int> result, current;
  int current_level_size = 1;
  int next_level_size = 0;
  q.emplace(root);
  while (!q.empty()) {
    auto node = q.front();
    if (node->left) {
      q.emplace(node->left);
      next_level_size++;
    }
    if (node->right) {
      q.emplace(node->right);
      next_level_size++;
    }
    q.pop();
    current_level_size--;
    current.emplace_back(node->data);
    if (current_level_size == 0) {
      result.insert(result.end(), current.begin(), current.end());
      current.clear();
      current_level_size = next_level_size;
      next_level_size = 0;
    }
  }
  std::for_each(result.begin(), result.end(),
                [](const auto &a) { cout << a << " "; });
  std::cout << "\n";
}

void Binary_tree::spiral_level_order_print_by_counting() {
  std::cout << "spiral_level_order_print_by_counting\n";
  if (!root) return;
  std::queue<Node *> q;
  std::vector<int> result, current;
  int current_level_size = 1;
  int next_level_size = 0;
  bool ltr = false;
  q.emplace(root);
  while (!q.empty()) {
    auto node = q.front();
    if (ltr) {
      if (node->left) {
        q.emplace(node->left);
        next_level_size++;
      }
      if (node->right) {
        q.emplace(node->right);
        next_level_size++;
      }
    } else {
      if (node->right) {
        q.emplace(node->right);
        next_level_size++;
      }
      if (node->left) {
        q.emplace(node->left);
        next_level_size++;
      }
    }
    q.pop();
    current_level_size--;
    current.emplace_back(node->data);
    if (current_level_size == 0) {
      result.insert(result.end(), current.begin(), current.end());
      current.clear();
      current_level_size = next_level_size;
      next_level_size = 0;
      ltr = !ltr;
    }
  }
  std::for_each(result.begin(), result.end(),
                [](const auto &a) { cout << a << " "; });
  std::cout << "\n";
}

void Binary_tree::spiral_level_order_print_using_two_stack() {
  std::cout << "spiral_level_order_print_using_two_stack\n";
  if (!root) return;
  std::vector<int> result;
  std::stack<Node *> s1, s2;
  s1.push(root);

  while (!s1.empty() || !s2.empty()) {
    while (!s1.empty()) {
      auto node = s1.top();
      s1.pop();
      result.emplace_back(node->data);
      if (node->left) s2.emplace(node->left);
      if (node->right) s2.emplace(node->right);
    }

    while (!s2.empty()) {
      auto node = s2.top();
      result.emplace_back(node->data);
      s2.pop();
      if (node->right) s1.emplace(node->right);
      if (node->left) s1.emplace(node->left);
    }
  }
  std::for_each(result.begin(), result.end(),
                [](const auto &a) { cout << a << " "; });
  std::cout << "\n";
}

void test_binary_tree_util() {
  Binary_tree bt;
  bt.insert(40);
  bt.insert(50);
  bt.insert(10);
  bt.insert(20);
  bt.insert(60);
  bt.insert(30);
  bt.insert(55);
  bt.insert(80);
  /* Test various cases */
  bt.inorder_print();
  bt.preorder_print();
  bt.postorder_print();
  bt.level_order_print();
  bt.level_order_print_by_counting();
  bt.spiral_level_order_print_using_two_stack();
}
}  // namespace util