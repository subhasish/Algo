/*
 * 00.TwoSum.cpp
 *
 * Problem:
 * 			Write a program that takes a sorted array and a target value and determines if
 * 			there are two values in the array that add up to that value.
 *
 *  Created on: Jun 2, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			One solution is to store all the elements in a hash table and then iterate over
//			all the elements and check if (target - element) is present in the hash table.
//			But this solution takes O(n) extra space.
//
//			Another solution is to shrink the array such that solution always exists inside
//			the subarray.
//
//			Specifically, if sum of the leftmost and rightmost element is smaller than target
//			then leftmost element cannot be part of the solution, we need larger element.
//			Same for rightmost element.

typedef vector<int> VI;

// Assume input is sorted
bool HasTwoSum(const VI& A, int target)
{
	for(int i=0, j=A.size()-1 ; i<j ; ) {
		int sum = A[i]+A[j];
		if(sum == target) {
			return true;
		} else if(sum < target) {
			++i;
		} else {	// sum > target
			--j;
		}
	}
	return false;
}

int main()
{
	VI A = {-2, 1, 2, 4, 7, 11};

	cout << HasTwoSum(A, 2) << endl;
	cout << HasTwoSum(A, 10) << endl;

}
