/*
 * 04.ThreeSum.cpp
 *
 * Problem: Given an input array determine if there are three numbers in the array such that
 * 			they add to a specified number.
 *
 * 			We can choose to solve both version of the problem when same entry can appear
 * 			only one time or multiple times.
 *
 *  Created on: Jun 2, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Similar to the two sum problem three sum can be solved in same way.
//			Only thing is that we need to find (target - element) for each element as sum of two
//			other elements.

typedef vector<int> VI;

bool HasTwoSumExcept(const VI& A, int target, int except_idx) {
	for(int i=0, j=A.size()-1; i<j ; ) {
		if(i == except_idx) { ++i; continue; }
		if(j == except_idx) { --j; continue; }

		int sum = A[i] + A[j];
		if(sum == target) {
			return true;
		} else if(sum < target) {
			++i;
		} else {  // sum > target
			--j;
		}
	}
	return false;
}

bool HasThreeSum(VI& A, int target) {
	sort(A.begin(), A.end());

	for(size_t i=0 ; i<A.size() ; ++i) {
		if(HasTwoSumExcept(A, target-A[i], i)) {
			return true;
		}
	}

	return false;
}


int main()
{
	VI A = {11, 2, 5, 7, 3};

	cout << HasThreeSum(A, 22) << endl;
	cout << HasThreeSum(A, 21) << endl;  //3, 7, 11
}
