/*
 * 02.ReverseSubList.cpp
 *
 * Problem: Given a singly linked list and two positions, reverse the sublist between the positions
 *
 *  Created on: Oct 31, 2017
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

// Possible to do it in single pass.
// After start node is identified keep on reversing node by tracking wit extra nodes
SN ReverseSublist(SN L, int start, int finish)
{
	SN dummy_head (new Node(0, L));  // dummy_head->next will point to the start of the original list
	SN sublist_head = dummy_head;    // sublist_head->next will point to start of sublist to be reversed

	for(int k=1; k < start ; ++k) {
		sublist_head = sublist_head->next;
	}

	// sublist_head->next will be the first node of the sublist

	// Start the reverse from the SECOND node, as first node is by default reversed
	SN prev = sublist_head->next;
	for(int k=start+1 ; k <= finish ; ++k) {
		// Invariant: List reversed until now. Put next element at the start of the sublist
		// Notice: Prev do not change; point to the last node of the reversed sublist

		SN toMove = prev->next;       // Node to move is the prev->next
		prev->next = toMove->next;    // Prev->next will now point to the next node
		toMove->next = sublist_head->next; // Node moved will point to what head points
		sublist_head->next = toMove;  // Head will point to new node moved
	}

	return dummy_head->next;
}

void PrintSmartList(SN head) {
	cout << "List: ";
	while(head != nullptr) {
		cout << head->val << " -> ";
		head = head->next;
	}
	cout << "null" << endl;
}

int main()
{
	SN L(new Node(1, SN(new Node(2, SN(new Node(3, SN(new Node(4, SN(new Node(5))))))))));

	SN R = ReverseSublist(L,2,4);
	PrintSmartList(R);
}
