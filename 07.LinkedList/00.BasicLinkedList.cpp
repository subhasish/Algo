/*
 * 00.BasicLinkedList.cpp
 *
 * Problem: Create basic linked list. Do operations line search, insert and delete
 *
 *  Created on: Oct 28, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct Node{
	T data;

	//Node<T>* next;
	shared_ptr<Node<T>> next;

	Node(T m) : data(m), next(nullptr) {}
	~Node() { cout << "Node with value " << data << " is being destroyed." << endl;}
};

typedef shared_ptr<Node<int>> shared_node_int;


//Node<int>* SearchList(Node<int>* L, int key)
shared_node_int SearchList(shared_node_int L, int key)
{
	while(L && L->data != key) {
		L = L->next;
	}

	return L; //null if not present
}


//void InsertAfter(Node<int>* node, int key)
void InsertAfter(const shared_node_int& node, int key)
{
//	Node<int>* new_node = new Node<int>(key);
	shared_node_int new_node(new Node<int>(key));

	new_node->next = node->next;
	node->next = new_node;
}


//Node<int>* DeleteAfter(Node<int>* node)
shared_node_int DeleteAfter(const shared_node_int& node)
{
//	Node<int>* ret_node = node->next;
	shared_node_int ret_node = node->next;

	node->next = (node->next != nullptr) ? node->next->next : nullptr;
	return ret_node;
}

// Assume: non-cyclic
//void PrintList(Node<int>* L)
void PrintList(shared_node_int L)
{
	cout << "List: ";
	while(L != nullptr) {
		cout << L->data << " -> ";
		L = L->next;
	}
	cout << "null" << endl;
}

int main()
{
//	Node<int>* head = new Node<int>(1);
	shared_node_int head(new Node<int>(1));

	InsertAfter(head, 6);
	InsertAfter(head, 5);
	InsertAfter(head, 4);
	InsertAfter(head, 3);
	InsertAfter(head, 2);

	PrintList(head);
}


