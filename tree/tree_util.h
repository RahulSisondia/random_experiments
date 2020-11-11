#include "../my_util.h"

struct Node {
  int data = 0;
  shared_ptr<Node> left = nullptr;
  shared_ptr<Node> right = nullptr;
  Node(int data) : data(data) {}
};

class Binary_tree {
 public:
  Binary_tree();
  ~Binary_tree();

  void insert(int key);
  shared_ptr<Node> search(int key);
  void inorder_print();
  void postorder_print();
  void preorder_print();
  void level_order_print();
  void level_order_print_by_counting();
  void spiral_level_order_print_by_counting();
  void spiral_level_order_print_using_two_stack();
  void bottem_up_traversal();

 private:
  void insert(int key, shared_ptr<Node> leaf);
  shared_ptr<Node> search(int key, shared_ptr<Node> leaf);
  void inorder_print(shared_ptr<Node> leaf);
  void postorder_print(shared_ptr<Node> leaf);
  void preorder_print(shared_ptr<Node> leaf);
  shared_ptr<Node> m_root = nullptr;
};
