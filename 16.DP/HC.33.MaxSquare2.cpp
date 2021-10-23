/*
 * HC.33.MaxSquare.cpp
 *
 * Problem: The problem has application to image processing.
 * 			Let A be an n X m boolean 2D array.
 *
 * 			Design an algorithm for computing the largest 2D square subarray containing only 1s.
 *
 *  Created on: Jan 10, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

//Solution:
//			We have solved this problem in another way in DP/HC.33.MaxSquare.cpp. Here is little
//			simpler approach without storing the number of 1s in down and right side.
//
//			For each (i,j) if we store the side of the maximum square for which (i,j) is the
//			bottom-right corner then:
//			DP(i,j) = min(DP(i-1,j), DP(i-1,j-1), DP(i,j-1)) + 1

int MaxRectangle(const vector<vector<bool>>& A) {

	//DP table to store side of the square where (i,j) is the bottom-right corner
	vector<vector<int>> side_table(A.size(), vector<int>(A.front().size()));
	int max_square_area = 0;

	for(int i = 0 ; i < (int) A.size() ; ++i) {
		for(int j = 0 ; j < (int) A.front().size() ; ++j) {
			//Process (i,j) if it is feasible
			if(A[i][j]) {
				//Find the side of the maximum square area with A[i][j] as its top-left corner
				int prev_side = (i>0) ? min(side_table[i-1][j], ((j>0) ? side_table[i-1][j-1] : 0)) : 0;
				prev_side = min(prev_side, ((j>0) ? side_table[i][j-1] : 0));
				side_table[i][j] = prev_side + 1;

				//Update maximum area if possible
				max_square_area = max(max_square_area, side_table[i][j] * side_table[i][j]);
			}
		}
	}

	return max_square_area;
}

int main() {
	vector<vector<bool>> A =
	{
			{ false, false,  true,  true, false,  true, false, false},
			{  true,  true,  true,  true, false, false,  true,  true},
			{ false,  true,  true,  true,  true, false,  true,  true},
			{ false,  true,  true,  true, false,  true,  true,  true},
			{  true, false,  true,  true, false, false,  true, false},
			{ false, false, false,  true,  true,  true, false, false},
			{ false,  true, false, false,  true, false,  true, false},
			{  true,  true,  true, false,  true,  true, false,  true},
			{  true,  true, false, false, false, false,  true,  true},
	};

	cout << "Maximum rectangle has area = " << MaxRectangle(A) << endl;
}
