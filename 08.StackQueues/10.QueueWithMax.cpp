/*
 * 10.QueueWithMax.cpp
 *
 * Problem: Implement queue with max API
 *
 *  Created on: Jan 4, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: As always, problem is when max is popped how to find next max.
//           When a number is pushed:
//              1. It is max if all other elements are popped and no other is pushed
//              2. If it is greater than all previous elements, then no other element before it can ever be max
//
//           So we will have to keep a decreasing sequence of maximum number.
//           If a number is pushed then we could remove all the number less than it from the sequence of maximum numbers.
//           We will use Deque for max sequence, as we need to pop from both front and back.
//
//           We could keep same number multiple times to count for multiple occurrences.

class QueueWithMax
{
	queue<int> Q;
	deque<int> maxQ;

public:

	bool empty() {
		return Q.empty();
	}

	void push(int a) {
		Q.push(a);

		// Remove all the elements that are smaller than current value
		while(!maxQ.empty()) {
			if(maxQ.back() < a) {  // Keep equals to count for multiple occurrences
				maxQ.pop_back();
			} else {
				break;
			}
		}
		maxQ.push_back(a);
	}

	void pop() {
		if(maxQ.front() == Q.front()) {
			maxQ.pop_front();
		}
		Q.pop();
	}

	int& front() {
		return Q.front();
	}

	int& back() {
		return Q.back();
	}

	int max() {
		return maxQ.front();
	}
};

int main()
{
	QueueWithMax Q;

	Q.push(200);
	Q.push(13);
	Q.push(41);
	Q.pop();
	Q.push(5);

	cout << Q.max() << endl;
}
