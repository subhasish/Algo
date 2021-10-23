/*
 * 02.NQueens.cpp
 *
 * Problem: Write a program which returns all distinct non-attacking placements of n queens
 * 			on an NxN chess board.
 *
 *  Created on: Apr 3, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			For finding a solution with nth row the other (n-1) rows should also have a valid
//			solution. That suggests recursion.
//
//			This is enumeration problem like Permutation where we grow recursion tree
//			and at the leaf we would add the leaf to the result and backtrack for next result.
//
//			Go row by row. Try positioning queens in all open positions in current row and then
//			try next row. When last row is filled we know we have a solution.
//			If we fail to fill a row then we know placements in previous rows do not work.
//			We skip rest and try next solution in previous rows. This is backtracking.
//
//			Placement in the board can be stored in an 1D array where value j in position i
//			will mean that a queen is placed in column j of row i. As each row an has only one
//			entry, we can get away with only 1D array. index => row, value => column.
//
//			What position in a row is still open can be obtained by looking at existing placements.
//			Ideally, storing column position for previous rows in enough. But then for each cell we
//			need to check each previous placement.
//			Alternatively we can populate 3 indices for column, forward diagonal and back diagonal
//			and in O(1) figure out if a cell is open or not. Range for column values is 0 to n-1.
//			All forward diagonals have same (i-j) that ranges from -(n-1) to (n-1).
//			All back diagonals have same (i+1) that ranges from 0 to (2n-2).
//
// Time Complexity:
//			Time complexity is lower bounded by number of non attacking placements.
//			But no exact form is known for this quantity as a function of n.
//			But recurrence relation tend to be	T(n) = n*(T(n-1) + 1) = O(n!)
//			At each step at lease there should be one less call because one column is used up.

typedef vector<int> VI;
typedef vector<VI> VVI;

void SolveNQueens(int row, int n, VI& col_placement, VI& col_idx, VI& f_diag_idx, VI& b_diag_idx, VVI& result)
{
	if(row == n) 	// All row 0 to (n-1) done. Valid placement reached.
	{
		result.emplace_back(col_placement);
	}
	else
	{
		for(int col=0; col<n ; ++col)
		{
			if(col_idx[col] == -1 && f_diag_idx[row-col+n-1] == -1 && b_diag_idx[row+col] == -1)
			{
				// This means the position is open

				col_placement[row] = col;											// update placement
				col_idx[col] = 1, f_diag_idx[row-col+n-1]=1, b_diag_idx[row+col]=1;	// update indices

				SolveNQueens(row+1, n, col_placement, col_idx, f_diag_idx, b_diag_idx, result);

				// back track to not affect while trying other positions in the row
				col_placement[row] = -1;													// clear placement
				col_idx[col] = -1, f_diag_idx[row-col+n-1] = -1, b_diag_idx[row+col] = -1;	// clear indices
			}
		}
	}
}

VVI NQueens(int n)
{
	VVI result;
	VI col_placements(n, -1);	// value j in position i indicates row i has queen in position j
	VI col_idx(n, -1), f_diag_idx(2*n-1, -1), b_diag_idx(2*n-1, -1);

	SolveNQueens(0, n, col_placements, col_idx, f_diag_idx, b_diag_idx, result);

	return result;
}

int main()
{
	VVI result = NQueens(8);

	for(VI& oneSol: result) {
		cout << "One solution: ";
		for(int i: oneSol) {
			cout << i << ", ";
		}
		cout << endl;
	}

	// 4 => 2, 5 => 10, 8 => 92
	cout << "Total possible distinct solutions: " << result.size() << endl;
}
