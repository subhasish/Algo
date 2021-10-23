/*
 * 03.LCAnoParent.cpp
 *
 * Problem: Compute lowest common ancestor (LCA) of two nodes in a binary tree without using parent pointer.
 *
 *  Created on: Jan 9, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// **Solution: LCA is the node for which one node appear in left sub-tree and another appear in the right sub-tree.
//             To know whether we have found some node in children, it has to be post-order.
//             We have to count how many of them found in left and how many in right. If both are exactly one then only we found LCA.
//             Two information to return, LCA (if found) and number of nodes found. So, will use a helper function.

// Time complexity: O(n)

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

struct ReturnNode {
	int nodesFound;
	UBTI lca;
};

// In recursion (remember it is going up) consider root as one possible nodes to match with
ReturnNode LCAhelper(UBTI& root, UBTI& node1, UBTI& node2)
{
	if(root == nullptr)
		return {0, nullptr};

	ReturnNode left_r = LCAhelper(root->left, node1, node2);
	if(left_r.nodesFound == 2) {  // Both nodes found under left sub-tree
		return {2, move(left_r.lca)};
	}

	ReturnNode right_r = LCAhelper(root->right, node1, node2);
	if(right_r.nodesFound == 2) {  // Both nodes found under right sub-tree
		return {2, move(right_r.lca)};
	}

	int totalNodesFound = left_r.nodesFound + right_r.nodesFound +
			(node1 == root) + (node2 == root);

	return {totalNodesFound, totalNodesFound==2 ? move(root): nullptr};
}

UBTI LCA(UBTI& root, UBTI& node1, UBTI& node2)
{
	return LCAhelper(root, node1, node2).lca;
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

	UBTI lca = LCA(root, root->left->left, root->left->right->right);

	cout << lca->data << endl;

}
