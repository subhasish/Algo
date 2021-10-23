/*
 * 04.OverlappingNoCycleList.cpp
 *
 * Problem: Determine if two list has any overlap or not. Assume no cycle.
 *          If overlap exists then return the first node of the overlap.
 *
 *  Created on: Nov 4, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

struct Node
{
	int val;
	shared_ptr<Node> next;

	Node(int a=0, shared_ptr<Node> p=nullptr) :val(a), next(p) {}
	~Node() { cout << "Node with value " << val << " is being destroyed" << endl; }
};

typedef shared_ptr<Node> SN;

int ListLength(SN L)
{
	int length=0;
	while(L != nullptr) {
		L = L->next;
		++length;
	}
	return length;
}


void AdvanceByLength(SN* L, int k)
{
	while(k--) {
		(*L) = (*L)->next;
	}
}

// Detecting existence of overlap is easy. Just check if tail nodes are same or not.
// To detect the first overlapping node:
//     compute length of each list and move longer one ahead so that each meet at first overlapping node when moved one by one
SN OverlappingNoCycleList(SN L1, SN L2)
{
	int len1 = ListLength(L1), len2 = ListLength(L2);

	//Advancing using a function is easy as to keep the advanced pointer in original pointer itself
	AdvanceByLength((len1 > len2) ? &L1 : &L2, abs(len1-len2) );

	while(L1 != L2) {
		L1 = L1->next;
		L2 = L2->next;
	}

	return L1; // nullptr implies no overlap
}

int main()
{
	SN C(new Node(7, SN(new Node(8, SN(new Node(9, SN(new Node(10))))))));
	SN L1(new Node(1, C));
	SN L2(new Node(2, SN(new Node(3, SN(new Node(4, SN(new Node(5, SN(new Node(6,C))))))))));

	SN start = OverlappingNoCycleList(L1, L2);

	if(start == nullptr) {
		cout << "Lists do not have overlap" << endl;
	} else {
		cout << "Overlap starts at node with value " << start->val << endl << endl;
	}
}


