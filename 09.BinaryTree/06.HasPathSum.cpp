/*
 * 06.HasPathSum.cpp
 *
 * Problem: Find a root to leaf path with specified sum
 *
 *  Created on: Jan 12, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Classic preorder problem. Transfer the partial sum from parent to its children, then take decision at the leaf.

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

// Easier to solve using remaining weight parameter
bool HasPathSum(UBTI& root, int remaining_weight) {
	if(root == nullptr) {
		return false;
	} else if (root->left == nullptr && root->right == nullptr) {   // Leaf
		if(remaining_weight == root->data) {
			return true;
		} else {
			return false;
		}
	} else {    // Non-leaf
		return HasPathSum(root->left, remaining_weight - root->data) ||
				HasPathSum(root->right, remaining_weight - root->data);
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

	cout << "Has path sum of 590: " << HasPathSum(root, 590) << endl;
	cout << "Has path sum of 31:  " << HasPathSum(root, 31) << endl;
}
