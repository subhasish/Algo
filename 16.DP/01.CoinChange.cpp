/*
 * 01.CoinChange.cpp
 *
 * Problem: Given a final score and all possible scores of individual play compute the number of
 * 			combinations (order does not matter) of plays that can result in the final score.
 *
 * 			Same as, coin change problem:
 * 			Given a value N and infinite supply of each of S={S1, S2,..., Sm} valued coins, how
 * 			many ways can we make the change? The order of the coins does not matter.
 *
 * 			Basically finding all possible combinations summing up to a given number.
 *
 * 			Variant:
 * 			When order matters, give the number of possible sequences of plays that can give the
 * 			final score.
 *
 *
 *  Created on: Apr 22, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			We can see it is similar to the problem of finding all possible combinations.
//			There the restriction was total number of elements (subset size), here total score/value.
//			Also there one element could appear one time, and here element may appear multiple times.
//
//			If we have number of solutions of N from {S1, S2,..., Sm-1} and of (N-Sm) from
//			full set of coins then we can compute the result for the full set.
//			That would be sum of those two numbers.
//
//			***First would correspond to cases when Sm was not present in the solution and second
//			one where at least one Sm is used.
//
//			So besides N, the set also becomes one input of the function. In normal combination
//			function we removed element from main array and passed that. Another way is to pass the
//			fixed array and pass a parameter m and callee will only consider element from 1 to m.
//			So F(m,N)=F(m-1,N)+F(m,N-Sm)
//
//			When thinking this kind of problem I was always blocked by the thought that I need to
//			consider all possible of combinations and there is no ordered way to that. But
//			seeing these problems it is clear that there is ordered way to do this.
//
//			Base case is for all m, when N=0 the result is 1, score 0 is only obtained by not
//			including any element. In enumeration tree, N=0 correspond to reaching a leaf, and
//			we want to count the path by counting 1 for N=0.
//
//			It turns out that we would compute the function for same (m,n) pair many times.
//			Memoization can help us with that. Store the result in a 2D array and reuse that.
//
//			Top-down vs Bottom-up:
//			The recurrence relation should be easy to form bottom solution. Fill the arrays from
//			smaller indices to larger indices. For bottom-up especially be careful of overshooting.
//			That is trying to find solutions of subproblem (negative) that does not exist.
//
//			Time complexity is O(m*N) in bottom up one, space complexity also same.
//
// Reuse caching to reduce space:
//			Note that for solution for m, we need to look only up to (m-1). So we can reuse the
//			previous row for (m-1) to store the current solution. All solution for (m-1) must be
//			computed before computing solution for m. Then for m, compute 1 to N in incremental
//			fashion. So we need to keep only one 1D array where cache[i] will store the
//			final number of combinations for total score i.
//
// Variant:
//			When sequence matters, is just like permutation with less restriction that we can still
//			use previous value we used before.

int CombinationSum(const vector<int> S, int N)
{
	int m = (int) S.size();
	// cache[i][j] will hold number of possible solution for sum j from set S[0..i]
	vector<vector<int>> cache(m, vector<int>(N+1,0));

	for(int i=0; i<m ; ++i) {
		cache[i][0] = 1;		// Base case: 0 score in 1 way, when none is selected
	}

	for(int i=0; i<m ; ++i) {
		for(int j=1 ; j<=N ; ++j) {
			// Without counting m th play/coin
			int without_this = (i>=1) ? cache[i-1][j] : 0;

			// With at lease one of m th play/coin
			int with_at_least_one = ((j-S[i]) >= 0) ? cache[i][j-S[i]] : 0;

			cache[i][j] = without_this + with_at_least_one;
		}
	}

	return cache[m-1][N];
}

int CombinationSum1DCache(const vector<int> S, int N)
{
	vector<int> cache(N+1,0);	// cache[j]  will store the count for sum of j
								// with coins from S[0..i-1] when we are at iteration i

	cache[0] = 1;				// Base case: 0 score in 1 way, when none is selected

	for(int i=0; i< (int)S.size() ; ++i) {
		for(int j=1 ; j<=N ; ++j) {
			// Without counting m th play/coin
			int without_this = cache[j];

			// With at lease one of m th play/coin
			int with_at_least_one = ((j-S[i]) >=0 ) ? cache[j-S[i]] : 0;

			cache[j] = without_this + with_at_least_one;
		}
	}

	return cache[N];
}

// Variant: where sequence matters
int PermutationSum(vector<int>& S, int N)
{
	if(N<0) return 0;
	if(N==0) return 1;

	int result = 0;
	for(size_t i=0 ; i< S.size() ; ++i) {
		result += PermutationSum(S, N-S[i]);
	}
	return result;
}

int main()
{
	vector<int> S = {1, 2, 3};
	cout << "Total number of combinations = " << CombinationSum(S, 4) << endl;
	cout << "Total number of combinations = " << CombinationSum1DCache(S, 4) << endl;

	cout << "Total number of permutations = " << PermutationSum(S, 4) << endl;

	vector<int> Steps = {1,2};
	cout << "Total number of ways to reach 4 using step at most 2: " << PermutationSum(Steps, 4) << endl;
}
