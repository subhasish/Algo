/*
 * 13.PreorderReconstruction.cpp
 *
 * Problem: Reconstruct a binary tree from the preorder traversal with appropriate marker where left and right child are empty.
 *
 *  Created on: Jan 14, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: It is not clear to see where the left subtree ends.
//           But if we use recursion and if the recursion for left returns the last index used then we can start computing right from there.
//
//           This is classic example of what recursion can do.
//               We write the base case correctly.
//               Then we can assume that the routine correctly computes the left subtree, which will also tell us where the right subtree begins.

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

typedef vector<int*> VIP;



UBTI ReconstructPreorderHelper(VIP pre, int& index)
{
	if(pre[index] == nullptr) {  // Base case
		++index;
		return nullptr;
	}
	int* data = pre[index];
	++index;
	UBTI left = ReconstructPreorderHelper(pre, index);
	UBTI right = ReconstructPreorderHelper(pre, index);
	return UBTI(new BTI(*data, move(left), move(right)));

}

UBTI ReconstructPreorder(VIP pre)
{
	int index = 0;
	return ReconstructPreorderHelper(pre, index);
}

void PostOrder(UBTI& root) {
	if(root == nullptr) {
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	cout << "Postorder: " << root->data << endl;
}

int* t(int i) {
	return new int(i);
}

int main()
{
	VIP pre = {t(1),t(2),t(4),t(8),nullptr,nullptr,t(9),nullptr,nullptr,t(5),nullptr,t(10),t(13),nullptr,nullptr,nullptr,t(3),t(6),nullptr,t(11),t(14),nullptr,t(16),nullptr,nullptr,t(15),nullptr,nullptr,t(7),nullptr,t(12),nullptr,nullptr};
	//VI in  = {8,4,9,2,5,13,10,1,6,14,16,11,15,3,7,12};
	UBTI root = ReconstructPreorder(pre);

	PostOrder(root);
	// Output should be: 8,9,4,13,10,5,2,16,14,15,11,6,12,7,3,1
}
