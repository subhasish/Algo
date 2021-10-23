/*
 * 01.SearchFirstOfK.cpp
 *
 * Problem: Given a sorted file with duplicates, find first occurrence of a number
 *
 *  Created on: Feb 7, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Can easily be done using STL function lower_bound.
//
//           Alternatively, we can form predicate Is greater than or equal K and then apply logic as in FirstTrue.cpp
//           Only need to make sure the element returning is actually k

typedef vector<int> VI;

int SearchFirstOfK(const VI& arr, int k)
{
	int lo = 0, hi = arr.size() -1;

	if(hi < 0) return -1;  // Empty array

	while(lo < hi) {
		int mid = lo + (hi - lo)/2;

		if(arr[mid] >= k) {
			hi = mid;
		} else {  // arr[mid] < k
			lo = mid + 1;
		}
	}

	// Search reduced to single element
	if(arr[lo] == k) {
		return lo;
	} else {
		return -1;   // Not found
	}
}

int main()
{
	VI arr = {-14, -10, 2, 108, 108, 243, 285, 285, 285, 401};

	cout << "First 108 is at index: " << SearchFirstOfK(arr, 108) << endl;
	cout << "First 285 is at index: " << SearchFirstOfK(arr, 285) << endl;
	cout << "First -14 is at index: " << SearchFirstOfK(arr, -14) << endl;
	cout << "First 109 is at index: " << SearchFirstOfK(arr, 109) << endl;
}
