/*
 * 09.KthNodeInTree.cpp
 *
 * Problem: Find kth node in a binary tree, in the order of inorder traversal.
 *          Assume that each node has number of nodes in the subtree under it.
 *
 *  Created on: Jan 13, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: It can be done it O(k) by simply keeping one counter of node so far visited while doing inorder traversal.
//           If we have the number nodes under a nodes subtree available, then we can skip some some subtree altogether.
//           This will be O(h) as we descend the tree in each iteration.

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	int size;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)), size(1) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;


BTI* KthNodeInTree(UBTI& root, int index)
{
	if(root == nullptr)
		return nullptr;

	int left_size = (root->left != nullptr) ? root->left->size : 0;

	if(root->left != nullptr && index <= root->left->size) {
		return KthNodeInTree(root->left, index);
	} else if(index == left_size + 1) {
		return root.get();
	} else {
		return KthNodeInTree(root->right, index - left_size - 1);
	}
}

// Ignore its complexity. Assume it is already available
void ComputeSizes(UBTI& root) {
	if(root == nullptr)
		return;

	if(root->left == nullptr && root->right == nullptr) {  // Leaf
		root->size = 1;
		return;
	} else {            // Non-leaf
		ComputeSizes(root->left);
		ComputeSizes(root->right);
		root->size = ((root->left != nullptr)?root->left->size:0) + ((root->right != nullptr)?root->right->size:0) + 1;
		return;
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

	ComputeSizes(root);

	BTI* kthNode = KthNodeInTree(root, 5);
	cout << "5th node: " << kthNode->data << endl;

	kthNode = KthNodeInTree(root, 8);
	cout << "8th node: " << kthNode->data << endl;
}


