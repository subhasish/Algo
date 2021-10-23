/*
 * HC.09.ListZipping.cpp
 *
 * Problem: Zipping of a list L is defined as interleaving of nodes numbered 0,1,2,...
 * 			with the nodes numbered (n-1),(n-2),... where n is the number of nodes in
 * 			the list.
 * 			Implement the zip function.
 *
 *  Created on: Nov 3, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Just need to find the middle of the list. Then reverse the second half and
//			interleave them.

struct Node {
	int val;
	shared_ptr<Node> next;

	Node(int a, shared_ptr<Node> p=nullptr): val(a), next(p) {}
};

typedef shared_ptr<Node> SN;

SN ReverseList(SN list);
void PrintSmartList(SN head);

SN ListZipping(SN list) {
	SN dummy_head(new Node(0,list));
	SN middle, slow, fast, prev_slow;

	// Find the middle
	slow = fast = prev_slow = list;
	while(fast != nullptr) {
		fast = fast->next;
		prev_slow = slow;		// Used to break the two lists
		slow = slow->next;
		if(fast != nullptr) {
			fast = fast->next;
		}
	}
	// Could also be done using only increment slow when both fast and fast->next is not null.
	// Then slow actually is the prev_slow. And second half starts from slow->next.

	// Break the two lists
	prev_slow->next = nullptr;
	middle = slow;

	// Reverse the second half
	middle = ReverseList(middle);

	// Interleave the two lists
	SN head = dummy_head;
	for (SN p=list, q=middle; (p != nullptr || q != nullptr) ;) {
		if(p != nullptr) {
			head->next = p;
			head = p;
			p = p->next;
		}
		if(q != nullptr) {
			head->next = q;
			head = q;
			q = q->next;
		}
	}

	return dummy_head->next;
}

SN ReverseList(SN list) {
	SN dummy_head(new Node(0,list));	// dummy_head->next will point to the head of the list

	SN p=list->next;					//** Tricky initialization
	list->next = nullptr;				//** Otherwise infinite loop

	while( p != nullptr ) {				// Traverse list with p pointer and move node to fist of the list
		SN p_next = p->next;			// Next node where p will point
		p->next = dummy_head->next;		// That node will now point to whatever the head is pointing now
		dummy_head->next = p;			// Head will point to that the new node
		p = p_next;
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

	SN R = ListZipping(L);
	PrintSmartList(R);
}
