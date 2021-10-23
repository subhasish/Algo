/*
 * 05.RebuildBSTFromTraversal.cpp
 *
 * Problem: Given the sequence of a BST inorder traversals can you rebuild the BST from it?
 * 			Solve the same problem for preorder and postorder traversal sequence.
 *
 * 			Assume all nodes have unique key.
 *
 *  Created on: Mar 23, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Try with different 3 node trees and see that many can produce same inorder sequence.
//			So there is no unique tree from an inorder sequence.
//
//			For preorder and postorder case is different. As it is BST the inorder is implied, that is sorted.
//			So theoretically we have two sequence and we should be able to construct the BST.
//
//			In practice, once we figure out root (1st for preorder / last for postorder) all smaller elements
//			will represent the left subtree and all larger nodes will represent the right subtree.

struct BSTNode{
	int data;
	unique_ptr<BSTNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BSTNode (int a, unique_ptr<BSTNode> b, unique_ptr<BSTNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BSTNode> UBSTN;
typedef vector<int> VI;

// This function has worst case time complexity O(n^2) as for each node we potentially searching rest of the strings to find
// the partition of the subtrees.
// It is possible keep creating BST node as we traverse each node
UBSTN RebuildBSTFromPreorderHelper(const VI& preorder, int start, int end)
{
	if(start > end) return nullptr;
	if(start < 0 || start >= (int)preorder.size()) return nullptr;
	if(end < 0 || end >= (int)preorder.size()) return nullptr;

	UBSTN root(new BSTNode(preorder[start], nullptr, nullptr));
	int pos;
	for(pos = start+1; pos <= end ; ++pos)
	{
		if(preorder[pos] > preorder[start])
			break;
	}
	root->left = move(RebuildBSTFromPreorderHelper(preorder,start+1,pos-1));
	root->right = move(RebuildBSTFromPreorderHelper(preorder,pos,end));

	return root;
}

// To avoid traversing each node multiple times, we need to create BST node as we traverse each node
// Sitting at each node if we have range of valid values of current (say left) subtree and
//   current node fall outside then we know this node should node should skipped for that subtree
// To facilitate reading correct node we need to pass around the index as nodes gets read,
//   next node need to know where to read from

UBSTN RebuildBSTFromPreorderOnValueRange(const VI& preorder, int low, int high, int* root_idx_ptr)
{
	// Build a BST on the subtree rooted at root_idx from the sequence on keys in range [low, high]
	int& root_idx = *root_idx_ptr;

	// reached end
	if(root_idx >= (int)preorder.size())  return nullptr;

	// outside range: should skip this node for this subtree
	if(preorder[root_idx] < low || preorder[root_idx] > high) return nullptr;

	// Came for correct subtree: create the node
	int root = preorder[root_idx];
	// Note that it updates root_idx; so order of calls are very important
	++root_idx;
	UBSTN left_subtree = RebuildBSTFromPreorderOnValueRange(preorder, low, root, root_idx_ptr);
	UBSTN right_subtree = RebuildBSTFromPreorderOnValueRange(preorder, root, high, root_idx_ptr);

	return UBSTN(new BSTNode(root, move(left_subtree), move(right_subtree)));
}
UBSTN RebuildBSTFromPreorder(const VI& preorder)
{
	//return RebuildBSTFromPreorderHelper(preorder, 0, preorder.size()-1);

	int root_idx = 0;
	return RebuildBSTFromPreorderOnValueRange(preorder, numeric_limits<int>::min(), numeric_limits<int>::max(), &root_idx);
}

void InorderBST(const UBSTN& root)
{
	if(root == nullptr) return;

	InorderBST(root->left);
	cout << root->data << ", ";
	InorderBST(root->right);
}

int main()
{
	VI preorder = {19, 7, 3, 2, 5, 11, 17, 13, 43, 23, 37, 29, 31, 41, 47, 53};

	UBSTN tree = RebuildBSTFromPreorder(preorder);

	cout << "Inorder of the tree: " << endl;
	InorderBST(tree);
	cout << endl;
}
