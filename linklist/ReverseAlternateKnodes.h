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

/*
https://leetcode.com/problems/reverse-nodes-in-k-group/solution/

Given a linked list, reverse the nodes of a linked list k at a time and return
its modified list.

k is a positive integer and is less than or equal to the length of the linked
list. If the number of nodes is not a multiple of k then left-out nodes, in the
end, should remain as it is.

Follow up:

Could you solve the problem in O(1) extra memory space?
You may not alter the values in the list's nodes, only nodes itself may be
changed.
Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]

Input: head = [1,2,3,4,5], k = 1
Output: [1,2,3,4,5]
*/
namespace {
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
  }; 
class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (count(head) < k) return head;

    ListNode* prev_head = head;
    /*
    1->2->3->4->5->6  ==>   3->2->1->6->5->4
     Suppose if we call the reverse method we need three things
     1. Pointer to 3 which is stored in result.
     2. Pointer to 1 which is already stored in the prev_head.
     3. Pointer to node 4 so that we can reverse from that. We updated the the
        head.
      Now it just a matter of calling the same method recursively.
    */
    ListNode* result = reverseList(&head, k);
    if (head != nullptr) prev_head->next = reverseKGroup(head, k);
    return result;
  }

  ListNode* reverseList(ListNode** head, int k) {
    ListNode* current = *head;
    ListNode* next = nullptr;
    ListNode* prev = nullptr;
    int count = 0;
    while (current != nullptr && count != k) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
      count++;
    }
    *head = current;
    return prev;
  }

  int count(ListNode* head) {
    int count = 0;
    while (head != nullptr) {
      head = head->next;
      count++;
    }
    return count;
  }
};
}  // namespace 
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