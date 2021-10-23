/*
 * 12.LongestNonDecreasing.cpp
 *
 * Problem: Write a program that takes an input array and finds the length of longest
 * 			nondecreasing subsequence in the array. The numbers in the subsequence need
 * 			not to be consecutive.
 *
 * Variant 1:
 * 			Return the subsequence.
 *
 * Variant 2:
 * 			Find longest alternating subsequence.
 *
 * Variant 3:
 * 			Find longest weakly alternating subsequence.
 *
 * Variant 4:
 * 			A sequence is convex if a[i] < (a[i-1]+a[i+1])/2 for all i. Find longest convex one.
 *
 * Variant 5:
 * 			A sequence is bitonic if there exists a k such the a[i]<a[i+1] for i<k and
 * 			a[i]>a[i+1] for i>=k. That is first increasing then decreasing. Find longest bitonic.
 *
 * Variant 6:
 * 			Do it for points in 2D
 *
 * Variant 7:
 * 			Find longest nondecreasing subsequence in O(n log n) time
 *
 *  Created on: May 12, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			It is clear that longest nondecreasing subsequence in A[0..i] may not not end at i.
//			So if we store that result for i then it would be hard to grow based on previous
//			results.
//
//			Instead if we store for each i, the longest nondecreasing subsequence ending at i
//			then that would be easy to grow by seeing the value at A[i].
//			So, DP[i] = 1  + max(DP[j]) where j<i and A[j] <= A[i]
//
//			Also we cannot stop at first j<i where A[j]<=A[i]. A[j] could be much smaller and
//			there could be other j that has DP[j] with large value.
//
// Time complexity:
//			Time complexity is O(n^2)
//
// Variant 1:
//			Store the last index in separate array
//
// Variant 2:
//			Store two arrays one where element is greater and another for smaller. Combine
//
// Variant 3: Problem statement not clear
//
// Variant 4:
//			Store the sequence. Store all possible previous two indices that satisfy the convexity.
//			While growing check if any of them satisfy current for current element.
//			!!!Check for better
//
// Variant 5:
//			Store both increasing and decreasing subsequence for each i. Then check sum for each i.
//
// Variant 6:
//			Simply extend this algorithm in 2D.
//
// Variant 7:
//			https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
//			See implementation in different file


int LongestNonDecreasingSubsequence(const vector<int>& A)
{
	// DP[i] = length of longest nondecreasing subsequence ending with A[i]
	vector<int> DP(A.size(),1);

	// Base case (i==0) is already done by initializing with 1

	for(size_t i=1 ; i<A.size() ; ++i) {
		for(int j=i-1 ; j>=0 ; --j) {
			if(A[i] >= A[j]) {
				DP[i] = max(DP[i], 1+DP[j]);
			}
		}
	}

	// Find maximum over the whole array
	int result=0;
	for(size_t i=0 ; i<DP.size() ; ++i) {
		if(DP[i]>result) {
			result = DP[i];
		}
	}
	return result;
}

int main()
{
	vector<int> A = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9};
	cout << "Length of maximum nondecreasing subsequence = " << LongestNonDecreasingSubsequence(A) << endl;
}
