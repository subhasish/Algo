/*
 * 02.FirstGreaterThanK.cpp
 *
 * Problem: Find the first value greater than a given value inside a BST
 *
 *  Created on: Mar 22, 2018
 *      Author: subha
 */

//Next line for MinGW bug
#define __USE_MINGW_ANSI_STDIO 0

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Sounds like a binary search in the sorted array. But here we have a tree instead of array.
//
//			Solution could be to follow inorder and find first element greater than the given node.
//			But here we are not fully utilizing the BST property. We can avoid looking some subtree altogether.
//			If a node is smaller we do not need to look at its left subtree.
//			If a node is larger, it could be solution, but we do not need to look at its left subtree.
//
//			So basically we need to store the best candidate for the result and update the candidate as we
//			iteratively descend through the tree.

struct BSTNode{
	int data;
	unique_ptr<BSTNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BSTNode (int a, unique_ptr<BSTNode> b, unique_ptr<BSTNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BSTNode> UBSTN;


BSTNode* FindFirstGreaterThanK(const UBSTN& root, int k)
{
	BSTNode* p = root.get();
	BSTNode* result_so_far = nullptr;

	while(p != nullptr)
	{
		if(p->data <= k) {
			p = p->right.get();
		} else {
			result_so_far = p;
			p = p->left.get();
		}
	}

	return result_so_far;
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

	BSTNode* res = FindFirstGreaterThanK(root, 23);
	cout << "Greater than 23: " << (res == nullptr ? "Not found" : to_string(res->data)) << endl;

	res = FindFirstGreaterThanK(root, -1);
	cout << "Greater than -1: " << (res == nullptr ? "Not found" : to_string(res->data)) << endl;

	res = FindFirstGreaterThanK(root, 223);
	cout << "Greater than 223: " << (res == nullptr ? "Not found" : to_string(res->data)) << endl;
}
