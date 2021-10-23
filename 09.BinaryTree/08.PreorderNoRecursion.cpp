/*
 * 08.PreorderNoRecursion.cpp
 *
 * Problem: Implement preorder traversal without recursion
 *
 *  Created on: Jan 13, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Clearly we will have to implement recursion using stack.
//           Remember to push right child in to the stack before the left child.
//
//           Much simpler than inorder, as no need remember the visited node.

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;


void PreorderNoRecursion(UBTI& root) {
	stack<BTI *> st;
	BTI* p = root.get();

	st.push(p);
	while(!st.empty()) {
		p = st.top();
		st.pop();

		cout << "Preorder: " << p->data << endl;
		if(p->right != nullptr) {
			st.push(p->right.get());
		}
		if(p->left != nullptr) {
			st.push(p->left.get());
		}
	}
}

int main() {
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

		PreorderNoRecursion(root);

		//Output should be: 1,2,4,8,9,5,10,13,3,6,11,14,16,15,7,12
}
