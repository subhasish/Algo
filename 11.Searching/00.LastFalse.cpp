/*
 * 00.LastFalse.cpp
 *
 * Problem: Implement basic binary search to find last element for which some condition becomes false,
 *          where the array has consecutive false followed by consecutive trues.
 *
 *  Created on: Feb 6, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Do binary search similar to what we do to find the Last false element.
//           But decrement high on true and not increment low on false.
//           Avoid infinite loop by pointing mid to high for 2 element case.

typedef vector<bool> VB;

int BinarySearchLastFalse(VB& arr)
{
	int lo = 0, hi = (int)arr.size()-1;

	if(hi < 0) return -1; // Empty array

	while(lo < hi) {
		int mid = lo + (hi - lo + 1)/2;

		if(arr[mid] == true) {
			hi = mid - 1;
		} else {
			lo = mid;
		}
	}

	// Now it is a single element, can compare with both low and high
	if(arr[lo] == true) { // No false element
		return -1;
	}

	return lo;
}

int main() {
	VB arr = {false, false, false, true, true, true, true, true, true};
	cout << "Last false at: " << BinarySearchLastFalse(arr) << endl;

	arr = {false, false, false, true};
	cout << "Last false at: " << BinarySearchLastFalse(arr) << endl;

	arr = {false};
	cout << "Last false at: " << BinarySearchLastFalse(arr) << endl;

	arr = {true};
	cout << "Last false at: " << BinarySearchLastFalse(arr) << endl;

	arr = {};
	cout << "Last false at: " << BinarySearchLastFalse(arr) << endl;
}

