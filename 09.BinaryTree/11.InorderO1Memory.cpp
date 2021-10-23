/*
 * 11.InorderO1Memory.cpp
 *
 * Problem: Do inorder traversal using O(1) memory.
 *          Assume that each node has parent pointer.
 *
 *  Created on: Jan 14, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: If we keep track of previous pointer then we can detect where we are coming from
//           If coming from parent, go to left subtree
//           If coming from left subtree, print current data and go to right subtree
//           If coming from right subtree, go up as done with current subtree
//
//           For all the above cases handle when left/right my be empty

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	BinaryTreeNode* parent;  //Not owning

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)), parent(nullptr) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

void InorderO1Memory(UBTI& root)
{
	BTI* prev = nullptr;
	BTI* curr = root.get();

	while(curr != nullptr) {
		BTI* next;

		if(prev == curr->parent) {
			// came down from parent
			if(curr->left != nullptr) {
				next = curr->left.get();
			} else {
				cout << "Inorder: " << curr->data << endl;
				next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
			}
		} else if(prev == curr->left.get()) {
			// came up from left child
			cout << "Inorder: " << curr->data << endl;
			next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
		} else {
			// done with both children
			next = curr->parent;
		}

		prev = curr;
		curr = next;
	}
}

// Do not consider this in time complexity
void PopulateParent(UBTI& root) {
	if(root == nullptr) {
		return;
	}

	if(root->left != nullptr) {
		root->left->parent = root.get();
		PopulateParent(root->left);
	}

	if(root->right != nullptr) {
		root->right->parent = root.get();
		PopulateParent(root->right);
	}
}

int main()
{
	UBTI root = UBTI(new BTI(1,
						UBTI(new BTI(2,
								UBTI(new BTI(4,
										UBTI(new BTI(8, nullptr, nullptr)),
										UBTI(new BTI(9, nullptr, nullptr)))),
								UBTI(new BTI(5,
										nullptr,
										UBTI(new BTI(10,
												UBTI(new BTI(13, nullptr, nullptr)),
												nullptr)))))),
						UBTI(new BTI(3,
								UBTI(new BTI(6,
										nullptr,
										UBTI(new BTI(11,
												UBTI(new BTI(14,nullptr,
														UBTI(new BTI(16,nullptr,nullptr)))),
												UBTI(new BTI(15,nullptr,nullptr)))))),
								UBTI(new BTI(7,
										nullptr,
										UBTI(new BTI(12, nullptr, nullptr))))))));

	PopulateParent(root);

	InorderO1Memory(root);

	//Output should be: 8,4,9,2,5,13,10,1,6,14,16,11,15,3,7,12
}
