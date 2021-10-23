/*
 * HC.23.BSTToDoublyList.cpp
 *
 * Problem: Doubly linked list and BST both have a key and two references, so one can be transformed
 * 			into another.
 * 			Design an algorithm that takes as input a BST and returns a sorted doubly linked list
 * 			on the same elements. Your algorithm should not do any dynamic allocation, instead can
 * 			reuse the BST nodes to make the list.
 *
 *  Created on: Dec 24, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			From BST structure it is clear that recursive algorithm can be used to solve the problem.
//			If we have list for the left and right subtrees then we can just append them around root to
//			come to a solution.
//
//			The only thing we need for this is that the recursive calls returns both head and tail of
//			the list. We need both as root needs to be attached to the tail of left list and head of
//			right list.
//
//			Only note that left and right list can return null and where the root can be either
//			head or tail.
//
// Time complexity:
//			T(n) = O(1) + 2*T(n/2) = O(n)
//			Another way to look at the time complexity is that constant amount of time is spent on
//			each node, hence O(n).

struct BSTNode {
	int val;
	shared_ptr<BSTNode> left, right;

	BSTNode(int a, shared_ptr<BSTNode> b = nullptr, shared_ptr<BSTNode> c = nullptr) : val(a), left(b), right(c) {}
};

typedef shared_ptr<BSTNode> SBN;

struct HeadAndTail {
	SBN head, tail;
};

HeadAndTail BSTToDoublyListHelper(const SBN& tree);

SBN BSTToDoublyList(const SBN& tree) {
	return BSTToDoublyListHelper(tree).head;
}

HeadAndTail BSTToDoublyListHelper(const SBN& tree) {
	// Base case: empty subtree
	if(!tree) {
		return HeadAndTail{nullptr, nullptr};
	}

	// Recursively built list from left and right subtree
	HeadAndTail left = BSTToDoublyListHelper(tree->left);
	HeadAndTail right = BSTToDoublyListHelper(tree->right);

	// Append tree to the list from left subtree
	if(left.tail) {
		left.tail->right = tree;
	}
	tree->left = left.tail;

	// Append list from right subtree to the tree
	if(right.head) {
		right.head->left = tree;
	}
	tree->right = right.head;

	return HeadAndTail{ left.head ? left.head : tree,
						right.tail ? right.tail : tree};
}

void PrintListAsBST(const SBN& list) {
	if(list) {
		cout << list->val << " ";
		PrintListAsBST(list->right);
	}
}

int main() {
	SBN a = SBN(new BSTNode(7));
	SBN b =	SBN(new BSTNode(3));
	SBN c = SBN(new BSTNode(2));
	SBN d = SBN(new BSTNode(5));
	SBN e = SBN(new BSTNode(11));

	a->left = b; a->right = e;
	b->left = c; b->right = d;

	SBN head = BSTToDoublyList(a);
	PrintListAsBST(head);
}
