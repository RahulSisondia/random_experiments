#include "tree_util.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>

using namespace std;

Binary_tree::Binary_tree() : m_root(nullptr) {}
Binary_tree::~Binary_tree() {}

void Binary_tree::insert(int key, shared_ptr<Node> leaf) {
  if (key < leaf->data) {
    if (leaf->left)
      insert(key, leaf->left);
    else
      leaf->left = make_shared<Node>(key);
  } else {
    if (leaf->right)
      insert(key, leaf->right);
    else
      leaf->right = make_shared<Node>(key);
  }
}

void Binary_tree::insert(int key) {
  if (m_root)
    insert(key, m_root);
  else
    m_root = make_shared<Node>(key);
}

shared_ptr<Node> Binary_tree::search(int key, shared_ptr<Node> leaf) {
  if (!leaf) return nullptr;
  if (leaf->data == key)
    return leaf;
  else if (leaf->data < key)
    return search(key, leaf->right);
  else
    return search(key, leaf->left);
}

shared_ptr<Node> Binary_tree::search(int key) { return search(key, m_root); }

void Binary_tree::inorder_print(shared_ptr<Node> leaf) {
  if (!leaf) return;

  inorder_print(leaf->left);
  std::cout << leaf->data << " ";
  inorder_print(leaf->right);
}

void Binary_tree::inorder_print() {
  std::cout << "inorder :\n";
  inorder_print(m_root);
  std::cout << "\n";
}
void Binary_tree::postorder_print() {
  std::cout << "postorder :\n";
  postorder_print(m_root);
  std::cout << "\n";
}
void Binary_tree::postorder_print(shared_ptr<Node> leaf) {
  if (!leaf) return;
  postorder_print(leaf->left);
  postorder_print(leaf->right);
  std::cout << leaf->data << " ";
}

void Binary_tree::preorder_print() {
  std::cout << "preorder :\n";
  preorder_print(m_root);
  std::cout << "\n";
}
void Binary_tree::preorder_print(shared_ptr<Node> leaf) {
  if (!leaf) return;
  std::cout << leaf->data << " ";
  preorder_print(leaf->left);
  preorder_print(leaf->right);
}

void Binary_tree::level_order_print() {
  std::cout << "level_order_print\n ";
  if (!m_root) return;
  std::queue<shared_ptr<Node>> q;
  std::vector<int> result;
  q.emplace(m_root);
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
  if (!m_root) return;
  std::queue<shared_ptr<Node>> q;
  std::vector<int> result, current;
  int current_level_size = 1;
  int next_level_size = 0;
  q.emplace(m_root);
  while (!q.empty()) {
    auto node = q.front();
    q.pop();
    current_level_size--;
    current.emplace_back(node->data);

    if (node->left) {
      q.emplace(node->left);
      next_level_size++;
    }
    if (node->right) {
      q.emplace(node->right);
      next_level_size++;
    }

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
  if (!m_root) return;
  std::queue<shared_ptr<Node>> q;
  std::vector<int> result, current;
  int current_level_size = 1;
  int next_level_size = 0;
  bool ltr = false;
  q.emplace(m_root);
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
  if (!m_root) return;
  std::vector<int> result;
  std::stack<shared_ptr<Node>> s1, s2;
  s1.push(m_root);

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

void Binary_tree::bottem_up_traversal() {
  if (m_root == nullptr) return;
  vector<vector<int>> result;
  std::queue<shared_ptr<Node>> q;
  q.emplace(m_root);
  while (q.empty() == false) {
    vector<int> level;
    int node_count = q.size();
    while (node_count) {
      auto node = q.front();
      q.pop();
      level.push_back(node->data);
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
      node_count--;
    }
    result.push_back(level);
  }
  for (int i = result.size() - 1; i >= 0; i--) {
    cout << "{";
    for (int j = 0; j < result[i].size() - 1; j++) {
      cout << result[i][j] << ",";
    }
    cout << result[i].back();
    cout << "}" << endl;
  }
  PRINT_MSG;
}

int main() {
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
  bt.bottem_up_traversal();
  return 0;
}