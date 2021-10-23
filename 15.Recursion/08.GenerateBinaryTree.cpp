/*
 * 08.GenerateBinaryTree.cpp
 *
 * Problem: Write a program which returns all distinct binary trees with specified number of nodes
 *
 *  Created on: Apr 14, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			A binary tree of n nodes can be created by two subtrees whose total is (n-1) nodes.
//			So if we have solution of all (n-1) nodes then we can get solution for n nodes
//			by trying out all possible values of left and right subtrees.
//			So this can be solved using recursion.
//
// Time complexity:
//			The number of calls to the recursive function follows Catalan number.


struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

typedef vector<UBTI> VUBTI;

VUBTI GenerateAllBinaryTrees(int num_nodes)
{
	VUBTI result;

	if(num_nodes==0) {
		result.emplace_back(nullptr);
	}

	for(int num_left_tree = 0 ; num_left_tree < num_nodes ; ++num_left_tree) {
		int num_right_tree = num_nodes - 1 - num_left_tree;

		VUBTI left_subtrees = GenerateAllBinaryTrees(num_left_tree);
		VUBTI right_subtrees = GenerateAllBinaryTrees(num_right_tree);

		// Now generate all combinations of left subtrees and right subtrees
		for(UBTI& left: left_subtrees) {
			for(UBTI& right: right_subtrees) {
				result.emplace_back(unique_ptr<BinaryTreeNode>(new BinaryTreeNode(0, move(left), move(right))));
			}
		}
	}

	return result;
}

int main()
{
	VUBTI result = GenerateAllBinaryTrees(5);

	cout << "Total number of trees with 5 nodes: " << result.size() << endl;
}
