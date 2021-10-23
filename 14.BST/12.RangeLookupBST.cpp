/*
 * 12.RangeLookupBST.cpp
 *
 * Problem: In map for a location (p,q) finding nearest restaurant can be done by storing x and y coordinates of all restaurants
 * 			in two BSTs. Then we can take intersection of restaurants appearing in [p-D,p+D] and [q-D,q+D], D chosen heuristically.
 * 			Quadtrees and k-d trees are more robust for these applications, but this approach works well in practice.
 *
 * 			Write a program that takes a BST and an interval and returns the BST keys that lie in that range.
 *
 *  Created on: Mar 26, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Brute force approach is to do inorder traversal and see which nodes are in range. But it is waste if range is small.
//
//			Note that all nodes and their subtrees until we get to the LCA are not in range.
//			We can prune the tree and not do traversal over all node.
//
//			Time complexity = O(m + h) where m is the number of keys in the interval and h is the height
//
//			If the problem was to only count the number of nodes in the interval and
//			if nodes stores the size of its subtrees then search can be made faster, by skipping some subtrees: in O(h).

struct BSTNode{
	int data;
	unique_ptr<BSTNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BSTNode (int a, unique_ptr<BSTNode> b, unique_ptr<BSTNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BSTNode> UBSTN;
typedef vector<int> VI;

void RangeLookupInBSTHelper(const UBSTN& root, int lo, int hi, VI* res_ptr)
{
	VI& res = *res_ptr;

	if(root == nullptr) return;

	if(root->data >= lo && root->data <= hi) {
		// Doing in inorder; just in case result being in sorted helps something down the road
		RangeLookupInBSTHelper(root->left, lo, hi, res_ptr);
		res.emplace_back(root->data);
		RangeLookupInBSTHelper(root->right, lo, hi, res_ptr);
	} else if(root->data < lo) {								// Everything in right subtree
		RangeLookupInBSTHelper(root->right, lo, hi, res_ptr);
	} else {													// Everything in left subtree
		RangeLookupInBSTHelper(root->left, lo, hi, res_ptr);
	}
}

VI RangeLookupInBST(const UBSTN& root, int lo, int hi)
{
	VI res;
	RangeLookupInBSTHelper(root, lo, hi, &res);
	return res;
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

	VI res = RangeLookupInBST(root, 10, 30);
	for(int i: res) {
		cout << i << ", ";
	}
	cout << endl;

	res = RangeLookupInBST(root, 35, 41);
	for(int i: res) {
		cout << i << ", ";
	}
	cout << endl;
}
