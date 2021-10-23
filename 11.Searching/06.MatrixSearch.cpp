/*
 * 06.MatrixSearch.cpp
 *
 * Problem: Given a 2D array whose rows and columns are non-decreasing, find whether an element exists in the array or not.
 *
 *  Created on: Feb 10, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Can compare with middle element and reject 1/4th of the matrix and search in rest. T(n) = 3*T(n/4) + O(1). Gives T(n) = O(x^1.6)
//
//           Another tricky way to approach these problems is to compare with extremal values.
//			 But comparing A[0][0] or A[n-1][n-1] with the number gains nothing, because they are two extreme points.
//
//			 We need to compare with some intermediate point such that we can reject one half or other.
//			 With some experiment, it becomes clear that comparing with A[0][n-1] is useful.
//			 If the number is smaller than A[0][n-1] then we can ignore last column, and
//			 if number is greater than A[0][n-1] then we can ignore the first row
//
// Time complexity: O(n+m)

typedef vector<int> VI;
typedef vector<VI> VVI;

bool MatrixSearch(const VVI& mat, int k)
{
	if(mat.empty() || mat[0].empty())
		return false;

	int row=0, col=mat[0].size()-1;     // Start with last element of the first row

	while(row < ((int) mat.size()) && col > 0) {
		if(mat[row][col] == k) {
			return true;
		} else if(mat[row][col] > k) {
			--col;    // Eliminate this column
		} else {
			row++;    // Eliminate this row
		}
	}

	return false;
}

int main() {
	VVI arr = {
			{ -1, 2, 4, 4, 6},
			{ 1, 5, 5, 9, 21},
			{ 3, 6, 6, 9, 22},
			{ 3, 6, 8, 10, 24},
			{ 6, 8, 9, 12, 25},
			{ 8, 10, 12, 13, 40}
	};

	cout << "Number 7 present in array: " << MatrixSearch(arr, 7) << endl;
	cout << "Number 10 present in array: " << MatrixSearch(arr, 10) << endl;
}
