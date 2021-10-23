/*
 * HC.07.RookAttack.cpp
 *
 * Problem: Write a program that takes as input a 2D array A of 1s and 0s, where the 0s encode
 * 			the position of the rooks on an m X n chessboard and updates the array to contain
 * 			0s at all the places which can be attacked by the rooks.
 *
 *  Created on: Nov 1, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Rooks only attack the rows and columns they are in. So if we can know which rows
//			and columns have them in one pass and mark full array in second pass that would
//			work.
//
//			But it will need extra O(m + n) memory.
//			We can use the 1st row and 1st column to avoid the extra memory.
//			Only thing is that it can overwrite the information that 1row and first column
//			originally had a 0 on it or not. So first row and and first column has to be
//			handled separately.
//
//			We can store whether 1row and column had a rook in separate boolean variable and
//			based on them mark 1st row and column

void RookAttack(vector<vector<int>>& A) {
	size_t m = A.size(), n = A[0].size();
	bool has_first_row_zero = false, has_first_column_zero = false;

	for(size_t i=0; i<n ; i++) {		// Note if first row has zero
		if(A[0][i] == 0) {
			has_first_row_zero = true;
			break;
		}
	}
	for(size_t i=0; i<m ; i++) {		// Note if first column is zero
		if(A[i][0] == 0) {
			has_first_column_zero = true;
			break;
		}
	}

	for(size_t i=1 ; i<m ; ++i) {		// Note if row or column has 0
		for(size_t j=1 ; j<n ; ++j) {
			if(A[i][j] == 0) {
				A[i][0] = A[0][j] = 0;
			}
		}
	}

	for(size_t i=1 ; i<m ; ++i) {		// Mark rows
		if(A[i][0] == 0) {
			for(size_t j=1 ; j<n ; ++j) {
				A[i][j] = 0;
			}
		}
	}

	for(size_t j=1 ; j<n ; ++j) {		// Mark columns
		if(A[0][j] == 0) {
			for(size_t i=1 ; i<m ; ++i) {
				A[i][j] = 0;
			}
		}
	}

	if(has_first_row_zero) {
		for(size_t j=0 ; j<n ; ++j) {
			A[0][j] = 0;
		}
	}

	if(has_first_column_zero) {
		for(size_t i=0 ; i<m ; ++i) {
			A[i][0] = 0;
		}
	}
}

void PrintBoard(vector<vector<int>>& board) {
	for(vector<int>& list: board) {
		for(int i: list) {
			cout << i << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	vector<vector<int>> board =
	{
			{1,0,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,0,1,1},
			{1,1,1,0,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{0,1,1,1,1,0,1,1},
			{1,1,1,1,1,1,1,1}
	};

	RookAttack(board);
	PrintBoard(board);
}
