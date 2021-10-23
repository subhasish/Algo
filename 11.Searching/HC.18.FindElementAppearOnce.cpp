/*
 * HC.18.FindElementAppearOnce.cpp
 *
 * Problem: Given an integer array where each entry but one appears three times exactly, and the
 * 			remaining element appears exactly once. Find the element appearing once.
 *
 *  Created on: Dec 18, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			If other elements appeared twice then we had two solutions: one where we store all the
//			element counts in a hash table; another solution is to bitwise-xor the elements.
//
//			Analogous or general form of the xor approach is to count the number of 1's in each bit
//			position and then find what does not match according to the array constraint.
//
//			Here we can do count mod 3 to eliminate the numbers that appear thrice. We can use an array
//			whose size is of integer word size, and whose ith element will count the number of 1s in
//			ith bit position across all the inputs.
//
// Complexity:
//			Time complexity O(n), space complexity O(1)

int FindElementAppearsOnce(vector<int>& A) {
	size_t sz = numeric_limits<int>::digits + 1;
	vector<int> C(sz);

	for(int i=0 ; i < (int)A.size() ; ++i) {
		int x = A[i];
		for(int j=0; j<(int)sz ; ++j) {
			C[j] += x&1;
			x >>= 1;
		}
	}

	int result = 0;
	for(int j=(int)sz-1 ; j>=0 ; --j) {
		result |= (C[j] % 3) ;
		if (j>0) {
			result <<= 1;
		}
	}

	return result;
}

int main() {
	vector<int> A = {2, 4, 7, 2, 2, 7, 4, 7, 11, 4};
	cout << "Single element = " << FindElementAppearsOnce(A) << endl;
}
