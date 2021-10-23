/*
 * 07.StackUsingHeap.cpp
 *
 * Problem: Implement stack APIs using heap
 *
 *  Created on: Feb 2, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: There is no way heap can know the order of insertion and pop accordingly.
//           But heap can pop in some priority. So we need to make the order of insertion as priority.
//           So need to insert the order augmented with actual data.
//
//           One implementation would be use size of heap as priority. As it would be largest for new element.
//           Another implementation could use a counter as time-stamp that would always increase with every insert.
//           Using size is more scalable and less likely to hit INT.Max
//
//           Using same priority we can implement a Queue using a min heap

// C++:
//			 Do not use () inside class, use {} instead

class MyStack {

	struct ValueWithRank {
			int value;
			size_t rank;
		};

	// Do not use () inside class, use {} instead
	priority_queue<ValueWithRank, vector<ValueWithRank>, function<bool(ValueWithRank&, ValueWithRank&)>>
			max_heap{[](ValueWithRank& a, ValueWithRank& b) { return a.rank < b.rank; } };

  public:

	void push(int a) {
		max_heap.push({a, max_heap.size()});
	}

	int top() {
		return max_heap.top().value;
	}

	void pop() {
		max_heap.pop();
	}

	bool empty() {
		return max_heap.empty();
	}


};

void PrintAndEmptyStack(MyStack S) {
	cout << "Stack: " ;
	while(! S.empty()) {
		cout << S.top() << ", ";
		S.pop();  //DON'T FORGET to POP => Infinite loop
	}
	cout << endl;
}

int main()
{
	MyStack S;
	S.push(2);
	S.push(3);
	S.push(4);

	int val = S.top();
	S.pop();   //NOTE: Pop does not return any value. Use top() before popping.

	cout << "Popped value = " << val << endl;

	S.push(5);

	PrintAndEmptyStack(S);

	return 0;
}
