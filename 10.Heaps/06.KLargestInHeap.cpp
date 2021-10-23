/*
 * 06.KLargestInHeap.cpp
 *
 * Problem: Compute K largest elements in a max heap without modifying the heap
 *
 *  Created on: Feb 2, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//          Doing K top() operation will modify the heap.
//          Also finding K th element using partition will also modify heap
//
//          Note that heap has partial ordering. A[0] must be one of the K largest element. One of its children A[1] and A[2] must be 2nd largest one.
//          So we need another data structure to use the partial ordering of heap that can find k largest elements consecutively.
//          Heap is that data structure.
//          Only thing is that we need to keep track of index of each element, so that when we pop it we can put its children in the heap again.

typedef vector<int> VI;

VI KLargestInHeap(VI heap, size_t k) {

	if(k >= heap.size())
		return heap;

	VI result;

	struct HeapEntry{
		int value;
		size_t index;
	};

	priority_queue<HeapEntry, vector<HeapEntry>, function<bool(HeapEntry&, HeapEntry&)>>
			max_heap([]( HeapEntry& a,  HeapEntry& b) {return a.value < b.value; });

	max_heap.push({heap[0],0});

	for(size_t i=0; i<k ; i++) {
		HeapEntry top = max_heap.top();
		max_heap.pop();

		size_t ind1 = top.index*2 + 1;
		size_t ind2 = top.index*2 + 2;

		if(ind1 < heap.size()) {
			max_heap.push({heap[ind1], ind1});
		}
		if(ind2 < heap.size()) {
			max_heap.push({heap[ind2], ind2});
		}

		result.push_back(top.value);
	}

	return result;
}


int main()
{
	VI heap = {561, 314, 401, 28, 156, 359, 271, 11, 3};
	VI res = KLargestInHeap(heap, 4);

	for(int i: res) {
		cout << i << endl;
	}
}
