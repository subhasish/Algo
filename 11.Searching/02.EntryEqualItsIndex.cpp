/*
 * 02.EntryEqualItsIndex.cpp
 *
 * Problem: Search an element in an sorted array such that its value is equal to its index.
 *          Each element is distinct
 *
 *  Created on: Feb 7, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: After an entry becomes equal to its index the all elements afterwards cannot be less than index.
//           Reason is that index will increment by 1 and value will at least increment by that.
//
//           So if we use predicate whether element is greater or equal to index then array will be like consecutive false then consecutive trues
//           So we can find first true using same logic as FirstTrue.cpp

typedef vector<int> VI;


int SearchEntryEqualsItsIndex(const VI& arr)
{
	int lo = 0, hi = arr.size()-1;

	if(hi < 0) return -1;   // Empty array

	while(lo < hi) {
		int mid = lo + (hi - lo) / 2;

		if(arr[mid] >= mid) {
			hi = mid;
		} else {    // arr[mid] < mid
			lo = mid + 1;
		}
	}

	// Search reduced to single element
	if(arr[lo] == lo) {
		return lo;
	} else {
		return -1;
	}
}

int main()
{
	VI arr1 = {-2, 0, 2, 3, 6, 7, 9};
	cout << "Index for which element equals index is: " << SearchEntryEqualsItsIndex(arr1) << endl;

	VI arr2 = {-2, 0, 4, 5, 6, 7, 9};
	cout << "Index for which element equals index is: " << SearchEntryEqualsItsIndex(arr2) << endl;
}
