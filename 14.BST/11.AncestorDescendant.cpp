/*
 * 11.AncestorDescendant.cpp
 *
 * Problem: Write a program that takes two nodes in a BST and a third node and determines
 * 			if one of the two nodes is proper ancestor and the other one is proper descendant of the
 * 			middle node.
 *
 *  Created on: Mar 26, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Simple solution would be to search one in the subtree of the other and if middle is found in the path the done.
//			This might take whole height to traverse if we start with wrong node.
//			Better is search for the middle from both the nodes in interleaved fashion.
//			If middle is found then search the other node from the middle.

struct BSTNode{
	int data;
	unique_ptr<BSTNode> left, right;

	//For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
	BSTNode (int a, unique_ptr<BSTNode> b, unique_ptr<BSTNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BSTNode> UBSTN;

bool PairIncludesAncestorAndDescendant(const UBSTN& root, int node_0, int node_1, int middle)
{
	BSTNode *search_0=root.get(), *search_1=root.get();

	// Get to the actual BST nodes
	while(node_0 != search_0->data) {
		if(node_0 < search_0->data) {
			search_0 = search_0->left.get();
		} else {
			search_0 = search_0->right.get();
		}
	}
	while(node_1 != search_1->data) {
		if(node_1 < search_1->data) {
			search_1 = search_1->left.get();
		} else {
			search_1 = search_1->right.get();
		}
	}

	BSTNode *p0=search_0, *p1=search_1;
	// Perform interleaved search for middle
	while((p0 == nullptr || p0->data != middle) && (p1 == nullptr || p1->data != middle) && (p0 != search_1) && (p1 != search_0) && (p0 || p1)) {
		if(p0) {
			p0 = (middle < p0->data) ? p0->left.get() : p0->right.get();
		}
		if(p1) {
			p1 = (middle < p1->data) ? p1->left.get() : p1->right.get();
		}
	}

	// If middle not found
	if(((p0 == nullptr || p0->data != middle) &&(p1 == nullptr || p1->data != middle)) || p0 == search_1 || p1 == search_0) {
		return false;
	}

	// Now search from middle
	if(p0 && p0->data == middle) {
		p1=p0;
		while(p1 && p1 != search_1) {
			p1 = (search_1->data < p1->data) ? p1->left.get() : p1->right.get();
		}
		if(p1 && p1 == search_1) {
			return true;
		} else {
			return false;
		}
	}
	if(p1 && p1->data == middle) {
		p0=p1;
		while(p0 && p0 != search_0) {
			p0 = (search_0->data < p0->data) ? p0->left.get() : p0->right.get();
		}
		if(p0 && p0 == search_0) {
			return true;
		} else {
			return false;
		}
	}
	return false;
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

	cout << "Test 31, 43 and 37: " << PairIncludesAncestorAndDescendant(root, 31, 43, 37) << endl;
	cout << "Test 31, 43 and 11: " << PairIncludesAncestorAndDescendant(root, 31, 43, 11) << endl;
}
