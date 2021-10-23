/*
 * 11.IsPalindromeList.cpp
 *
 * Problem: Is the given linked list is a Palindrome?
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

void PrintSmartList(SN head) {
	cout << "List: ";
	while(head != nullptr) {
		cout << head->val << " -> ";
		head = head->next;
	}
	cout << "null" << endl;
}

//Reverse the list passed in
void ReverseList(SN* Lptr)
{
	SN L = *Lptr;
	SN head(new Node(0, L));

	// One node is by default reversed. So start from the SECOND node.
	// So Prev is at the start of the list
	SN prev = L;
	// Node to move is the second node
	SN toMove = prev->next;

	while(toMove != nullptr) {     // While there is something to move
		prev->next = toMove->next; // Prev->next will now point to the next node
		toMove->next = head->next;   // Node moved will point to what head points
		head->next = toMove;         // Head will point to new node moved

		toMove = prev->next;      // Update the next node to move
	}

	(*Lptr) = head->next;
}

bool EqualListUptoLength(SN A, SN B)
{
	while(A != nullptr && B != nullptr) {
		if(A->val != B->val)
			return false;
		A = A->next; B = B->next;
	}
	return true;
}

//Checking a list in both direction is not possible efficiently
//So reverse half of the list and then compare and then reverse back
bool IsPalindromeList(SN* LP)
{
	SN L = *LP;
	//Find the middle
	SN slow=L,fast=L;
	while(fast != nullptr) {
		fast = fast->next;
		if(fast != nullptr) {
			fast = fast->next;
			slow = slow->next;
		}
	}
	SN mid=slow;

	cout << "Mid at: " << mid->val << endl;
	//Reverse from middle
	ReverseList(&mid);

	// NOTE: No the list is Y shape. 1 -> 2 -> 3 -> 4 -> 5 will be 1 -> 2 -> 3 -> null and 5 -> 4 -> 3 -> null
	// mid pointing to 5 here

	bool isPalindrome = false;
	if(EqualListUptoLength(L, mid)) {
		isPalindrome = true;
	}

	// Reverse the rest of the list to restore the original list as well as its shape
	ReverseList(&mid);

	return isPalindrome;
}


int main()
{
	SN L(new Node(1, SN(new Node(2, SN(new Node(3, SN(new Node(2, SN(new Node(1))))))))));

//	SN L(new Node(1, SN(new Node(2, SN(new Node(2, SN(new Node(1))))))));

	PrintSmartList(L);

	cout << "****************************************" << endl;
	cout << "Palindrome check = " << IsPalindromeList(&L) << endl;
	cout << "****************************************" << endl;


}

