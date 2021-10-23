/*
 * 03.NumberOfWays.cpp
 *
 * Problem: Write a program that counts how many ways you can go from top-left to the
 * 			bottom-right in a 2D array by only moving down or right.
 *
 * 			Variant 1:
 * 			Do it in space O(min(m,n))
 *
 * 			Variant 2:
 * 			Solve it in presence of obstacles, specified by a boolean 2D array
 *
 * 			Variant 3:
 * 			Path with maximum sum where each cell has some positive resource
 *
 * 			Variant 4:
 * 			Path with maximum when path can begin or end anywhere. Cell can have negatives.
 * 			But movement is still restricted to either bottom or right.
 *
 * 			Variant 5 & 6:
 * 			Monotone and strict monotone numbers.
 *
 *  Created on: Apr 28, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Only way to come to cell (i,j) is from either (i-1,j) or from (i,j-1).
//			So total way to reach (i,j) is total of these two possibilities.
//
//			DP can be used to store the results and avoid re-computations.
//
//			Base case would be for top row and left column where it can be reached in one way only
//			from left and up respectively
//
//			Bottom up should be easy.
//
// Complexity:
//			Both time and space complexity is O(mn)
//
// Analytical solution:
//			A valid path will have (n-1) down move and (m-1) right move. So total path length is
//			(n+m-2). So total possible solution is (n+m-2) choose (n-1).
//
// Variant 1:
//			Only data from previous row/column is necessary. So space can be reused.
//
// Variant 2:
//			If current cell is an obstacle then there is no solution for that. If any of the
//			previous cell has obstacle then that cannot be considered.
//
// Variant 3:
//			Instead of sum, consider max
//
// Variant 4:
//			Somewhat similar to maximum sub-array problem. If I get negative from my ancestors
//			then it's better to start at current. Once done we may need to search the end with
//			maximum in the 2D array using extra iteration.
//
// Variant 5 & 6:
//			Handled in separate solution

int NumberOfWays(int n, int m)
{
	// Table to store the total number of
	int DP[n][m];

	// Base case
	for(int i=0 ; i<n ; ++i) {
		DP[i][0] = 1;
	}
	for(int j=0 ; j<m ; ++j) {
		DP[0][j] = 1;
	}

	// Recurrence
	for(int i=1 ; i<n ; ++i) {
		for(int j=1 ; j<m ; ++j) {
			DP[i][j] = DP[i-1][j] + DP[i][j-1];
		}
	}

	return DP[n-1][m-1];
}

int main()
{
	cout << "Ways to reach (5,4) = " << NumberOfWays(5,4) << endl;
	cout << "Ways to reach (5,5) = " << NumberOfWays(5,5) << endl;
}
