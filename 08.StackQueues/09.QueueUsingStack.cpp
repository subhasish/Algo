/*
 * 09.QueueUsingStack.cpp
 *
 * Problem: Implement queue using stack
 *
 *  Created on: Jan 4, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: It is not possible to solve this problem using single stack.
//           Using two stacks it can be done by pushing into stack and then while popping
//           first popping and pushing all into a 2nd stack and then pop from that.
//           Again all remaining elements can again be pushed back to 1st stack.
//
// Optimization: We do not need to put all remaining elements back to 1st stack. Instead, we can
//           keep popping from the 2nd stack until that is empty.

class QueueUsingStack
{
	stack<int> _in;
	stack<int> _out;

	void refillOut() {
		if(!_out.empty())
			return;

		while(!_in.empty()) {
			_out.push(_in.top());
			_in.pop();
		}
	}

public:

	bool empty() {
		return _in.empty() && _out.empty();
	}

	void push(int a) {
		_in.push(a);
	}

	void pop() {
		if(empty()) {
			throw length_error("Cannot perform pop() from an empty queue.");
		}
		refillOut();
		_out.pop();
	}

	int front() {
		if(empty()) {
			throw length_error("Cannot perform top() from an empty queue.");
		}
		refillOut();
		return _out.top();
	}
};


void PrintAndEmptyQueue(QueueUsingStack Q)
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
	QueueUsingStack Q;

	Q.push(2);
	Q.push(3);
	Q.push(4);
	Q.pop();
	Q.push(5);

	PrintAndEmptyQueue(Q);
}
