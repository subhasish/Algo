/*
 * 05.SumRootToLeaf.cpp
 *
 * Problem: Find sum of all root to leaf paths of a binary tree where each node has a boolean number
 *          Can be generalized to decimal number or number of some other base.
 *
 *  Created on: Jan 11, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Summing from LSB has to track position of each digit to compute base to the power position.
//           But summing from MSB is easy as every time multiplying base to the intermediate result would work,
//           no need to keep track of anything other than result.
//           So we would do Preorder, for left or right subtree we would propagate the result. And at leaf we will add it to total.

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

void SumRootToLeafHelper(UBTI& root, int& total, int sumSoFar)
{
	if(root == nullptr) {
		return;
	}

	sumSoFar = sumSoFar*2 + root->data;
	if(root->left == nullptr && root->right == nullptr) {
		total += sumSoFar;
		return;
	}

	SumRootToLeafHelper(root->left, total, sumSoFar);
	SumRootToLeafHelper(root->right, total, sumSoFar);

}

int SumRootToLeaf(UBTI& root) {
	int total=0;
	SumRootToLeafHelper(root, total, 0);
	return total;
}

int main() {
	UBTI root = UBTI(new BTI(1,
						UBTI(new BTI(0,
								UBTI(new BTI(0,
										UBTI(new BTI(0, nullptr, nullptr)),
										UBTI(new BTI(1, nullptr, nullptr)))),
								UBTI(new BTI(1,
										nullptr,
										UBTI(new BTI(1,
												UBTI(new BTI(0, nullptr, nullptr)),
												nullptr)))))),
						UBTI(new BTI(1,
								UBTI(new BTI(0,
										nullptr,
										UBTI(new BTI(0,
												UBTI(new BTI(1,nullptr,
														UBTI(new BTI(1,nullptr,nullptr)))),
												UBTI(new BTI(0,nullptr,nullptr)))))),
								UBTI(new BTI(0,
										nullptr,
										UBTI(new BTI(0, nullptr, nullptr))))))));

	// Paths:
	//  1000   =  8
	//  1001   =  9
	//  10110  = 22
	//  110011 = 51
	//  11000  = 24
	//  1100   = 12
	// ------------
	// Sum =    126

	cout << "Sum = " << SumRootToLeaf(root) << endl;
}
