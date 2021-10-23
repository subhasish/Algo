/*
 * 08.CircularQueue.cpp
 *
 * Problem: Implement circular queue that uses array internally.
 *          The queue should support dynamic resizing.
 *
 *  Created on: Jan 3, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Circular queue can be implemented in array using front and back index.
//           While trying to insert in a full queue it should resize.
//
// Resizing: Notice that while resizing, the element will appear consecutively (may start from beginning).

typedef vector<int> VI;

class CircularQueue {
	VI arr;
	size_t head=0, tail=0;		// tail is one beyond the last element where the new item will be inserted
	size_t num_of_elements=0; 	// Lot of pain is saved by maintaining number of elements

public:

	explicit CircularQueue(int capacity) : arr(capacity) {}

	bool empty() {
		return num_of_elements == 0;
	}

	size_t size() {
		return num_of_elements;
	}

	void push(int val) {
		if(num_of_elements == arr.size()) { // Need to resize
			// Make elements appear consecutively from start
			rotate(arr.begin(), arr.begin()+head, arr.end());  // rotate to make element at head at first position

			// Reset head and tail
			head = 0; tail = num_of_elements;

			// Double the size
			arr.resize(arr.size()*2);
		}

		arr[tail] = val;
		tail = (tail+1) % arr.size();
		++num_of_elements;
	}

	void pop() {
		if(0 == num_of_elements) {
			throw length_error("Cannot perform pop() in empty queue.");
		}

		head = (head + 1) % arr.size();
		--num_of_elements;
	}

	int front() {
		if(0 == num_of_elements) {
			throw length_error("Cannot perform front() in empty queue.");
		}
		return arr[head];
	}

	int back() {
		if(0 == num_of_elements) {
			throw length_error("Cannot perform back() in empty queue.");
		}
		return arr[tail-1];
	}

	void Print() {
		if(num_of_elements == 0) {
			cout << "Queue is empty!!" << endl;
			return;
		} else {
			cout << "Size of the queue: " << size() << endl;
			cout << "Capacity: " << arr.size() << endl;
			cout << "Elements: ";
		}
		for(size_t i = head; i != tail ; i = (i+1) % arr.size()) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
};

int main()
{
	CircularQueue Q(2);

	Q.push(1);
	Q.push(2);
	Q.push(3);

	Q.Print();

	Q.push(4);
	Q.pop();
	Q.pop();
	Q.push(5);
	Q.push(6);
	Q.push(7);

	Q.Print();
}
