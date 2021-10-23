/*
 * 00.SharedPtr.cpp
 *
 * Try out shared_ptr of c++11
 *
 *  Created on: Oct 30, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int m;

	Node(int a=0) : m(a) {}
	~Node() { cout << "Node with value " << m << " is destroyed" << endl; }
};

struct SimpleList {
	int m;
	SimpleList* next;

	SimpleList(int a=0, SimpleList* p=nullptr) : m(a), next(p) {}
	~SimpleList() { cout << "List node with value " << m << " is destroyed" << endl; }
};

struct SmartList {
	int m;
	shared_ptr<SmartList> next;

	SmartList(int a=0, shared_ptr<SmartList> p = nullptr) : m(a), next(p) {}
	~SmartList() { cout << "SmartList node with value " << m << " is destroyed" << endl; }

};

void WhyNeedSmartPointers() {
	shared_ptr<Node> p1(new Node(1));
	Node* p2 = new Node(2);

	throw "Exiting from Func1";

	delete p2;
}

SimpleList* CreateSimleList() {
	SimpleList* tail = new SimpleList(1);
	SimpleList* head = new SimpleList(2, tail);

	return head;
}

void PrintSimpleList(SimpleList* head) {
	cout << "Simple List: ";
	while (head) {
		cout << head->m << " -> ";
		head = head->next;
	}
	cout << "null" << endl;
}

shared_ptr<SmartList> CreateSmartList() {
	shared_ptr<SmartList> tail(new SmartList(1));
	shared_ptr<SmartList> head(new SmartList(2, tail));

	return head;
}

void PrintSmartList(shared_ptr<SmartList> head) {
	cout << "Smart List: ";
	while(head != nullptr) {
		cout << head->m << " -> ";
		head = head->next;
	}
	cout << "null" << endl;
}

int main()
{
	try {
		WhyNeedSmartPointers();
	} catch (...) {

	}

	SimpleList* simple = CreateSimleList();
	shared_ptr<SmartList> smart = CreateSmartList();

	PrintSimpleList(simple);
	PrintSmartList(smart);
}


