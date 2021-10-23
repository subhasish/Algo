/*
 * 10.InsertDeleteBST.cpp
 *
 * Problem: Implement insert and delete function of BST
 *
 *  Created on: Mar 25, 2018
 *      Author: subha
 */

#include<bits/stdc++.h>

using namespace std;

// Solution:
//			Implement standard BST insert and delete
//			Insert:
//				Search and insert in a leaf. Only consider left and right child where to insert.
//			Delete:
//				3 cases: no child, one child and two children
//
// C++:
//			unique_ptr.reset(p) : deletes the current resource and takes ownership of p
//			unique_ptr.release(): yields ownership and return the pointer

struct BSTNode{
	int data;
	unique_ptr<BSTNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BSTNode (int a, unique_ptr<BSTNode> b, unique_ptr<BSTNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BSTNode> UBSTN;

struct BinarySearchTree
{
	UBSTN root;

	BinarySearchTree(): root(nullptr) {}

	bool Insert(int key)
	{
		if(root == nullptr) {
			root = UBSTN(new BSTNode(key, nullptr, nullptr));
		} else {
			BSTNode* curr = root.get();
			BSTNode* parent = nullptr;

			while(curr)
			{
				parent = curr;
				if(key == curr->data) {
					return false;
				} else if(key < curr->data) {
					curr = curr->left.get();
				} else {
					curr = curr->right.get();
				}
			}

			// Insert key according to the key and parent
			if(key < parent->data) {
				parent->left = UBSTN(new BSTNode(key, nullptr, nullptr));
			} else {
				parent->right = UBSTN(new BSTNode(key, nullptr, nullptr));
			}
		}
		return true;
	}

	bool Delete(int key)
	{
		// Find the node with the key
		BSTNode* curr = root.get();
		BSTNode* parent = nullptr;

		while(curr && curr->data != key) {
			parent = curr;
			curr = (key < curr->data) ? curr->left.get() : curr->right.get();
		}

		if(!curr) {		// Not found
			return false;
		}

		BSTNode* key_node = curr;

		// Handle case 2 and 3 together for right child.
		// No change in root.
		if(key_node->right) {
			// Find the minimum in the right subtree
			BSTNode* r_key_node = key_node->right.get();
			BSTNode* r_parent = key_node;
			while(r_key_node->left) {
				r_parent = r_key_node;
				r_key_node = r_key_node->left.get();
			}
			key_node->data = r_key_node->data;

			// Move links to erase the node
			if(r_parent->left.get() == r_key_node) {
				r_parent->left.reset(r_key_node->right.release());	// Point to its right, if any
			} else {
				r_parent->right.reset(r_key_node->right.release());	// Point to its right, if any
			}
		}
		else 	// Case 1 and 2 for left child
		{
			// Update root if needed
			if(root.get() == key_node) {
				root.reset(key_node->left.release());		// Point to its left, if any
			} else {
				if(parent->left.get() == key_node) {
					parent->left.reset(key_node->left.release());	// Point to its left, if any
				} else {
					parent->right.reset(key_node->left.release());	// Point to its left, if any
				}
			}
		}
		return true;
	}

	void Inorder()
	{
		cout << "Inorder of the BST: ";
		InorderHelper(root);
		cout << endl;
	}

private:
	void InorderHelper(const UBSTN& root)
	{
		if(root == nullptr) return;

		InorderHelper(root->left);
		cout << root->data << ", ";
		InorderHelper(root->right);
	}
};


int main()
{
	BinarySearchTree bst;

	bst.Insert(8);
	bst.Insert(22);
	bst.Insert(33);
	bst.Insert(12);
	bst.Insert(2);
	bst.Insert(21);

	bst.Inorder();

	bst.Delete(8);
	bst.Delete(22);
	bst.Delete(12);
	bst.Insert(6);
	bst.Insert(31);
	bst.Insert(17);

	bst.Inorder();
}
