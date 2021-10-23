/*
 * 01.MergeTwoSortedList.cpp
 *
 * Problem: Merge two sorted list into one
 *
 *  Created on: Oct 30, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int val;
	shared_ptr<Node> next;

	Node(int a=0, shared_ptr<Node> p=nullptr) : val(a), next(p) {}
	~Node() { cout << "Node with value " << val << " is destroyed" << endl; }
};

typedef shared_ptr<Node> SN;

// Append node to tail and update both node pointer and tail
void AppendList(SN* node, SN* tail) {
	(*tail)->next = (*node);
	*tail = *node;
	*node = (*node)->next;
	(*tail)->next = nullptr;
}

// Merge like merge-sort. Take the smaller one and put it in result
SN MergeTwoSortedList(SN& L1, SN& L2)
{
	//dummy head: to create a place holder for the result
	SN dummy_head (new Node());
	SN tail = dummy_head;

	//while both list ha element append smaller one in tail
	while(L1 && L2) {
		AppendList(L1->val < L2->val ? &L1 : &L2, &tail);
	}

	//Add rest of the remaining list
	tail->next = (L1 ? L1 : L2);

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
//	SN t1(new Node(7));
//	SN t2(new Node(3, t1));
//	SN L1(new Node(1, t2));

	SN L1(new Node(1, SN(new Node(3, SN(new Node(7))))));

//	SN t3(new Node(5));
//	SN L2(new Node(2, t3));

	SN L2(new Node(2, SN(new Node(5))));

	SN res = MergeTwoSortedList(L1, L2);
	PrintSmartList(res);
}
