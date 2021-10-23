/*
 * 04.LCAOfBST.cpp
 *
 * Problem: Compute LCA of two nodes in a BST.
 * 			Nodes do not have parent pointer.
 * 			Assume that each node has unique value.
 *
 *  Created on: Mar 23, 2018
 *      Author: subha
 */

//Next line for MinGW bug
#define __USE_MINGW_ANSI_STDIO 0

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			At LCA both node will appear in different subtrees.
//			Using BST property we can detect easily which subtree the node lies and that will help to arrive at the LCA fast.

struct BSTNode{
	int data;
	unique_ptr<BSTNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BSTNode (int a, unique_ptr<BSTNode> b, unique_ptr<BSTNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BSTNode> UBSTN;

BSTNode* FindLCAOfBST(const UBSTN& root, const UBSTN& a, const UBSTN& b)
{
	if(root == nullptr) return nullptr;
	if(a == nullptr) return b.get();
	if(b == nullptr) return a.get();

	BSTNode* p = root.get();

	int small = (a->data < b->data ? a->data : b->data);
	int large = (a->data < b->data ? b->data : a->data);

	while(p != nullptr) {
		if(large < p->data) {		// Both are in left
			p = p->left.get();
		} else if(small > p->data) { // Both are in right
			p = p->right.get();
		} else {				// Both are in different sides: LCA
			return p;
		}
	}

	return nullptr;
}

int main()
{
	UBSTN root = UBSTN(new BSTNode(19,
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

	BSTNode* lca = FindLCAOfBST(root, root->right->right->right, root->right->left->right->left->right);
	cout << "LCA of those two nodes: " << (lca == nullptr ? "Not found" : to_string(lca->data)) << endl;
}
