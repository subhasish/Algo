/*
 * 00.BasicHeap.cpp
 *
 * Problem: Implement basic heap APIs
 *
 *  Created on: Jan 21, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;


// C++: Comparator as parameter:
//     This is example of Class taking comparator as template parameter. Any type can come as template parameter, as always.
//     Only restriction here is that it has to have matching operator as the class is used.

// For Heap:
//     putting element from index 1 makes computation easier
//     The comparator(child, parent) will be true invariant, to match with STL priority_queue

template<typename _Compare = less<int>>
struct MyHeap
{
	VI arr;
	_Compare comp;

	size_t parent(size_t k) { return (k>0) ? (k-1) / 2 : 0; }
	size_t child1(size_t k) { return 2*k + 1; }
	size_t child2(size_t k) { return 2*k + 2; }

	size_t size() { return arr.size(); }

	void swim(size_t k) {
		while(k>0) {
			size_t par = parent(k);
			if(!comp(arr[k], arr[par])) {
				swap(arr[k], arr[par]); // @suppress("Invalid arguments")
			}
			k = par;
		}
	}

	void sink(size_t k) {
		while (k < size()) {
			size_t ch1 = child1(k);
			size_t ch2 = child2(k);

			size_t max = k;
			if(ch1 < size() && !comp(arr[ch1], arr[k])) {
				max = ch1;
			}
			if(ch2 < size() && !comp(arr[ch2], arr[max])) {
				max = ch2;
			}

			if(max != k) {
				swap (arr[max], arr[k]); // @suppress("Invalid arguments")
				k = max;
			} else {
				break;
			}
		}
	}

	void push(int a) {
		arr.push_back(a);
		swim(size()-1);
	}

	int top() {
		return arr[0];
	}

	void pop() {
		swap(arr[0], arr[size() - 1]); // @suppress("Invalid arguments")
		arr.pop_back();
		sink(0);
	}

	bool empty() {
		return arr.empty();
	}

	void print() {
		cout << "Array: " ;
		for(size_t i=0; i<arr.size() ; ++i) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
};

int main()
{
	MyHeap<> max_heap;
	MyHeap<greater<int>> min_heap;

	max_heap.push(1);
	max_heap.push(3);
	max_heap.push(5);
	max_heap.push(2);
	max_heap.push(4);
	max_heap.push(6);

	while(!max_heap.empty()) {
		cout << "Max heap: " << max_heap.top() << endl;
		max_heap.pop();
	}

	min_heap.push(1);
	min_heap.push(3);
	min_heap.push(5);
	min_heap.push(2);
	min_heap.push(4);
	min_heap.push(6);

	while(!min_heap.empty()) {
		cout << "Min heap: " << min_heap.top() << endl;
		min_heap.pop();
	}
}


