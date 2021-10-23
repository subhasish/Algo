/*
 * 00.Queue.cpp
 *
 * Problem: Use basic c++ libraries for Queue
 *
 *  Created on: Jan 1, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

void PrintAndEmptyQueue(queue<int> Q)
{
	cout << "Queue: ";
	while(!Q.empty()) {
		cout << Q.front() << ", ";
		Q.pop();    //NOTE: Pop does not return any value. Use front() before popping.
	}
	cout << endl;
}

int main()
{
	queue<int> Q;

	Q.push(2);
	Q.push(3);
	Q.push(4);

	PrintAndEmptyQueue(Q);
}

