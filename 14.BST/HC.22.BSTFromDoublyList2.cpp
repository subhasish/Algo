/*
 * HC.22.BSTFromDoublyList2.cpp
 *
 * Problem: Doubly linked list and BST both have a key and two references, so one can be transformed
 * 			into another.
 * 			Consider a doubly linked list of sorted numbers. We want to build a height balanced BST
 * 			from the entries on the list. Reuse the nodes of the list for BST, using the previous
 * 			and next field for left and right children respectively.
 *
 * 			In the previous solution we did it in O(n log n) time. Try to do it in O(n) time.
 *
 *  Created on: Dec 23, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			We have done similar BST building from array in 09.MinimumHeightBST.cpp in O(n) as
//			finding middle element from array is O(1). But finding middle element for list is O(n).
//			We cannot avoid that.
//			So in HC.22.BSTFromDoublyList.cpp after finding middle element we solved the problem in
//			O(n log n) time.
//
//			Key insight to improve the runtime is that since we spend O(n) time in finding the
//			mid point we can do more than just finding the mid point. Specifically we can make a
//			balanced BST from the first n/2 nodes.
//
//			Since we can pass the start and end, each call can determine how much to process and
//			eventually how to process. In previous solution we iterate each node to find the
//			next start for the right subtree.
//
//			But if we could pass that pointer around each call and that gets progressed as each node
//			is processed then we do not need extra iteration to find the start of next phase.
//
//			Since we are changing the links in the list, we need to be careful to ensure that we can
//			recover the root. We can do this by keeping a reference to the head of the list being
//			processed.
//
// Note:
//			- How to pass pointers around recursive calls
//			- How start and end helps recursive calls

struct ListNode {
	int val;
	shared_ptr<ListNode> next, prev;

	ListNode(int a, shared_ptr<ListNode> b = nullptr, shared_ptr<ListNode> c = nullptr) : val(a), next(b), prev(c) {}
};

typedef shared_ptr<ListNode> SLN;

SLN BuildBSTFromDoublyListHelper(SLN* list_ref, int start, int end);

SLN BuildBSTFromDoublyList(SLN list, int length) { //assume length of the list is given
	return BuildBSTFromDoublyListHelper(&list, 0, length-1);
}

SLN BuildBSTFromDoublyListHelper(SLN* start_ref, int start, int end) {
	if(start > end) {
		return nullptr;
	}

	if(start == end) {
		auto curr = *start_ref;
		*start_ref = (*start_ref)->next;
		curr->next = nullptr;
		curr->prev = nullptr;
		return curr;
	}

	int mid = start + (end - start)/2;
	SLN left = nullptr, right = nullptr;

	// Left
	if(start < mid) {
		left = BuildBSTFromDoublyListHelper(start_ref, start, mid-1);
	}

	// Root
	SLN curr = *start_ref;
	*start_ref = (*start_ref)->next;

	// Right
	if(mid<end) {
		right = BuildBSTFromDoublyListHelper(start_ref, mid+1, end);
	}

	curr->prev = left;
	curr->next = right;
	return curr;

}

void InorderDoublyLinkedBST(const SLN& root)
{
	if(root == nullptr) return;

	InorderDoublyLinkedBST(root->prev);
	cout << root->val << ", ";
	InorderDoublyLinkedBST(root->next);
}

int main() {
	SLN a = SLN(new ListNode(2));
	SLN b = SLN(new ListNode(3));
	SLN c = SLN(new ListNode(5));
	SLN d = SLN(new ListNode(7));
	SLN e = SLN(new ListNode(11));

	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	b->prev = a;
	c->prev = b;
	d->prev = c;
	e->prev = d;

	SLN root = BuildBSTFromDoublyList(a, 5);

	cout << "Root = " << root->val << endl;

	cout << "In-order traversal of the nodes = ";
	InorderDoublyLinkedBST(root);
	cout << endl;

}
