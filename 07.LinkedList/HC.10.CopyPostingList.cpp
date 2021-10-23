/*
 * HC.10.CopyPostingList.cpp
 *
 * Problem: A posting list is a singly lined list with an additional "jump" field at each node that
 * 			points to any other node.
 * 			Implement a function which takes a posting list and return a copy if it.
 *
 * 			If you modify original list, restore it before returning.
 *
 *  Created on: Nov 4, 2018
 *      Author: subha
 */

#define __USE_MINGW_ANSI_STDIO 0

#include <bits/stdc++.h>
using namespace std;


struct PostingListNode {
	int val;
	shared_ptr<PostingListNode> next, jump;

	PostingListNode(int a, shared_ptr<PostingListNode> n=nullptr, shared_ptr<PostingListNode> j=nullptr): val(a), next(n), jump(j) {}
};
typedef shared_ptr<PostingListNode> SPN;


// Solution:
//			Create a copy of the posting list without assigning value to jump field. Then use hash table
//			to store the mapping between nodes in original list and the copied list. Then traverse the
//			original list and copied list in tandem and assign jump field.

SPN CopyPostingList(const SPN& list)
{
	if(list == nullptr) {
		return nullptr;
	}

	SPN copy = nullptr;
	SPN copy_head = SPN(new PostingListNode(0, nullptr));
	SPN copy_prev = copy_head;

	SPN iter = list;
	unordered_map<SPN, SPN> map;

	while(iter != nullptr) {
		copy = SPN(new PostingListNode(iter->val));
		map[iter] = copy;
		copy_prev->next = copy;
		copy_prev = copy;
		iter = iter->next;
	}

	iter = list;
	copy = copy_head->next;
	while(iter != nullptr) {
		copy->jump = map[iter->jump];
		iter = iter->next;
		copy = copy->next;
	}

	return copy_head->next;
}

// Optimized solution:
//			The previous solution uses extra memory in the form of hash table.
//			The key to improve the space complexity is to use the next field in the original
//			node to store the mapping to the copied list and the next of copied list can
//			store the next node of the original list.
//			Then we can assign the jump and then undo the changes appropriately.

SPN CopyPostingListOpt(SPN& list) {
	if(list == nullptr) {
		return nullptr;
	}

	// Step 1: Make copy of the original list with mapping preserved using next fields
	SPN iter = list;
	while(iter != nullptr) {
		SPN new_node = SPN(new PostingListNode(iter->val, iter->next));
		iter->next = new_node;
		iter = new_node->next;
	}

	// Step 2: Assign the jump field in the copied list
	iter = list;
	while(iter != nullptr) {
		if(iter->jump != nullptr) {
			iter->next->jump = iter->jump->next;
		}
		iter = iter->next->next;
	}

	// Step 3: Revert the original list
	iter = list;
	SPN new_list_head = list->next;
	while(iter != nullptr) {
		SPN temp = iter->next->next;
		if(temp != nullptr) {
			iter->next->next = temp->next;
		}
		iter->next = temp;
		iter = temp;
	}

	return new_list_head;
}

void PrintPostingList(SPN list) {
	while (list != nullptr) {
		cout << "[" << list->val << ", J: " << (list->jump != nullptr? to_string(list->jump->val) : "null") << "] -> ";
		list = list->next;
	}
	cout << "null" << endl;
}

int main() {
	SPN d = SPN(new PostingListNode(4));
	SPN c = SPN(new PostingListNode(3, d));
	SPN b = SPN(new PostingListNode(2, c));
	SPN a = SPN(new PostingListNode(1, b));
	a->jump = c;
	b->jump = d;
	c->jump = b;
	d->jump = a;
	SPN list = a;

	SPN copy = CopyPostingList(list);
	PrintPostingList(copy);

	copy = CopyPostingListOpt(list);
	PrintPostingList(copy);

}
