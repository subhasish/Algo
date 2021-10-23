/*
 * 10.NumberOfWaysToReach.cpp
 *
 * Problem: You are climbing stairs. You can advance 1 to K steps at a time. Your destination is
 * 			reach exactly n steps.
 * 			Write a program that takes n and k and returns the number of ways in which you can
 * 			get to your destination.
 *
 *  Created on: May 11, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			It is same as the coin change problem where order matters. In coin change problem
//			we were interested in number of combinations of the input set that result in the sum.
//			Here we are interested in the number of permutations that would give the sum.
//
//			Recurrence is F(n,k) = Sum over i=1..k F(n-i,k)
//			Top-down one is done in DP/01.CoinChange.cpp
//
//			Bottom up is to compute the amount from n=1..n, F(0,k)=1
//
//			Note the Base case, where case for 0 is counting 1, to count for path that exactly
//			reached 0. Also can be thought as none is selected in 1 way.

int NumberOfWaysToReachTopDown(int n, int k)
{
	if(n < 0)  return 0;		// overshoot
	if(n == 0) return 1;		// No step remaining; exactly reached by last step

	int result = 0;
	for(int i=1 ; i<=k ; ++i) {
		result += NumberOfWaysToReachTopDown(n-i, k);
	}
	return result;
}

int NumberOfWaysToReachBottomUp(int n, int k)
{
	// DP[i] = number of ways to each n==i
	int DP[n+1];

	// Base case
	DP[0] = 1;		// ALERT!! To count the path that reached to 0

	// Recurrence
	for(int i=1 ; i <= n; ++i) {
		int res = 0;
		for(int j=1; j<=k ; ++j) {	// For all possible last steps
			if(i-j>=0) {
				res += DP[i-j];
			} else {
				// Overshoot; do not count
			}
		}
		DP[i] = res;
	}

	return DP[n];
}

int main()
{
	cout << "Total number of ways to reach 4 using step at most 2: " << NumberOfWaysToReachTopDown(4,2) << endl;
	cout << "Total number of ways to reach 4 using step at most 2: " << NumberOfWaysToReachBottomUp(4,2) << endl;
}
