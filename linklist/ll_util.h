#pragma once

#include <iostream>

#include "../my_util.h"

/* Link list node */
struct node {
  int data;
  struct node* next;
};


/* UTILITY FUNCTIONS */
/* Function to push a node in the beginning of the list */
node* head_push(struct node*& head_ref, int new_data) {
  /* allocate node */
  struct node* new_node = new node;

  /* put in the data  */
  new_node->data = new_data;

  /* link the old list off the new node */
  new_node->next = head_ref;

  /* move the head to point to the new node */
  head_ref = new_node;
  return head_ref;
}

/* Function to print linked list */
int print_list(struct node* node) {
  int count = 0;
  while (node != NULL) {
    cout << node->data;
    node = node->next;
    if (node) cout << "->";
    count++;
  }
  cout << "\n";
  return count;
}

string print_list_to_string(struct node* node) {
  string result;
  while (node != NULL) {
    result += std::to_string(node->data);
    node = node->next;
    if (node) result += "->";
  }
  return result;
}
