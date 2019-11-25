#pragma once

#include <stdio.h>
#include <iostream>

/* Link list node */
struct node {
  int data;
  struct node* next;
};


/* UTILITY FUNCTIONS */
/* Function to push a node */
void push(struct node*& head_ref, int new_data) {
  /* allocate node */
  struct node* new_node = new node;

  /* put in the data  */
  new_node->data = new_data;

  /* link the old list off the new node */
  new_node->next = head_ref;

  /* move the head to point to the new node */
  head_ref = new_node;
}

/* Function to print linked list */
void printList(struct node* node) {
  int count = 0;
  while (node != NULL) {
    printf("%d  ", node->data);
    node = node->next;
    count++;
  }
}
