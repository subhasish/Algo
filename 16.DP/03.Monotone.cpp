/*
 * 03.Monotone.cpp
 *
 * Problem: A decimal number can be thought as sequence of digits 0-9 where first digit cannot be 0.
 * 			A decimal number is a monotone if D[i] <= D[i+1] for all i.
 * 			Write a program which takes a positive number k and compute the number of decimal
 * 			numbers of length k that are monotone.
 *
 * 			Variant 1:
 * 			A number is strictly monotone if D[i] < D[i+1] for all i. Compute the number of all
 * 			possible strictly monotone numbers of size k.
 *
 *  Created on: Apr 29, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			For (i+1) th digit the number of way it can be 6 is the sum of ways i th digit can be
//			1, 2, 3, 4, 5 and 6. It is not clear how to compute the number directly.
//
//			Similar to number of ways to reach a cell in 2D array, this also can be solved using
//			a 2D array. Each possible digit can form a row, so total 9 rows and there can be
//			k columns.
//
//			The cell DP[i][j] would represent ways to form monotone number of size j that ends
//			with digit i. Result would be sum of all the cells present in column k.


int Monotone(int k)
{
	// DP[i][j] would represent ways to form monotone number of size j that ends  with digit i.
	int DP[10][k + 1];

	// Base case: number of 1 digit ending with digit i is 1
	for(int i = 1; i <= 9 ; ++i) {
		DP[i][1] = 1;
	}
	//Do not need to consider 0 as if cannot start then it cannot have 0 anywhere. Otherwise it will break monotone constraint.

	for(int j = 2; j <= k ; ++j) {
		for(int i = 1; i <= 9 ; ++i) {
			DP[i][j] = 0;
			for(int t = 1 ; t <= i ; ++t) {  // Sum for all previous digits that are less than equal i
				DP[i][j] += DP[t][j-1];
			}
		}
	}

	// result is sum for column k
	int result=0;
	for(int i = 1 ; i <= 9 ; ++i) {
		result += DP[i][k];
	}

	return result;
}

int StrictMonotone(int k)
{
	// DP[i][j] would represent ways to form monotone number of size j that ends  with digit i.
	int DP[10][k+1];

	// Base case: number of 1 digit ending with digit i is 1
	for(int i = 1; i <= 9 ; ++i) {
		DP[i][1] = 1;
	}
	//Do not need to consider 0 as if cannot start then it cannot have 0 anywhere. Otherwise it will break monotone constraint.


	for(int j = 2; j <= k ; ++j) {
		for(int i = 1; i <= 9 ; ++i) {
			DP[i][j] = 0;
			for(int t = 1; t < i ; ++t) {  // Sum for all previous digits that are less than equal i
				DP[i][j] += DP[t][j-1];
			}
		}
	}

	// result is sum for column k
	int result=0;
	for(int i = 1 ; i <= 9 ; ++i) {
		result += DP[i][k];
	}

	return result;
}


int main()
{
	cout << "Number of monotone numbers of length 7 = " << Monotone(7) << endl;
	cout << "Number of monotone numbers of length 10 = " << Monotone(10) << endl;

	cout << "Number of strict monotone numbers of length 7 = " << StrictMonotone(7) << endl;
	cout << "Number of strict monotone numbers of length 10 = " << StrictMonotone(10) << endl;
}
