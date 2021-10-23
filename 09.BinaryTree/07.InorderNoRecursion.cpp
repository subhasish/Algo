/*
 * 07.InorderNoRecursion.cpp
 *
 * Problem: Implement inorder traversal without recursion.
 *
 *  Created on: Jan 12, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Clearly we will have to implement recursion using stack
//
//			The main difference between recursion for inorder and stack is that recursion can
//			remember if one subtree has been explored or not. With two recursive calls back to back,
//			we know when to explore the right call stack, that is it is just following binary tree
//			structure.
//
//			But simple stack is linear and one node in stack has only previous element. But in tree,
//			two element has one parent. So no direct replacement. We need to remember which child to
//			explore next.
//
//			The solution used here does it by storing extra bit of information that whether the left
//			subtree of the node is explored or not. We call it visited flag.
//
//			If visited flag is not set we try to explore the left subtree and set the flag. We don't
//			pop the node from the stack so that it gets processed after its left subtree is processed.
//
//			If the visited flag is set then we pop that element from the stack. Process/print it and
//			then put right subtree in the stack to be processed.
//
// **Learning: Learned a lot regarding how to use smart pointers with containers.
//             STL containers always copy objects. So you cannot create container of references.
//             Instead, create container of raw pointers and then to get raw pointer from
//             unique_ptr use get() function.
//
//             For simple applications, moving the ownership to container using std::move() will work,
//             But not for complex cases.
//
// Postorder: Postorder is just a variation of inorder, where we need to push right and left if not visited.

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	bool visited;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)), visited(false) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

void InorderNoRecursion(UBTI& root)
{
	stack<BTI *> st;

	BTI* p = root.get();
	st.push(p);

	cout << "Inorder: " << endl;

	while(!st.empty()) {
		p = st.top();

		if(!p->visited && p->left != nullptr) {
			st.push(p->left.get());
			p->visited = true;

			continue;
		}
		else {
			st.pop();
			cout << " " << p->data ;

			if(p->right != nullptr) {
				st.push(p->right.get());
			}
		}
	}
	cout <<  endl;
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

	InorderNoRecursion(root);

	//Output should be: 8,4,9,2,5,13,10,1,6,14,16,11,15,3,7,12
}
