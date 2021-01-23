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
    else {
      leaf->left = make_shared<Node>(key);
      leaf->left->parent = leaf;
    }
  } else {
    if (leaf->right)
      insert(key, leaf->right);
    else {
      leaf->right = make_shared<Node>(key);
      leaf->right->parent = leaf;
    }
  }
}

void Binary_tree::insert(int key) {
  if (m_root)
    insert(key, m_root);
  else {
    m_root = make_shared<Node>(key);
    m_root->parent = nullptr;
  }
}

void Binary_tree::inorder_print() {
  std::cout << "inorder :\n";
  ::inorder_print(m_root);
  std::cout << "\n";
}
void Binary_tree::postorder_print() {
  std::cout << "postorder :\n";
  ::postorder_print(m_root);
  std::cout << "\n";
}

void Binary_tree::preorder_print() {
  std::cout << "preorder :\n";
  ::preorder_print(m_root);
  std::cout << "\n";
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
  CHECK(result, {40, 10, 50, 20, 60, 30, 55, 80});
  PRINT_MSG;
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
  CHECK(result, {40, 10, 50, 20, 60, 30, 55, 80});
  PRINT_MSG;
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
  PRINT_V(result);
  PRINT_MSG;
}

void Binary_tree::spiral_level_order_print_using_two_stack() {
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
  CHECK(result, {40, 50, 10, 20, 60, 80, 55, 30});
  PRINT_MSG;
}
/*
 This is easier method to do the level order traversal.
 Besides, it could be used to find the Bottom left or Bottom right node or last
 level easily.
*/
void Binary_tree::level_order_preferred() {
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
  CHECK(result, {{40}, {10, 50}, {20, 60}, {30, 55, 80}});
  PRINT_MSG;
}

/*
 This is easier method to do the level order traversal.
 We keep pushing elements as we do. It just that we print the output in spiral
 order. So we do by inserting the elements in the current vector.
*/
void Binary_tree::spiral_level_order_preferred() {
  if (m_root == nullptr) return;
  vector<vector<int>> result;
  std::queue<shared_ptr<Node>> q;
  bool l2r = true;
  q.emplace(m_root);
  int i = 0;
  while (q.empty() == false) {
    int node_count = q.size();
    vector<int> level(node_count);  // Reserve the size.
    while (i < node_count) {
      auto node = q.front();
      q.pop();

      if (l2r)
        level[i] = node->data;
      else
        level[node_count - 1 - i] = node->data;

      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
      i++;
    }
    i = 0;       // Reset i
    l2r = !l2r;  // Toggle the flag.
    result.push_back(level);
  }
  CHECK(result, {{40}, {50, 10}, {20, 60}, {80, 55, 30}});
  PRINT_MSG;
}

/*
 We change the datastructure from queue to dequeue and we can do spiral order
 traversal as well. This is cool techinique. Only thing is to be careful from
 where to pop and in what order to push the children.
*/
void Binary_tree::spiral_level_order_better() {
  if (m_root == nullptr) return;
  vector<vector<int>> result;

  std::deque<shared_ptr<Node>> q;
  bool ltr = true;
  q.push_back(m_root);
  while (q.empty() == false) {
    vector<int> level;
    int node_count = q.size();
    while (node_count) {
      shared_ptr<Node> node;
      if (ltr) {
        node = q.front();
        q.pop_front();
        if (node->left) q.push_back(node->left);
        if (node->right) q.push_back(node->right);
      } else {
        node = q.back();
        q.pop_back();
        if (node->right) q.push_front(node->right);
        if (node->left) q.push_front(node->left);
      }
      level.push_back(node->data);
      node_count--;
    }
    ltr = !ltr;
    result.push_back(level);
  }
  CHECK(result, {{40}, {50, 10}, {20, 60}, {80, 55, 30}});
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
  bt.level_order_preferred();
  bt.spiral_level_order_better();
  bt.spiral_level_order_preferred();
  return 0;
}