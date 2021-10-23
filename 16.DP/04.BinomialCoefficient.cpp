/*
 * 04.BinomialCoefficient.cpp
 *
 * Problem: The binomial coefficient (n C k) is short form of n(n-1)..(n-k+1)/k(k-1)..(2)(1).
 * 			If is not obvious that result would always be an integer. Furthermore, direct
 * 			computation of numerator and denominator would result in overflows if integers are
 * 			used even if final result is integer.
 *
 * 			Design an efficient algorithm for computing (n C k) which has the property that it
 * 			never overflows if the final result fits in integer word size.
 *
 *  Created on: Apr 30, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Direct computation would result in overflow. But this number is also the number of
//			way to choose k element from n elements.
//			That is the same as sum of number of ways to choose (k-1) elements from (n-1)
//			elements [when k th element is included] and ways to choose k elements from (n-1)
//			elements [when k th element is not included].
//
//			This recurrence relation can easily be transformed in to a DP of two parameters.
//
//			Time and space complexity both O(nk)


int ComputeBinomialCoefficient(int n, int k)
{
	// DP array
	int DP[n+1][k+1];

	// Base case
	for(int i=1; i<=n ; ++i) {
		DP[i][1] = i;						// ways to choose 1 element from n is n
	}

	for(int i=2; i <=n ; ++i) {
		for(int j=2; j <= k ; ++j) {		// Note j can be greater than i.
			if(i <= j) {
				DP[i][j] = 1;				// if i <= j, only one way. Kind of base case
			} else {
				DP[i][j] = DP[i-1][j] + DP[i-1][j-1];
			}
		}
	}

	return DP[n][k];
}

int main()
{
	cout << " 5 C 2 = " << ComputeBinomialCoefficient(5,2) << endl;
	cout << " 5 C 3 = " << ComputeBinomialCoefficient(5,3) << endl;
	cout << " 50 C 3 = " << ComputeBinomialCoefficient(50,3) << endl;
	cout << " 50 C 47 = " << ComputeBinomialCoefficient(50,47) << endl;
	cout << " 50 C 50 = " << ComputeBinomialCoefficient(50,50) << endl;
	cout << " 50 C 100 = " << ComputeBinomialCoefficient(50,100) << endl;
}
