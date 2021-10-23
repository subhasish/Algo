/*
 * 05.OverlappingList.cpp
 *
 * Problem: Determine if two list has any overlap or not. Lists may have cycle.
 *          If overlap starts before cycle then return the first node of the overlap.
 *          If overlap starts on the cycle then return any node of either of the lists meeting the cycle.
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

// Move two pointers; slow and fast. If they meet then there is a cycle.
// The reasoning is: if fast iterator jumps over the slow iterator,
//                   the slow iterator will equal to the fast iterator in next step.
// Start of cycle: Find length of the cycle, say C.
//                 Now start two iterator one C ahead. Move them in tandem. When they meet that is the start node.
//                 If cycle start at x node ahead. When 2nd node reaches x, 1st node is at x+C. So they meet at the start.
SN HasCycle(SN L)
{
	SN slow = L;
	SN fast = (L->next) ? L->next->next : nullptr;
	bool hasCycle = false;

	while(fast && slow) {
		if (fast == slow) {
			hasCycle = true;
			break;
		}
		fast = (fast->next) ? fast->next->next : nullptr;
		slow = slow->next;
	}

	if(!hasCycle)
		return nullptr;

	//Now list has cycle. We find the cycle length C
	int C=1;
	slow = slow->next;
	while(slow != fast) {
		++C;
		slow = slow->next;
	}

	//Start from beginning and move one C ahead
	fast = slow = L;
	while(C>0) {
		fast = fast->next;
		--C;
	}

	//Now move them in tandem until they meet at the start of the loop
	while(slow != fast) {
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

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

int ListDistance(SN start, SN end) {
	int count = 0;
	while (start != end) {
		start = start->next;
		++count;
	}
	return count;
}

// Detect which lists has cycle. Depending on that use previous algos.
// Check for disjoint cycle
// If they overlap and one has cycle then BOTH should have the cycle.
// For that case do the following:
//    If two list meet before cycle starts then return that node
//       Compute length until start of the cycle for both. Use similar to previous logic.
//    Otherwise, both meet at cycle. Return any start.
SN OverlappingList(SN L1, SN L2)
{
	SN root1 = HasCycle(L1);
	SN root2 = HasCycle(L2);

	if(!root1 && !root2) {
		//Case 1: None of the list has cycle
		return OverlappingNoCycleList(L1, L2);
	} else if((!root1 && root2) || (root1 && !root2)) {
		//Case 2: One list has cycle, other not. No overlap possible
		return nullptr;
	}

	//Now both list has cycle

	//Check for disjoint cycle
	SN temp = root1;
	do {
		temp = temp->next;
	} while( temp != root1 && temp != root2);

	//Case 3: Disjoint cycle
	if(temp != root2) { //Do NOT check equality with root1. Breaks when both are same
		return nullptr;
	}

	//Now both list share same cycle

	//First see if they meet before cycle starts.
	//Compute length up to cycle for both. Move longer list ahead. Then move together.
	//If they meet then they overlap before the cycle starts
	int dis1 = ListDistance(L1, root1);
	int dis2 = ListDistance(L2, root2);

	AdvanceByLength((dis1 > dis2) ? &L1 : &L2, abs(dis1 - dis2));
	while(L1 != root1) {
		//Case 4: Overlaps before meeting cycle
		if(L1 == L2) {
			return L1;
		}
		L1 = L1->next;
		L2 = L2->next;
	}

	//Case 5: Do not meet before cycle. Then any start of cycle can be considered as start
	return root1;
}


int main()
{
	SN T(new Node(11));
	SN C(new Node(7, SN(new Node(8, SN(new Node(9, SN(new Node(10,T))))))));
	T->next = C;
	SN L1(new Node(1, C));
	SN L2(new Node(2, SN(new Node(3, SN(new Node(4, SN(new Node(5, SN(new Node(6,C))))))))));

	SN start = OverlappingList(L1, L2);

	if(start == nullptr) {
		cout << "Lists do not have overlap" << endl;
	} else {
		T->next = nullptr; // to break the cycle; so that shared_ptrs can be freed
		cout << "Overlap starts at node with value " << start->val << endl << endl;
	}
}




