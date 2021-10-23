/*
 * 01.HeightBalanced.cpp
 *
 * Problem: Check if a binary tree is height balanced, i.e., difference of heights of left and right subtree is at most one
 *
 *  Created on: Jan 9, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Classic postorder traversal. Keep height and balanced status of each sub-tree
//           Use helper function to do the actual recursion and return all info required.

struct BalanceStatusWithHeight {
	bool balanced;
	int height;
};

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

BalanceStatusWithHeight IsBalancedHelper(UBTI& root)
{
	if(root == nullptr) // Base case
		return {true,0};

	BalanceStatusWithHeight left_h = IsBalancedHelper(root->left);
	if(!left_h.balanced) // Left subtree is not balanced
		return {false, -1};

	BalanceStatusWithHeight right_h = IsBalancedHelper(root->right);
	if(!right_h.balanced) // Left subtree is not balanced
		return {false, -1};

	if(abs(left_h.height - right_h.height) > 1) {
		return {false, -1};
	} else {
		return {true, max(left_h.height, right_h.height) + 1};
	}
}

bool IsBalanced(UBTI& root)
{
	return IsBalancedHelper(root).balanced;
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

	cout << IsBalanced(root1) << endl;

	UBTI root2 = UBTI(new BTI(1,
						UBTI(new BTI(2,
								UBTI(new BTI(4,
										UBTI(new BTI(8, nullptr, nullptr)),
										UBTI(new BTI(9, nullptr, nullptr)))),
								UBTI(new BTI(5,
										nullptr,
										UBTI(new BTI(10,
												nullptr,
												nullptr)))))),
						UBTI(new BTI(3,
								UBTI(new BTI(6,
										nullptr,
										UBTI(new BTI(11,
												nullptr,
												nullptr)))),
								UBTI(new BTI(7,
										nullptr,
										UBTI(new BTI(12, nullptr, nullptr))))))));

		cout << IsBalanced(root2) << endl;
}

