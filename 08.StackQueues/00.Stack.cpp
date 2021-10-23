/*
 * 00.Stack.cpp
 *
 * Problem: Use basic libraries of C++ Stack library
 *
 *  Created on: Jan 1, 2018
 *      Author: subha
 */


#include <bits/stdc++.h>

using namespace std;

void PrintAndEmptyStack(stack<int> S) {
	cout << "Stack: " ;
	while(! S.empty()) {
		cout << S.top() << ", ";
		S.pop();  //DON'T FORGET to POP => Infinite loop
	}
	cout << endl;
}

int main()
{
	stack<int> S;
	S.push(2);
	S.push(3);
	S.push(4);

	int val = S.top();
	S.pop();   //NOTE: Pop does not return any value. Use top() before popping.

	cout << "Popped value = " << val << endl;

	PrintAndEmptyStack(S);

	return 0;
}


