/*
 * HC.24.MergeTwoBSTs.cpp
 *
 * Problem: Given two BSTs, it is straightforward to create a BST containing union of their keys;
 *			traverse one and insert its keys into another.
 *
 *			Design an algorithm that takes as input two BSTs and merge them to form a balanced BST.
 *			Do not allocate new node but rearrange references only.
 *
 *  Created on: Dec 25, 2018
 *      Author: subha
 */


#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Making one tree as balanced and inserting other one into that has overall time complexity
//			O(n log n). Besides time complexity the algorithm for preserving balancedness while
//			inserting is non-trivial. Also we might need to make first tree as balanced before we
//			start inserting second one into it.
//
//			Looking carefully the brute force algorithm does not exploit the fact that data is already
//			sorted.
//			Also in problem HC.23.BSTToDoublyList.cpp and HC.22.BSTFromDoublyList2.cpp we have converted
//			a BST to a doubly linked list and converted back in O(n) time without using additional
//			memory.
//
//			So we can convert the two BSTs to two lists then merge them and then convert it back to BST
//			O(n) time.
//
// Note:
//			- Be careful about passing reference to pointers to auxiliary functions like
//			  compute length. It can modify the actual list head.

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

SBN MergeTwoSortedList(SBN a, SBN b) {
	// Create a placeholder for the result.
	SBN dummy_head(new BSTNode(0));
	SBN tail = dummy_head;

	// Compare and merge
	while(a && b) {
		SBN next;
		if(a->val < b->val) {
			next = a;
			a = a->right;
		} else {
			next = b;
			b = b->right;
		}

		next->left = tail;
		next->right = nullptr;
		tail->right = next;
		tail = next;
	}

	// Append remaining elements from other non-empty list
	if(a) {
		tail->right = a;
		a->left = tail;
	} else if (b) {
		tail->right = b;
		b->left = tail;
	} else {
		tail->right = nullptr;
	}

	return dummy_head->right;
}


SBN BuildBSTFromDoublyListHelper(SBN* list_ref, int start, int end);

SBN BuildBSTFromDoublyList(SBN list, int length) { //assume length of the list is given
	return BuildBSTFromDoublyListHelper(&list, 0, length-1);
}

SBN BuildBSTFromDoublyListHelper(SBN* start_ref, int start, int end) {
	if(start > end) {
		return nullptr;
	}

	if(start == end) {
		auto curr = *start_ref;
		*start_ref = (*start_ref)->right;
		curr->right= nullptr;
		curr->left = nullptr;
		return curr;
	}

	int mid = start + (end - start)/2;
	SBN left = nullptr, right = nullptr;

	// Left
	if(start < mid) {
		left = BuildBSTFromDoublyListHelper(start_ref, start, mid-1);
	}

	// Root
	SBN curr = *start_ref;
	*start_ref = (*start_ref)->right;

	// Right
	if(mid<end) {
		right = BuildBSTFromDoublyListHelper(start_ref, mid+1, end);
	}

	curr->left = left;
	curr->right = right;
	return curr;

}

int ComputeLength(SBN l) {
	int count = 0;
	while(l) {
		++count;
		l = l->right;
	}
	return count;
}

void InorderBST(const SBN& root)
{
	if(root == nullptr) return;

	InorderBST(root->left);
	cout << root->val << ", ";
	InorderBST(root->right);
}

SBN MergeTwoBSTs(SBN A, SBN B) {
	A = BSTToDoublyList(A);
	B = BSTToDoublyList(B);

	int A_len = ComputeLength(A);
	int B_len = ComputeLength(B);

	SBN M = MergeTwoSortedList(A, B);
	return BuildBSTFromDoublyList(M, A_len+B_len);
}

int main() {
	SBN a = SBN(new BSTNode(17));
	SBN b =	SBN(new BSTNode(5));
	SBN c = SBN(new BSTNode(2));
	SBN d = SBN(new BSTNode(11));
	SBN e = SBN(new BSTNode(23));

	a->left = b; a->right = e;
	b->left = c; b->right = d;

	SBN f = SBN(new BSTNode(13));
	SBN g =	SBN(new BSTNode(7));
	SBN h = SBN(new BSTNode(3));
	SBN i = SBN(new BSTNode(19));

	f->left = g; f->right = i;
	g->left = h;

	SBN m = MergeTwoBSTs(a, f);

	cout << "In-order: ";
	InorderBST(m);
	cout << endl;
}
