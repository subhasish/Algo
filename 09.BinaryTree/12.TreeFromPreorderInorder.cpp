/*
 * 12.TreeFromPreorderInorder.cpp
 *
 * Problem: Reconstruct a binary tree from preorder and inorder traversal.
 *          Assume that each node has unique key.
 *
 *  Created on: Jan 14, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Preorder sequence gives us the key of the root node. Using that key in the inorder gives size of the subtrees
//           We can recursively build this tree.
//
// Optimization: Now every time finding the key in the inorder sequence will take O(n), giving total time O(n^2)
//               This can be optimized by building a hash table from keys to their positions in the inorder sequence

struct BinaryTreeNode{
	int data;
	unique_ptr<BinaryTreeNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

typedef vector<int> VI;


UBTI TreeFromPreorderInorderHelper(VI& pre, int pre_start, int pre_end,
								   VI& in, int in_start, int in_end,  //Parameter in is not required as index captures all the necessary information
								   map<int, size_t>& index)
{
	if(pre_end < pre_start || in_end < in_start) {
		return nullptr;
	}

	size_t root_index = index[pre[pre_start]];
	size_t left_size = root_index - in_start;

	return UBTI(new BTI{
		pre[pre_start],
		TreeFromPreorderInorderHelper(pre, pre_start+1, pre_start+left_size,
									  in, in_start, in_start+left_size-1,
									  index),
		TreeFromPreorderInorderHelper(pre, pre_start+left_size+1, pre_end,
									  in, root_index+1, in_end,
									  index)
	});
}

UBTI TreeFromPreorderInorder(VI& pre, VI& in)
{
	map<int, size_t> index;
	for(size_t i=0; i< in.size() ; i++) {
		index[in[i]] = i;
	}

	return TreeFromPreorderInorderHelper(pre, 0, pre.size()-1, in, 0, in.size()-1, index);
}

void PostOrder(UBTI& root) {
	if(root == nullptr) {
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	cout << "Postorder: " << root->data << endl;
}

int main()
{
	VI pre = {1,2,4,8,9,5,10,13,3,6,11,14,16,15,7,12};
	VI in  = {8,4,9,2,5,13,10,1,6,14,16,11,15,3,7,12};
	UBTI root = TreeFromPreorderInorder(pre, in);

	PostOrder(root);
	// Output should be: 8,9,4,13,10,5,2,16,14,15,11,6,12,7,3,1
}
