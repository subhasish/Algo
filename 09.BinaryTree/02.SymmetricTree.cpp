/*
 * 02.SymmetricTree.cpp
 *
 * Problem: Test if a binary tree is symmetric (both structure-wise and value wise)
 *
 *  Created on: Jan 9, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: One thing we can do it recursively, but the recursion is not based on one tree but two trees.
//           If left and right children are symmetric then tree is symmetric.
//           We only need to be careful about what parts we are comparing;
//                  always need to compare some parts of left subtree with some part of right sub-tree.


struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

bool IsTwoTreesSymmetric(UBTI& left, UBTI& right)
{
	if(left == nullptr && right == nullptr)
		return true;

	if((left == nullptr && right != nullptr) || (left != nullptr && right == nullptr))
		return false;

	// Now both nodes are present

	// ALL the below checks could be written compactly by short-circuiting conditions

	if(left->data != right->data)
		return false;

	// Now check recursively two children
	bool check1 = IsTwoTreesSymmetric(left->left, right->right);
	if(!check1)
		return false;

	bool check2 = IsTwoTreesSymmetric(left->right, right->left);
	return check2;
}

bool IsSymmetricTree(UBTI& root) {
	if(root == nullptr)
		return true;

	return IsTwoTreesSymmetric(root->left, root->right);
}


int main()
{
	UBTI root1 = UBTI(new BTI(1,
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

		cout << IsSymmetricTree(root1) << endl;

		UBTI root2 = UBTI(new BTI(1,
							UBTI(new BTI(6,
									nullptr,
									UBTI(new BTI(2,
											nullptr,
											UBTI(new BTI(3,
													nullptr,
													nullptr)))))),
							UBTI(new BTI(6,
									UBTI(new BTI(2,
											UBTI(new BTI(3,
													nullptr,
													nullptr)),
											nullptr)),
									nullptr))));

			cout << IsSymmetricTree(root2) << endl;
}
