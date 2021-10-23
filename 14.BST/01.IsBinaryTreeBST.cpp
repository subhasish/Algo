/*
 * 01.IsBinaryTreeBST.cpp
 *
 * Problem: Test if a binary tree is a BST or not
 *
 *  Created on: Mar 22, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Obvious one is post-order as we can only decide once we have seen all out children.
//			Return (max, min) of each subtree.
//
//			Another way is passing down the constraint
//
//			Another way is to do inorder traversal and see if elements appear in sorted order

struct BSTNode{
	int data;
	unique_ptr<BSTNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BSTNode (int a, unique_ptr<BSTNode> b, unique_ptr<BSTNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BSTNode> UBSTN;

bool AreKeysInRange(const UBSTN& root, int low, int high)
{
	if(root == nullptr) {
		return true;
	} else if(root->data < low || root->data > high) {
		return false;
	}

	return AreKeysInRange(root->left, low, root->data) &&
			AreKeysInRange(root->right, root->data, high);
}

bool IsBinaryTreeBST(const UBSTN& root)
{
	return AreKeysInRange(root, numeric_limits<int>::min(), numeric_limits<int>::max());
}

int main()
{
	UBSTN root1 = UBSTN(new BSTNode(19,
							UBSTN(new BSTNode(7,
									UBSTN(new BSTNode(3,
											UBSTN(new BSTNode(2, nullptr, nullptr)),
											UBSTN(new BSTNode(5, nullptr, nullptr)))),
									UBSTN(new BSTNode(11,
											nullptr,
											UBSTN(new BSTNode(17,
													UBSTN(new BSTNode(13, nullptr, nullptr)),
													nullptr)))))),
							UBSTN(new BSTNode(43,
									UBSTN(new BSTNode(23,
											nullptr,
											UBSTN(new BSTNode(37,
													UBSTN(new BSTNode(29,nullptr,
															UBSTN(new BSTNode(31,nullptr,nullptr)))),
													UBSTN(new BSTNode(41,nullptr,nullptr)))))),
									UBSTN(new BSTNode(47,
											nullptr,
											UBSTN(new BSTNode(53, nullptr, nullptr))))))));

	cout << "Tree 1 BST: " << IsBinaryTreeBST(root1) << endl;

	UBSTN root2 = UBSTN(new BSTNode(19,
							UBSTN(new BSTNode(7,
									UBSTN(new BSTNode(3,
											UBSTN(new BSTNode(2, nullptr, nullptr)),
											UBSTN(new BSTNode(5, nullptr, nullptr)))),
									UBSTN(new BSTNode(11,
											nullptr,
											UBSTN(new BSTNode(17,
													UBSTN(new BSTNode(13, nullptr, nullptr)),
													nullptr)))))),
							UBSTN(new BSTNode(43,
									UBSTN(new BSTNode(23,
											nullptr,
											UBSTN(new BSTNode(37,
													UBSTN(new BSTNode(29,nullptr,
															UBSTN(new BSTNode(31,nullptr,nullptr)))),
													UBSTN(new BSTNode(41,nullptr,nullptr)))))),
									UBSTN(new BSTNode(47,
											nullptr,
											UBSTN(new BSTNode(23, nullptr, nullptr))))))));

	cout << "Tree 1 BST: " << IsBinaryTreeBST(root2) << endl;
}
