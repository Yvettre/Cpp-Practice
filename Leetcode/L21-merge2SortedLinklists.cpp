/***************************************************************
Leetcode-easy-21: My runtime is 8ms.

Merge two sorted linked lists and return it as a new list.
The new list should be made by splicing together the nodes of the first two lists.

URL: https://leetcode.com/problems/merge-two-sorted-lists/
****************************************************************/
#pragma once
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {        
  if ( l1 == nullptr && l2 == nullptr ) return nullptr;
  
  if ( l1 == nullptr ) return l2;
  if ( l2 == nullptr ) return l1;
  
  ListNode* res = nullptr;
  ListNode *pres, *nodetmp;
  int valtmp;
  while ( l1 != nullptr && l2 != nullptr ) {
    if ( l1->val <= l2->val ) {
      valtmp = l1->val;
      l1 = l1->next;
    }
    else {
      valtmp = l2->val;
      l2 = l2->next;
    }
    nodetmp = new ListNode(valtmp);
    if ( res == nullptr ) res = nodetmp;
    else pres->next = nodetmp;
    pres = nodetmp;
  }

  if ( l1 == nullptr ) pres->next = l2;
  if ( l2 == nullptr ) pres->next = l1;
  
  return res;       
}