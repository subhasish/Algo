/*
 * HC.15.SearchUnknownLength.cpp
 *
 * Problem: Binary search is usually applied to an array of known length. Sometimes, the array is
 * 			"virtual", i.e., it is an abstraction of data spread across multiple machines. In such
 * 			cases length is not known in advance; accessing elements beyond the end results in
 * 			exception.
 *
 * 			Design an algorithm that takes a sorted array whose length is not known, and a key, and
 * 			returns an index of an array element which is equal to the key.
 *
 *  Created on: Nov 25, 2018
 *      Author: subha
 */

// Solution:
//			The main idea is to use the exception handling mechanism to modify range of the array to
//			look for and continue searching. This way we can do a binary search even if we do not know
//			the length of the array.
//
//			First of all we need to find a range where the number can possibly exists and then we will
//			search. We will find first p such that 2^p-1 is greater than k and then do binary search
//			in the range 2^(p-1) and 2^p - 2.
//
// Time complexity:
//			Two loops with log n complexity where n is the size of the array.
// C++:
//			vector::at throws the out_of_range exception but the not the array subscript version.

#include <bits/stdc++.h>
using namespace std;

int BinarySearchUnknownLength(const vector<int>& A, int k) {
	// Find possible range where k exists
	int p=0;
	while(true) {
		try {
			int idx = (1 << p) - 1; //2^p - 1
			if(A.at(idx) == k) {
				return idx;
			} else if(A.at(idx) > k) {	// Found idx such that k must exits between A[0,idx], if at all
				break;
			}
		} catch (const exception& e) {
			break;
		}
		++p;
	}

	// Binary search between indices 2^(p-1) and 2^p - 2, inclusive
	int lo = max(0, 1 << (p-1));
	int hi = (1 << p) - 2;
	while(lo <= hi) {
		int mid = lo + (hi-lo)/2;
		try {
			if(A.at(mid) == k) {
				return mid;
			} else if(A.at(mid) < k) {
				lo = mid + 1;
			} else { // A.at(mid) > k
				hi = mid - 1;
			}
		} catch (const exception& e) {	// mid is out-of-bound so set hi appropriately
			hi = mid - 1;
		}
	}
	return -1;	//Not found
}

int main() {

	//Test out_of_range exception
	//
	//	vector<int> A = {1,2,3};
	//	try {
	//		cout << A.at(5) << endl;
	//	} catch (const exception& e) {
	//		cout << "Exception encountered: " << e.what() << endl;
	//	}

	vector<int> A = {-14, -10, 2, 108, 108, 243, 285, 285, 285, 401};
	int index = BinarySearchUnknownLength(A, 285);
	if(index == -1) {
		cout << "Not found!" << endl;
	} else {
		cout << "Found at index " << index << endl;
	}

	index = BinarySearchUnknownLength(A, 3333);
	if(index == -1) {
		cout << "Not found!" << endl;
	} else {
		cout << "Found at index " << index << endl;
	}
}

