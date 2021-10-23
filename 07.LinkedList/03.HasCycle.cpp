/*
 * 03.HasCycle.cpp
 *
 * Problem: Detect whether a linked list has cycle or not.
 *          If cycle exists then return the start of the cycle, otherwise null
 *
 *  Created on: Nov 1, 2017
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

// Move two pointers; slow and fast at double as slow. If they meet then there is a cycle.
// The reasoning is: The relative speed between then is 1, so they would catch up.
//					 if fast iterator jumps over the slow iterator,
//                   the slow iterator will equal to the fast iterator in next step.
//
//                   Relative speed is the reason that if fast moves at speed of 3 then they are
//                   not guaranteed to meet
//
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

int main()
{
	SN S(new Node(6));
	SN T(new Node(11, S));
	SN L(new Node(1, SN(new Node(2, SN(new Node(3, SN(new Node(4, SN(new Node(5, S))))))))));
	SN C(new Node(7, SN(new Node(8, SN(new Node(9, SN(new Node(10, T))))))));
	S->next = C;

	SN start = HasCycle(L);
	if(start == nullptr) {
		cout << "List does not have a cycle" << endl;
	} else {
		T->next = nullptr; // to break the cycle; so that shared_ptrs can be freed
		cout << "Cycle starts at node with value " << start->val << endl;
	}


}

