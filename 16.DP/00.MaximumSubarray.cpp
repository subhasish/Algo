/*
 * 00.MaximumSubarray.cpp
 *
 * Problem: Find a continuous subarray that has maximum sum
 *
 *  Created on: Apr 21, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Brute force is to sum up each subarray and find maximum. O(n^3).
//			It can be improved to O(n^2) by using cumulative sum and computing S[i,j]=C[0,j]-C[0,i]
//
//			Divide and conquer can also be used as in merge/quick sort. If we partition in half and
//			each half returns maximum in each part with maximum subarray including first element and
//			last element. Then we can combine them to find maximum in the full array by taking
//			maximum of maximum of each half and sum of maximum subarray including last of left and
//			first of right. T(n)=O(n log n)
//
//			Another observation is that maximum subarray ending at an element can easily be extended
//			to next element. If maximum including last element is positive then we can include that
//			in the solution ending at current element. Otherwise we can start new subarray from
//			current element. T(n)=O(n)
//			This will give correct answer as it computes maximum subarray ending at each node and
//			actual maximum subarray ends at some node, right?

int FindMaximumSubarray(const vector<int>& A)
{
	int maximum=A[0];
	int max_ending_at_current=A[0];

	for(int i=1 ; i < (int)A.size() ; ++i) {
		if(max_ending_at_current > 0) {
			max_ending_at_current += A[i];
		} else {
			max_ending_at_current = A[i];
		}

		if(maximum < max_ending_at_current) {
			maximum = max_ending_at_current;
		}
	}

	return maximum;
}


int main()
{
	vector<int> A = {-2, -3, 4, -1, -2, 1, 5, -3};
	cout << "Maximum subarray sum: " << FindMaximumSubarray(A) << endl;
}
