/*
 * HC.33.MaxRectangle.cpp
 *
 * Problem: The problem has application to image processing.
 * 			Let A be an n X m boolean 2D array.
 *
 * 			Design an algorithm for computing the largest 2D array subarray containing only 1s.
 *
 *  Created on: Jan 10, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

//Solution:
//			Brute-force approach is to examine all 2D subarrays. There are m^2*n^2 subarrays,
//			characterized by two diagonal endpoints of the. So overall time complexity is O(m^3*n^3).
//
//			This can be easily reduced to O(m^2*n^2) by processing 2D subarrays by size and
//			reusing the results. While checking for subarray A[i,i+a][j,j+b] we can check if
//			A[i,i+a-1][j,j+b-1], A[i+a,i+a][j,j+b-1], A[i,i+a-1][j+b,j+b], and A[i+a][j+b] are feasible.
//			This will use O(m^2*n^2) space as well.
//
//			Another way to approach the problem is first computing maximum number of 1s from that point
//			towards down and right. Computing this information will take O(m*n) time and O(m*n) storage.
//			Say for point (i,j) we store (h_ij,w_ij). Then for each point, if we go over only points
//			in one direction, say down, and take minimum number of 1s in other direction, say right,
//			and while going compute current rectangle size and keep track of maximum while doing this,
//			Then we can compute the maximum for each point in O(m) or O(n) time. So overall time
//			complexity can be O(m*n^2) or O(n * m^2).

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

	int max_rect_area = 0;
	for(int i=0 ; i < (int)A.size() ; ++i) {
		for(int j=0 ; j < (int)A[i].size() ; ++j) {
			//Process (i,j) if it is feasible
			if(A[i][j]) {
				//Prune: If it is possible to even exceed max area
				if(table[i][j].h * table[i][j].w > max_rect_area) {
					int min_width = table[i][j].w;
					for(int a=0 ; a < table[i][j].h ; ++a) {
						min_width = min(min_width, table[a][j].w);

						//Update max area every time as max area may no use full table[i][j].h
						//that may decrease the min width
						max_rect_area = max(max_rect_area, min_width * (a+1));
					}
				}
			}
		}
	}

	return max_rect_area;
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
