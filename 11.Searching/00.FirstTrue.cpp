/*
 * 00.FirstYes.cpp
 *
 * Problem: Implement basic binary search to find first element for which some condition becomes true,
 *          where the array has consecutive false followed by consecutive trues.
 *
 *  Created on: Feb 5, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Do binary search.
//           If mid is true then take hi to the element.
//           If mid is false then take lo to that element + 1.
//           This will cause both hi and lo to point to the first element

typedef vector<bool> VB;

int BinarySearchFirstTrue(VB& arr) {
	int lo=0, hi=(int)arr.size()-1;

	if(hi < 0) return -1; // Empty array

	while(lo < hi) {
		int mid = lo + (hi-lo) / 2;

		if(arr[mid] == true) {
			hi = mid;
		} else {
			lo = mid + 1;
		}
	}

	// Now it is a single element, can compare with both low and high
	if(arr[lo] == false) { // No true entry in the array
		return -1;
	}

	return lo;
}

int main() {
	VB arr = {false, false, false, true, true, true, true, true, true};
	cout << "First true at: " << BinarySearchFirstTrue(arr) << endl;

	arr = {false, false, false, true};
	cout << "First true at: " << BinarySearchFirstTrue(arr) << endl;

	arr = {false};
	cout << "First true at: " << BinarySearchFirstTrue(arr) << endl;

	arr = {true};
	cout << "First true at: " << BinarySearchFirstTrue(arr) << endl;

	arr = {};
	cout << "First true at: " << BinarySearchFirstTrue(arr) << endl;
}
