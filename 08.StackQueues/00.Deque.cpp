/*
 * 00.Deque.cpp
 *
 * Problem: Use standard c++ Apis for Deque
 *
 *  Created on: Jan 1, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

void PrintAndEmptyDeque(deque<int> D)
{
	cout << "Deque: ";
	while(!D.empty()) {
		cout << D.front() << ", ";
		D.pop_front();  //NOTE: Pop does not return any value. Use front()/back() before popping.
	}
	cout << endl;
}

int main()
{
	deque<int> D;

	D.push_back(2);
	D.push_back(3);
	D.push_back(4);
	D.push_front(1);

	cout << "Front= " << D.front() << ", and Back= " << D.back() << endl;

	PrintAndEmptyDeque(D);
}

