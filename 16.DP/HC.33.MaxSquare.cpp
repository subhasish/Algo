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
//			We have solved the rectangle version of the problem in DP/HC.33.MaxRectangle.cpp. Here is
//			what we did there:
//
//			Approach was to first computing maximum number of 1s from that point towards down and
//			right. Computing this information will take O(m*n) time and O(m*n) storage.
//			Say for point (i,j) we store (h_ij,w_ij). Then for each point, if we go over only points
//			in one direction, say down, and take minimum number of 1s in other direction, say right,
//			and while going compute current rectangle size and keep track of maximum while doing this,
//			Then we can compute the maximum for each point in O(m) or O(n) time. So overall time
//			complexity can be O(m*n^2) or O(n * m^2).
//
//			Computing maximum square using the auxiliary data is relatively is easy.
//			Suppose we know the length s of the largest square with A[i+1][j+1] as its top-left
//			corner. Then the length of the largest square with A[i][j] as it top-left corner is
//			at most s+1. That will only occur if h_ij>s and w_ij>s. The general expression will be
//			min(s+1, h_ij, w_ij).
//			Note that this is O(1) computation. So overall time complexity will be O(m * n).

int MaxRectangle(const vector<vector<bool>>& A) {
	struct MaxHW {
		int h,w;
	};

	//DP table to store (h, w) for each (i,j)
	vector<vector<MaxHW>> table(A.size(), vector<MaxHW>(A.front().size()));

	//Compute the largest stretch of 1s for each cell in right and downward direction
	for(int i = (int) A.size()-1 ; i>=0 ; --i) {
		for(int j = (int) A.front().size()-1 ; j >=0 ; --j) {
			// find largest h such that (i,j) to (i+h-1, j) are feasible
			// find largest w such that (i,j) to (i, j+w-1) are feasible
			table[i][j] = A[i][j] ?
							MaxHW{(i+1 < (int)A.size() ? table[i+1][j].h + 1 : 1),
								   j+1 < (int)A[i].size() ? table[i][j+1].w + 1 : 1} :
							MaxHW{0,0};
		}
	}

	vector<vector<int>> side_table(A.size(), vector<int>(A.front().size()));
	int max_square_area = 0;

	for(int i = (int) A.size()-1 ; i>=0 ; --i) {
		for(int j = (int) A.front().size()-1 ; j >=0 ; --j) {
			//Process (i,j) if it is feasible
			if(A[i][j]) {
				//Find the side of the maximum square area with A[i][j] as its top-left corner
				int side = min(table[i][j].h, table[i][j].w);
				if(i < (int)A.size()-1 && j < (int)A[i].size()-1) {
					side = min(side, side_table[i+1][j+1]+1);
				}
				side_table[i][j] = side;

				//Update maximum area if possible
				max_square_area = max(max_square_area, side * side);
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
