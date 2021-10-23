/*
 * 10.SuccessorInTree.cpp
 *
 * Problem: Find successor of a node in a binary tree. Successor is the node that appear immediately after the node in inorder traversal.
 *          Assume each node has a parent pointer.
 *
 *  Created on: Jan 13, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: 3 cases:
//                1. If node has right subtree: it is the leftmost node in that subtree
//                   If no right subtree then two cases:
//                2.      If node is left child of the parent then parent is the successor
//                3.      If node is right child of the parent then parent is already visited.
//                        So go up until find a parent for which this node was in left subtree.

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	BinaryTreeNode* parent;  //Not owning

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)), parent(nullptr) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

BTI* Successor(UBTI& node) {
	if(node == nullptr)
		return nullptr;

	if(node->right != nullptr) {    // Has right sub-tree. Find the left most node there.
		BTI* p = node->right.get();
		while (p->left != nullptr) {
			p = p->left.get();
		}
		return p;
	}
	else {
		// Go up until find the parent for which this node is in left subtree
		BTI* p = node.get();
		while( p != nullptr && p->parent != nullptr && p == p->parent->right.get() ) { //Go up till we are in right
			p = p->parent;
		}

		return p->parent ;
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


int main() {
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

	BTI* successor = Successor(root->left->right->right);
	cout << "Successor of " << root->left->right->right->data << " is: " << successor->data << endl;

	successor = Successor(root->right->left);
	cout << "Successor of " << root->right->left->data << " is: " << successor->data << endl;

	successor = Successor(root->left->left->left);
	cout << "Successor of " << root->left->left->left->data << " is: " << successor->data << endl;
}
