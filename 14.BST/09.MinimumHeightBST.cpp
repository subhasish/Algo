/*
 * 09.MinimumHeightBST.cpp
 *
 * Problem: Write a program to build a minimum height BST from a sorted array
 *
 *  Created on: Mar 25, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Put middle one in root and build the two sides recursively
//			 Time complexity T(n) = 2T(n/2) + O(1) which solves to T(n)=O(n)
//							Master theorem case 1: c < (log a base b); a=2,b=2,c=0

struct BSTNode{
	int data;
	unique_ptr<BSTNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BSTNode (int a, unique_ptr<BSTNode> b, unique_ptr<BSTNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BSTNode> UBSTN;
typedef vector<int> VI;

UBSTN BuildMinimumHeightBSTFromSortedHelper(const VI& sorted_array, int lo, int hi)
{
	if(lo > hi) return nullptr;
	if(lo == hi) return UBSTN(new BSTNode(sorted_array[lo], nullptr, nullptr));

	int mid = lo + (hi - lo) /2;
	return UBSTN(new BSTNode(sorted_array[mid],
			move(BuildMinimumHeightBSTFromSortedHelper(sorted_array, lo, mid-1)),
			move(BuildMinimumHeightBSTFromSortedHelper(sorted_array, mid+1, hi))));
}
UBSTN BuildMinimumHeightBSTFromSorted(VI sorted_array)
{
	return BuildMinimumHeightBSTFromSortedHelper(sorted_array, 0, sorted_array.size()-1);
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
	VI sorted = { 2, 4, 7, 8, 22, 35, 664, 7453, 8884};
	UBSTN root = BuildMinimumHeightBSTFromSorted(sorted);
	InorderBST(root);
}
