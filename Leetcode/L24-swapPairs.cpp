/***************************************************************
Leetcode-easy-24: My runtime is 4ms.

Given a linked list, swap every two adjacent nodes and return its head.
Your algorithm should use only constant extra space.
You may not modify the values in the list's nodes, only nodes itself may be changed.

URL: https://leetcode.com/problems/merge-two-sorted-lists/
****************************************************************/
#pragma once
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* swapPairs(ListNode* head) {
  if ( head == nullptr || head->next == nullptr ) return head;
  
  ListNode *p1 = head, *p2 = head->next, *p3 = head->next->next;
  while ( p2 != nullptr ) {
    if ( p1 == head ) head = p2;
    
    p2->next = p1;               
    if ( p3 != nullptr && p3->next != nullptr ) {  // 偶数长度
      p1->next = p3->next;
      p1 = p3;
      p2 = p1->next;
      p3 = p2->next;
    }
    else {     // 奇数长度
      p1->next = p3;
      break;
    }
  }
  return head;
}