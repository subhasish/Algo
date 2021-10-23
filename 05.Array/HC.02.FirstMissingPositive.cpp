/*
 * HC.02.FirstMissingPositive.cpp
 *
 * Problem: Design an algorithm to find the smallest positive integer which is not present in the
 * 			given array.
 * 			You do not need to preserve the content of input array.
 *
 *  Created on: Oct 29, 2018
 *      Author: subha
 */

// Solution:
//			Result cannot be greater than the size of the array.
//			Brute force solutions are like:
//				- looking each number from 1 to A.size() in sequential search; O(n^2)
//				- sort the array and find first missing positive; O(n log n)
//			These does lots of unnecessary actions.
//
//			Using hash table O(n) time complexity can be improved to O(n). Note all numbers
//			in one traversal and then do find from 1 to A.size().
//
//			If we are allowed to modify the original array then that can be used as hash table.
//			A[i] can store whether (i+1) is present in the array.
//			Some negative constant can be used to mark A[i-1] when i is found in the array.
//			Later traverse the array in index order and see if A[i]!=found_constant.
//			Need to pre-process array to make sure none have that constant in the first place.
//
//			When overwriting A[i] with constant need to next look the place with the value A[i]
//			stored before the write. This will be a cycle.
//
// Time complexity: O(n)
// Space complexity: O(1), when using the input array.
//
//			If we do not want to pre-process then constant cannot be used. Instead we can mark each
//			place i with some function of i and then check if it contains the function value.
//			For example, index i stores (i+1) and then check if is.

#include <bits/stdc++.h>
using namespace std;

const int FOUND = -1;
const int NOT_FOUND = -2;


int FindFirstMissingPositive(vector<int>& A)
{
	// Pre-process to change all array entry matching FOUND to NOT_FOUND
	for(size_t i=0; i<A.size() ; ++i) {
		if(A[i] == FOUND) {
			A[i] = NOT_FOUND;
		}
	}

	for(int i=0; i< (int)A.size() ; ++i) {
		if(A[i] == FOUND) {
			continue;
		}
		int t=A[i];
		while( t>0 && t<=(int)A.size() && t != FOUND) {
			int value_lost = A[t-1];
			A[t-1] = FOUND;
			t = value_lost;
		}
	}

	for(size_t i=0; i<A.size() ; ++i) {
		if(A[i] != FOUND) {
			return i+1;
		}
	}
	return NOT_FOUND;
}

int main()
{
	vector<int> A = {3,5,4,-1,5,1,-1};
	cout << "First missing positive number: " << FindFirstMissingPositive(A) << endl;
}
