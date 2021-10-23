/*
 * 10.StableListSort.cpp
 *
 * Problem: Implement a routine that sorts lists efficiently. It should be stable sort.
 *
 *  Created on: Mar 11, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			For arrays quick sort is in-place solution but merge sort cannot be done in-place.
//			Unlike arrays, list can be merged in-place. Conceptually because insertion into a list is an O(1) operation.
//
//			Decomposing list in to two equal sized arrays is O(n), same as merging two n/2 sized arrays.
//			Time complexity remains as same as of merge sort.

struct Node {
	int val;
	char flag;
	shared_ptr<Node> next;

	Node(int a=0,char ch=' ', shared_ptr<Node> p=nullptr) : val(a), flag(ch), next(p) {}
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
SN MergeTwoSortedList(SN L1, SN L2)
{
	//dummy head: to create a place holder for the result
	SN dummy_head (new Node());
	SN tail = dummy_head;

	//while both list have element append smaller one in tail
	while(L1 && L2) {
		AppendList(L1->val <= L2->val ? &L1 : &L2, &tail);		// <= equality needed for being stable
	}

	//Add rest of the remaining list
	tail->next = (L1 ? L1 : L2);

	return dummy_head->next;
}


void PrintSmartList(SN head) {
	cout << "List: ";
	while(head != nullptr) {
		cout << "("<< head->val << "," << head->flag << ")" << " -> ";
		head = head->next;
	}
	cout << "null" << endl;
}

// Recursive function same as merge sort
SN StableListSort(SN L)
{
	if(L == nullptr || L->next == nullptr) {
		return L;
	}

	SN slow = L, fast = L;
	SN pre_slow = nullptr;	// To break the two halves

	while(fast && fast->next) {
		pre_slow = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	pre_slow->next = nullptr;

	return MergeTwoSortedList(StableListSort(L), StableListSort(slow));
}

int main()
{
	SN L(new Node(1, 'a', SN(new Node(5, 'b', SN(new Node(7, 'c', SN(new Node(2, 'd', SN(new Node(5, 'e'))))))))));

	SN res = StableListSort(L);
	PrintSmartList(res);
}


