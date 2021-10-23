/*
 * 06.FindClosestAmongArrays.cpp
 *
 * Problem: Design an algorithm that takes three (k in general) sorted arrays and returns one entry from each array such that the
 * 			interval covered by these elements are minimum.
 *
 *  Created on: Mar 24, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Brute force is to compare each triplet. But it does not use the fact that arrays are sorted.
//
//			Sorted array gives a systematic way to find the triplet.
//			We can start with three smallest of each array and then remove the smallest one and add next from that array.
//
//			Correctness of this approach lies in realizing that each time the interval we have is the
//			smallest interval for the smallest element in the interval.
//			Since the minimum interval containing elements from each array must begin with an element from some array,
//			we are guaranteed to encounter the smallest element.
//
//			Since we need to insert, delete and find the minimum and find the maximum among a collection of k elements,
//			BST is the natural choice.
//			But normal map will NOT work, as same element can exist in multiple arrays and we need to count both. Use multimap or custom BST.
//
// C++:
//			multimap

typedef vector<int> VI;
typedef vector<VI> VVI;

int FindClosestElementsInSortedArrays(const VVI sorted_arrays)
{
	int minimum_distance = numeric_limits<int>::max();

	// For each array we need to store two iterators; one the current iterator for traversing
	// and another is the end to check if we reached the end.
	struct IterTail {
		VI::const_iterator iter,end;
	};

	multimap<int, IterTail> iter_and_tail;
	// Initialize the map with smallest elements from each array
	for(const VI& v: sorted_arrays) {
		iter_and_tail.emplace(*v.begin(), IterTail{v.cbegin(),v.cend()});
	}

	while(true)		// Will breaks when one of the array reaches end
	{
		int min_value = iter_and_tail.cbegin()->first;
		int max_value = iter_and_tail.crbegin()->first;
		minimum_distance = min(max_value - min_value, minimum_distance);

		auto next_min = next(iter_and_tail.cbegin()->second.iter);
		auto next_end = iter_and_tail.cbegin()->second.end;

		if(next_min == next_end) {  // some array has no remaining element. So result must already be encountered
			break;
		}

		// Add the next element remove current minimum
		iter_and_tail.emplace(*next_min, IterTail{next_min, next_end});
		iter_and_tail.erase(iter_and_tail.cbegin());
	}

	return minimum_distance;
}

int main()
{
	VVI sorted_arrays =
	{
			{ 5, 10, 15 },
			{ 3, 6, 9, 12, 15 },
			{ 8, 16, 24}
	};

	cout << "Minimum distance: " << FindClosestElementsInSortedArrays(sorted_arrays) << endl;
}


