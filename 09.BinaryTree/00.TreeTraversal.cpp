/*
 * 00.TreeTraversal.cpp
 *
 * Problem: Create basic binary tree and do basic traversal like preorder, inorder and postorder
 *
 *  Created on: Jan 8, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Preorder:  N L R
// Inorder:   L N R
// Postorder: L R N
// Left always processed before Right. The position of accessing current node data distinguish the 3.


template<typename T>
struct BinaryTreeNode{
	T data;
	unique_ptr<BinaryTreeNode<T>> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode<T> (T a, unique_ptr<BinaryTreeNode<T>> b, unique_ptr<BinaryTreeNode<T>> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef BinaryTreeNode<int> BTI;
typedef unique_ptr<BTI> UBTI;

void TreeTraversal(UBTI& root)
{
	if(root) {
		cout << "Preorder: " << root->data << endl;

		TreeTraversal(root->left);

		//cout << "Inorder: " << root->data << endl;

		TreeTraversal(root->right);

		//cout << "Postorder: " << root->data << endl;
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

	TreeTraversal(root);
}


