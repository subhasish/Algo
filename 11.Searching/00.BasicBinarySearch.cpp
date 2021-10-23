/*
 * 00.BasicBinarySearch.cpp
 *
 * Problem: Implement basic binary search
 *
 *  Created on: Feb 6, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;


bool MyBinarySearch(const VI& arr, int key)
{
	int lo = 0, hi = arr.size() - 1;

	if(hi < 0) return false; // Empty input

	while(lo < hi) {
		int mid = lo + (hi - lo) / 2;

		if(arr[mid] == key) {
			return true;
		} else if (arr[mid] > key) {
			hi = mid - 1;
		} else {  // arr[mid] < key
			lo = mid + 1;
		}
	}

	if(arr[lo] == key) {   // Single element
		return true;
	} else {
		return false;
	}
}

int main() {

	VI arr = {1,2,3,4,5,6,7};

	cout << MyBinarySearch(arr, 5) << endl;
	cout << MyBinarySearch(arr, 10) << endl;
	cout << MyBinarySearch(arr, -5) << endl;

	arr = {};
	cout << MyBinarySearch(arr, -5) << endl;

	arr = {4};
	cout << MyBinarySearch(arr, -5) << endl;

	arr = {-5};
	cout << MyBinarySearch(arr, -5) << endl;

}
