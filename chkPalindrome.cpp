/***************************************************************
对于一个链表，请设计一个时间复杂度为O(n),额外空间复杂度为O(1)的算法，判断其是否为回文结构。
给定一个链表的头指针A，请返回一个bool值，代表其是否为回文结构。保证链表长度小于等于900。

测试样例：
1->2->2->1
返回：true

本解答结果（参考别人的代码理解后加了一句小修改）：占用内存600k，运行时间6ms
另外，这个答案对于释放链表并不友好，因为它修改了链表后半部分的指向，导致部分节点无法访问到
因此，此处没有给出main函数部分，有兴趣的可以戳这里：
https://www.nowcoder.com/practice/d281619e4b3e4a60a2cc66ea32855bfa?tpId=49&&tqId=29370&rp=1&ru=/activity/oj&qru=/ta/2016test/question-ranking
****************************************************************/
#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
  int val;
  struct ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

// 判断一个单向链表是否是回文数
bool chkPalindrome(ListNode* A) {
	// A为空时false，A为单个节点时true
	if (A==nullptr) { return false; }
	else if (A->next == nullptr) { return true; }

	// 快慢指针找出中间节点
	ListNode *quick = A, *slow = A;
	while (quick != nullptr && quick->next != nullptr) {
		quick = quick->next->next;
		slow = slow->next;
	}

	// 将中间节点后的指针反转
	ListNode *p = slow->next;
	ListNode *p1 = p->next;
	while (p != nullptr) {
		p->next = slow;
		slow = p;
		p = p1;
		if (p != nullptr) {   // 必须加，否则会出现试图访问空指针的next的情况，引起闪退
			p1 = p->next;
		}	
	}

	// 从头尾指针向中间遍历，判断是否是回文数（此时slow指针指向最后一个节点）
	while (A != slow) {
		if (A->val != slow->val) {
			return false;
		}
		else {
			if (A->next == slow) {
				return true;
			}
			A = A->next;
			slow = slow->next;
		}
	}
	return true;
}