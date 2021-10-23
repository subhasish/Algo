/*
 * 00.ListSTL.cpp
 *
 * Use STL list
 *
 *  Created on: Oct 28, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Assume: non-cyclic
//void PrintList(Node<int>* L)
void PrintList(std::list<int> L)
{
	std::list<int>::iterator it = L.begin();

	cout << "List: ";
	while(it != L.end()) {
		cout << *it << " -> ";
		++it;
	}
	cout << "null" << endl;
}

int main()
{
	std::list<int> mylist1, mylist2;
	std::list<int>::iterator it;

	// set some initial values:
	for (int i=1; i<=4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4

	for (int i=1; i<=3; ++i)
		mylist2.push_back(i*10);   // mylist2: 10 20 30

	it = mylist1.begin();
	++it;                         // points to 2

	mylist1.splice (it, mylist2); 	// mylist1: 1 10 20 30 2 3 4
									// mylist2 (empty)
									// "it" still points to 2 (the 5th element)
	PrintList(mylist1);
}


