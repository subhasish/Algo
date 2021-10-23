/*
 * 01.MergeSortedArray.cpp
 *
 * Problem: We have Some K (say 500) Large (say size 100000) arrays of sorted arrays.
 *          Merge them to produce a sorted array.
 *
 *  Created on: Jan 31, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Merging the whole array and then sort is O(n log n) and does not use the fact that arrays were sorted.
//           Merging two arrays at a time will take log K merges with O(n) taken for each merges. Total O(n log K). But it takes space for intermediate arrays.
//
//           Better is to keep track of all smaller elements from each array and take minimum of them each time. This can be done using min-heap.
//           Each time a element is selected, the next element from the array should populate the min-heap.
//           So we need to keep track of the index of array and the array itself for each elements in heap.
//           This can be done by creating iterator for each array and holding current pointer of the iterator.
//                   To detect end we may need to store the end iterator as well.
//                   Current can be initialized by begin iterator

// C++:
//			 Can use const_iterator instead of iterator as we are not modifying data inside container
//           ++const_iterator is perfectly fine as we are not changing the value and will make it point to next element

typedef vector<int> VI;
typedef vector<VI> VVI;


struct IteratorCurrentAndEnd {

	// Storing two iterators for each array
	VI::const_iterator current;
	VI::const_iterator end;

	bool operator > (const IteratorCurrentAndEnd& that) const {
		return *current > *(that.current);
	}
};

typedef IteratorCurrentAndEnd ICAE;

VI MergeSortedArrays(VVI& sorted_arrays)
{
	VI result;
	priority_queue<ICAE, vector<ICAE>, greater<ICAE>> min_heap;

	for(const VI& arr: sorted_arrays) {

		// Initialize each iterator begin() and insert in min heap
		min_heap.push( ICAE{arr.cbegin(), arr.cend()} );

	}


	while(!min_heap.empty()) {
		ICAE small = min_heap.top();
		min_heap.pop();

		//If not reached end for that array then insert next element. Also add the element if not end (No element at the end!!)
		if(small.current != small.end) {

			result.push_back(*small.current);
			++small.current;
			min_heap.push(small); //Or add ICAE{next(small.current), small.end}
		}
	}

	return result;
}


int main()
{
	VVI input =
	{
			{0,4,6,9,11},
			{2,7,88,99},
			{0,6,22,55,66}
	};

	VI res = MergeSortedArrays(input);

	for(int i: res) {
		cout << i << " ";
	}
	cout << endl;
}



