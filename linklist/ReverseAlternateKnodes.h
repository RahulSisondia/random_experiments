// ReverseAlternateKnodes.cpp : Defines the entry point for the console
// application.
//
#ifndef REVERSE_NODES
#define REVERSE_NODES

#include <stdio.h>
#include <stdlib.h>
#include "ll_util.h"


/* Reverses alternate k nodes and
returns the pointer to the new head node */
struct node* kAltReverse(struct node* head, int k) {
  struct node* current = head;
  struct node* next;
  struct node* prev = NULL;
  int count = 0;

  /*1) reverse first k nodes of the linked list */
  while (current != NULL && count < k) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
    count++;
  }

  /* 2) Now head points to the kth node.  So change next
  of head to (k+1)th node*/
  if (head != NULL) head->next = current;

  /* 3) We do not want to reverse next k nodes. So move the current
   * pointer to skip next k nodes */
  count = 0;
  while (count < k - 1 && current != NULL) {
    current = current->next;
    count++;
  }

  /* 4) Recursively call for the list starting from current->next.
  And make rest of the list as next of first node */
  if (current != NULL) current->next = kAltReverse(current->next, k);

  /* 5) prev is new head of the input list */
  return prev;
}

void test_alternate_kth_node() {
  /* Start with the empty list */
  struct node* head = NULL;

  // create a list 1->2->3->4->5...... ->20
  for (int i = 20; i > 0; i--) head_push(head, i);

  // printf("\n Given linked list \n");
  // print_list(head);
  head = kAltReverse(head, 3);

  // printf("\n Modified Linked list \n");
  // print_list(head);
  CHECK(print_list_to_string(head),
        string("3->2->1->4->5->6->9->8->7->10->11->12-"
               ">15->14->13->16->17->18->20->19"));
  PRINT_MSG;
}

#endif