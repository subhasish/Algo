/*
 * 01.StackWithMax.cpp
 *
 * Problem: Design a stack that supports Max operation
 *
 *  Created on: Jan 1, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: For each item pushed in the stack, we keep track of the maximum stored at or below that item in another stack.
//
// Problem:  Problem with not repeating max for each item is that if there is multiple item with max value then
//           while popping a item with value same as max we do not know whether to pop that item from max stack or not.
//
// Optimization: We can store count with the each max value to determine when to delete that item from max stack.
//
// Alternative: Alternative to count is to push element into max whenever element is equal to max

class StackWithMax
{
	stack<int> _Stack;
	struct MaxWithCount {
		int max, count;
	};
	stack<MaxWithCount> _MaxStack;

public:
	void push(int val) {
		_Stack.push(val);
		if(_MaxStack.empty()) {
			_MaxStack.push({val,1});
		} else {
			int max = _MaxStack.top().max;
			if(val > max) {
				_MaxStack.push({val,1});
			} else if (val == max) {
				int& max_count = _MaxStack.top().count;
				++max_count;
			}
		}
	}

	void pop() {
		if(_Stack.empty()) {
			throw length_error("Stack is empty");
		}

		int val = _Stack.top();
		_Stack.pop();

		int max = _MaxStack.top().max;
		if(max == val) {
			int& max_count = _MaxStack.top().count;
			if(max_count <= 1) {
				_MaxStack.pop();
			} else {
				--max_count;
			}
		}
	}

	bool empty() {
		return _Stack.empty();
	}

	int& top() {
		return _Stack.top();
	}

	int max() {
		return _MaxStack.top().max;
	}
};

int main()
{
	StackWithMax S;

	S.push(33);
	S.push(44);
	S.push(33);
	S.push(44);
	S.push(11);
	S.push(20);

	while(!S.empty()) {
		cout << "Element= " << S.top() << ", Max= " << S.max() << endl;
		S.pop();
	}

}


