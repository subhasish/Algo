/*
 * 04.LCAOptimized.cpp
 *
 * Problem: Write program to find LCA (Lowest Common Ancestor) in a binary tree that takes time proportional to the distance of the nodes.
 * 			Earlier solution we have seen computes path till root even if the nodes are very near to each other.
 *
 *  Created on: Feb 22, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: We can move up in tandem (alternate between two nodes) and store visited nodes in a hash table
//
// C++:
//			 Storing and checking can be simultaneously done by emplace() or insert()

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	BinaryTreeNode* parent;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)), parent(nullptr) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

BinaryTreeNode* LCA(UBTI& node1, UBTI& node2)
{
	unordered_set<BTI*> visited;

	BTI* iter1 = node1.get();
	BTI* iter2 = node2.get();

	while(iter1 || iter2)
	{
		if(iter1)
		{
			if(visited.emplace(iter1).second == false)
			{
				return iter1;
			}
			iter1 = iter1->parent;
		}

		if(iter2)
		{
			if(visited.emplace(iter2).second == false)
			{
				return iter2;
			}
			iter2 = iter2->parent;
		}
	}

	return nullptr;
}

// Do not consider this in time complexity
void PopulateParent(UBTI& root) {
	if(root == nullptr) {
		return;
	}

	if(root->left != nullptr) {
		root->left->parent = root.get();
		PopulateParent(root->left);
	}

	if(root->right != nullptr) {
		root->right->parent = root.get();
		PopulateParent(root->right);
	}
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

	PopulateParent(root);

	BTI* lca = LCA(root->left->left, root->left->right->right);

	cout << lca->data << endl;

}
