/*
 * 03.TopKInBST.cpp
 *
 * Problem: Find K largest elements in a BST
 *
 *  Created on: Mar 22, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			If we do reverse of inorder then we will get those k elements first.
//			For normal ascending inorder we do <L N R> so for descending we will need to do <R N L>

struct BSTNode{
	int data;
	unique_ptr<BSTNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BSTNode (int a, unique_ptr<BSTNode> b, unique_ptr<BSTNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BSTNode> UBSTN;
typedef vector<int> VI;

void FindKLargestInBSTHelper(const UBSTN& root, int k, VI* result)
{
	if(root != nullptr && ((int)result->size()) < k)
	{
		FindKLargestInBSTHelper(root->right, k, result);
		if (((int)result->size()) < k)
		{
			result->emplace_back(root->data);
			FindKLargestInBSTHelper(root->left, k, result);
		}
	}
}

VI FindKLargestInBST(const UBSTN& root, int k)
{
	VI result;
	FindKLargestInBSTHelper(root, k, &result);
	return result;
}


int main()
{
	UBSTN root = UBSTN(new BSTNode(19,
						UBSTN(new BSTNode(7,
								UBSTN(new BSTNode(3,
										UBSTN(new BSTNode(2, nullptr, nullptr)),
										UBSTN(new BSTNode(5, nullptr, nullptr)))),
								UBSTN(new BSTNode(11,
										nullptr,
										UBSTN(new BSTNode(17,
												UBSTN(new BSTNode(13, nullptr, nullptr)),
												nullptr)))))),
						UBSTN(new BSTNode(43,
								UBSTN(new BSTNode(23,
										nullptr,
										UBSTN(new BSTNode(37,
												UBSTN(new BSTNode(29,nullptr,
														UBSTN(new BSTNode(31,nullptr,nullptr)))),
												UBSTN(new BSTNode(41,nullptr,nullptr)))))),
								UBSTN(new BSTNode(47,
										nullptr,
										UBSTN(new BSTNode(53, nullptr, nullptr))))))));

	VI res = FindKLargestInBST(root, 5);

	for(int i: res) {
		cout << i << ", " ;
	}
	cout << endl;
}

