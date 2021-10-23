/*
 * HC.13.PostorderNoRecursion.cpp
 *
 * Problem: Implement postorder traversal without recursion.
 *
 *  Created on: Jan 12, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Clearly we will have to implement recursion using stack
//
//			The main difference between preorder and both inorder and postorder is that later two
//			needs to remember if one subtree has been explored or not. With two recursive calls back to back,
//			we know when to explore the right call stack and when both are done an we can process the
//			node, that is it is just following binary tree structure.
//
//			But simple stack is linear and one node in stack has only previous element. But in tree,
//			two element has one parent. So no direct replacement. We need to remember which child to
//			explore next or whether all of them has been explored and its time to process/print current.
//
//			There is an alternative approach as well. If we notice carefully then we can see that
//			post order can be computed as reverse of inverted preorder.
//			Preorder: N L R
//			Inverted Preorder: N R L (traverse right before left)
//			Reverse of inverted preorder: L R N == Post order
//
//

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;
typedef vector<int> VI;

VI InvertePreOrder(UBTI& root);
void PrintVector(VI& list);

void PostorderNoRecursion(UBTI& root)
{
	VI result = InvertePreOrder(root);
	VI postorder = {result.rbegin(), result.rend()};

	cout << "Postorder: " << endl;
	PrintVector(postorder);
}

VI InvertePreOrder(UBTI& root)
{
	VI result;
	stack<BTI *> path;
	path.push(root.get());

	while(!path.empty()) {
		BTI* curr = path.top();
		result.emplace_back(curr->data);
		path.pop();

		// Put left in the stack first so that it gets processed later
		if(curr->left.get() != nullptr) {
			path.push(curr->left.get());
		}
		if(curr->right.get() != nullptr) {
			path.push(curr->right.get());
		}
	}
	return result;
}

void PrintVector(VI& list) {
	for(int i: list) {
		cout << i << " ";
	}
	cout << endl;
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

	PostorderNoRecursion(root);

	//Postorder: 8, 9, 4, 13, 10, 5, 2, 16, 14, 15, 11, 6, 12, 7, 3, 1
}
