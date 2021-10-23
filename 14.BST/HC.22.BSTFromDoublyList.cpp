/*
 * HC.22.BSTFromDoublyList.cpp
 *
 * Problem: Doubly linked list and BST both have a key and two references, so one can be transformed
 * 			into another.
 * 			Consider a doubly linked list of sorted numbers. We want to build a height balanced BST
 * 			from the entries on the list. Reuse the nodes of the list for BST, using the previous
 * 			and next field for left and right children respectively.
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
//
//			So if we find middle element and make it root and recursively use left and right part to
//			make the left and right subtree then solution can be done in T(n) = O(n) + 2T(n/2) which
//			is O(n log n).
//
//			Each recursive call will be passed the first node of the list it start building from and
//			and the start and end indices. And it should return the pointer to the root so that
//			it can be added as left or right child of the parent node or can be returned as root.
//
//			Since we can pass the start and end, each call can determine how much to process and
//			eventually how to process.
//
// Note:
//			- How we handle root
//			- How list is structured
//			- How recursive calls are used
//			- How to use start and end to simplify and manage recursive calls

struct ListNode {
	int val;
	shared_ptr<ListNode> next, prev;

	ListNode(int a, shared_ptr<ListNode> b = nullptr, shared_ptr<ListNode> c = nullptr) : val(a), next(b), prev(c) {}
};

typedef shared_ptr<ListNode> SLN;

SLN BuildBSTFromDoublyListHelper(SLN list, int start, int end);

SLN BuildBSTFromDoublyList(SLN list, int length) { //assume length of the list is given
	return BuildBSTFromDoublyListHelper(list, 0, length-1);
}

SLN BuildBSTFromDoublyListHelper(SLN start_node, int start, int end) {
	if(start > end) {
		return nullptr;
	}

	if(start == end) {
		start_node->next = nullptr;
		start_node->prev = nullptr;
		return start_node;
	}

	int mid = start + (end - start)/2;
	SLN left = nullptr, right = nullptr;

	// Root: get hold before first call removes the references
	SLN curr = start_node;
	for(int i=start ; i<mid ; ++i) {
		curr = curr->next;
	}

	// Left
	if(start < mid) {
		left = BuildBSTFromDoublyListHelper(start_node, start, mid-1);
	}

	// Right
	if(mid<end) {
		right = BuildBSTFromDoublyListHelper(curr->next, mid+1, end);
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
