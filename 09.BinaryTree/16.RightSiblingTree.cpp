/*
 * 16.RightSiblingTree.cpp
 *
 * Problem: Each Binary tree node has a next field that should point to the sibling right to it.
 *          1. Given a perfect binary tree, populate the next field of the tree nodes.
 *          2. Given a general tree populate the next field of the tree nodes.
 *
 *  Created on: Jan 15, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Full binary tree: every nodes other than leaves has two children
// Perfect binary tree: A full binary tree where all leaves are at the same level, and every parent has two children
// Complete binary tree: All levels except the last is completely filled, and in last nodes are as far left as possible.

// Solution:
//     For perfect binary tree:
//          Next node of a left child is the right child. **Next node of a right child is the left child of the sibling of its parent.**
//          Time complexity O(n), space complexity O(1)
//     For general binary tree:
//          BFS should be able to compute the nodes in O(n) time and O(h) space.

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	BinaryTreeNode* next;  //Not owning

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b=nullptr, unique_ptr<BinaryTreeNode> c=nullptr) : data(a), left(move(b)), right(move(c)), next(nullptr) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;


void ConstrctRightSiblingPerfectTree(UBTI&  root)
{
	BTI* left_start = root.get();
	while (left_start != nullptr && left_start->left != nullptr) {
		// While sitting at parent, we will be populating next field for child level

		BTI* iter = left_start;
		while(iter) {
			// Populate left child's next field
			iter->left->next = iter->right.get();

			// Populate right child's next field
			if(iter->next != nullptr) {
				iter->right->next = iter->next->left.get();
			}

			iter = iter->next;
		}

		left_start = left_start->left.get();
	}
}

typedef vector<int> VI;
typedef vector<VI> VVI;

VVI ConstrctRightSiblingGeneral(UBTI&  root)
{
	BTI* prev = nullptr;
	VVI result;

	queue<BTI*> current;
	current.push(root.get());

	while(!current.empty()) {
		queue<BTI*> next;
		VI int_res;
		while (!current.empty()) {
			BTI* p = current.front();
			if(prev != nullptr) {
				prev->next = p;
			}
			int_res.push_back(p->data);
			prev = p;

			if(p->left != nullptr) {
				next.push(p->left.get());
			}
			if(p->right != nullptr) {
				next.push(p->right.get());
			}

			current.pop();
		}
		current = next;
		prev = nullptr;
		result.push_back(int_res);
	}

	return result;
}

void PrintRightSiblingsPerferctTree(UBTI& root) {
	BTI* left_iter = root.get();
	cout << "Perfect binary tree: " << endl;
	while (left_iter != nullptr) {
		BTI* iter = left_iter;
		while(iter != nullptr) {
			cout << iter->data << " ";
			iter = iter->next;
		}
		cout << endl;
		left_iter = left_iter->left.get();
	}
}

void PrintRightSiblingsGeneral(VVI t)
{
	cout << "Tree: " << endl;
	for(size_t i=0; i<t.size() ; ++i) {
		for(size_t j=0; j<t[i].size() ; ++j) {
			cout << t[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	UBTI perfect_root = UBTI(new BTI(1,
							UBTI(new BTI(2,
									UBTI(new BTI(4)),
									UBTI(new BTI(5)))),
							UBTI(new BTI(3,
									UBTI(new BTI(6)),
									UBTI(new BTI(7))))));
	ConstrctRightSiblingPerfectTree(perfect_root);
	PrintRightSiblingsPerferctTree(perfect_root);
	cout << endl << endl;

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

	VVI r_tree = ConstrctRightSiblingGeneral(root);
	PrintRightSiblingsGeneral(r_tree);

}
