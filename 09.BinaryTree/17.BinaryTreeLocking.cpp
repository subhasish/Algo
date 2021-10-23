/*
 * 17.BinaryTreeLocking.cpp
 *
 * Problem: Design APIs to lock or unlock nodes in binary tree.
 *          A node cannot be locked if any of its descendant or ancestor is locked.
 *			Example: All leafs can be locked simultaneously.
 *
 *			Assume each node can store its parent.
 *
 *  Created on: Jan 15, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Store number of descendants currently locked in each node
//           Lock and unlock will update all the ancestors in O(h).
//
//           But is locked check is still O(1)

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	BinaryTreeNode* parent;  //Not owning

	bool locked;
	int num_decendants_locked;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)), parent(nullptr), locked(false), num_decendants_locked(0) {}

	bool IsLocked() {
		return locked;
	}

	bool CanLock() {
		return !(locked || (num_decendants_locked > 0));
	}

	bool Lock();

	void Unlock();
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;


bool BTI::Lock() {
	if(!CanLock()) {
		return false;
	}

	BTI* p = parent;
	while (p != nullptr) {
		if (p->IsLocked()) {
			return false;
		}
		p = p->parent;
	}

	//That means we can lock the node
	this->locked = true;

	// update ancestors
	p= parent;
	while(p != nullptr) {
		++p->num_decendants_locked;
		p = p->parent;
	}
	return true;
}

void BTI::Unlock()
{
	this->locked = false;

	BTI* p = this->parent;
	while(p != nullptr) {
		--p->num_decendants_locked;
		p = p->parent;
	}

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

	PopulateParent(root);

	cout << root->left->left->Lock() << endl;          // True
	cout << root->left->left->right->Lock() << endl;   // False
	cout << root->left->right->Lock() << endl;         // True
	cout << root->right->left->right->Lock() << endl;  // True
	cout << root->right->left->right->Lock() << endl;  // False
	cout << root->right->right->right->Lock() << endl; // True

}
