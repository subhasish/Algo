/*
 * 14. CreateListOfLeaves.cpp
 *
 * Problem: Create a linked list of the leaves of a binary tree
 *          The leaves should appear in the left to right order.
 *
 *  Created on: Jan 14, 2018
 *      Author: subha
 */

// Solution: In any of the preorder, inorder, postorder traversal we visit left before right.
//           So if we just add a leaf doing such traversal then we are good.

#include <bits/stdc++.h>

using namespace std;

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

typedef list<int> LI;

LI ListOfLeaves(UBTI& root)
{
	LI leaves;
	if(root != nullptr) {
		if(root->left == nullptr && root->right == nullptr) {  // Leaf
			leaves.push_back(root->data);
		}
		else
		{
			// Traverse left first then right to maintain order
			leaves.splice(leaves.end(), ListOfLeaves(root->left));
			leaves.splice(leaves.end(), ListOfLeaves(root->right));
		}
	}
	return leaves;
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
	LI list = ListOfLeaves(root);

	cout << "Leaves (from left to right): ";
	for (LI::iterator it = list.begin(); it != list.end() ; ++it ) {
		cout << *it << " ";
	}
	cout << endl;
	//Output should be: 8 9 13 16 15 12
}
