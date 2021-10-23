/*
 * 03.SearchCyclicSmallest.cpp
 *
 * Problem: You are given a cyclic sorted array. Now find the position of smallest element in the array.
 *          Cyclic sorted array can be made sorted through rotation.
 *
 *  Created on: Feb 8, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Again the array can be transformed in to the space of consecutive false followed by consecutive trues.
//           The condition would be smaller than the first element. Then we need to find first true.
//
//           One edge case to handle is sorted case, where first element is itself smallest.

typedef vector<int> VI;

int SearchCyclicSmallest(const VI arr)
{
	int lo = 0, hi = arr.size() - 1;

	if(hi < 0) return -1;   // Empty array

	if(arr[lo] < arr[hi])  return lo;  // Sorted array

	// Else means the array is cyclic
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;

		if(arr[mid] < arr[0]) {  // Predicate is: element is less than first element
			hi = mid;
		} else {
			lo = mid + 1;
		}
	}

	// Search reduced to one element
	if(arr[lo] > arr[0]) {
		return -1; // Something went wrong!!
	} else {
		return lo;
	}

}

int main()
{
	VI arr = {5, 6, 7, 8, 9, 2, 3};
	cout << "Index to smallest element = " << SearchCyclicSmallest(arr) << endl;
}
