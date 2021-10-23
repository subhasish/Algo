/*
 * 00.BasicBST.cpp
 *
 * Problem: Write a basic BST program that finds if a given value is present in BST or not
 *
 *
 *  Created on: Mar 19, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Use the same data structure of unique pointer as in binary tree
//
// C++:
//			For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer


struct BSTNode{
	int data;
	unique_ptr<BSTNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BSTNode (int a, unique_ptr<BSTNode> b, unique_ptr<BSTNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BSTNode> UBSTN;

BSTNode* SearchBST(const UBSTN& root, int val)
{
	if(root == nullptr) return nullptr;
	if(root->data == val) return root.get();

	return (val < root->data) ? SearchBST(root->left, val) : SearchBST(root->right, val);
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

	cout << "Found 33: " << (nullptr != SearchBST(root, 33)) << endl;
	cout << "Found 37: " << (nullptr != SearchBST(root, 37)) << endl;
	cout << "Found 17: " << (nullptr != SearchBST(root, 17)) << endl;
	cout << "Found 47: " << (nullptr != SearchBST(root, 47)) << endl;
}


