/*
 * HC.31.CircularMaxSubarray.cpp
 *
 * Problem: We have seen how maximum subarray sum can be computed in DP/00.MaximumSubarray.cpp, but
 * 			it cannot solve for circular array. In circular array first and last elements are
 * 			considered adjacent.
 *
 * 			Given a circular array A, compute its maximum subarray sum in O(n) time.
 * 			Also try to do it in O(n) time and O(1) space.
 *
 *  Created on: Jan 4, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Recall that the conventional maximum subarray is computed by computing the maximum sum
//			S[i] ending at i as max(S[i-1]+A[i], A[i]).
//
//			One approach for maximum circular subarray is to break the problem into two separate
//			instances. First instance is the non-circular one and second one is the circular one.
//
//			For circular instance, we want to find maximum subarray starting at index 0 and maximum
//			subarray ending at index (n-1), and then take their sum.
//			But these two can have overlap. And subtracting the overlap may not give the right result.
//
//			Instead, we compute for each i the maximum subarray sum starting at 0 and ending at or
//			before i, and maximum subarray that starts after i and ends at the last element.
//			Then take maximum over all i.
//
//			Computing such maximum i can be done first by creating two prefix maximum sum and suffix
//			maximum sum arrays and then compute the sum for each i in O(1). Same code can be used to
//			compute for prefix and suffix. For suffix we can pass {rbegin(), rend()}
//			and then reverse() the result.

int MaxSubarray(const vector<int>& A);
int CircularMaxSubarray(const vector<int>& A);
vector<int> ComputeRunningMaximum(const vector<int>& A);

int MaxSumarraySumInCircular(const vector<int>& A) {
	return max(MaxSubarray(A), CircularMaxSubarray(A));
}

// Calculates the non-circular solution
int MaxSubarray(const vector<int>& A) {
	int maximum=A[0];
	int max_ending_at_current=A[0];

	for(int i=1 ; i < (int)A.size() ; ++i) {
		max_ending_at_current = max(max_ending_at_current + A[i], A[i]);
		maximum = max(maximum, max_ending_at_current);
	}

	return maximum;
}

// Calculates the solution which is circular
int CircularMaxSubarray(const vector<int>& A) {
	// maximum subarray sum starts at index 0 and ends at or before index i
	vector<int> max_begin = ComputeRunningMaximum(A);

	// maximum subarray sum starting at or after index i+1 and ending at last element
	vector<int> max_end = ComputeRunningMaximum({A.crbegin(), A.crend()});	// NOTE: rbegin() to rend()
	reverse(max_end.begin(), max_end.end());

	// Calculate the circular max
	int circular_max = 0;
	for(size_t i=0 ; i < A.size()-1 ; ++i) {
		circular_max = max(circular_max, max_begin[i] + max_end[i+1]);
	}
	return circular_max;
}

vector<int> ComputeRunningMaximum(const vector<int>& A) {
	vector<int> running_maximum;

	// surely includes first
	int sum = A.front();
	running_maximum.emplace_back(sum);

	for(size_t i=1 ; i < A.size() ; ++i) {
		sum += A[i];
		running_maximum.emplace_back(max(sum, running_maximum.back()));	// sum upto this may not be max
	}
	return running_maximum;
}

int main() {
	vector<int> A = {10, -4, 5, -4, 10};
	cout << "Max in circular = " << MaxSumarraySumInCircular(A) << endl;

	vector<int> B = {10, 4, 5, -4, 10};
	cout << "Max in circular = " << MaxSumarraySumInCircular(B) << endl;

	vector<int> C = {-10, -4, 5, -4, 10};
	cout << "Max in circular = " << MaxSumarraySumInCircular(C) << endl;
}
