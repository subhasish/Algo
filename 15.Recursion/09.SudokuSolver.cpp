/*
 * 09.SudokuSolver.cpp
 *
 * Problem: Implement a sudoku solver
 *
 *  Created on: Apr 15, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Similar to N-Queen problem. Try all possibilities but constrained based on what we placed so far.
//			Backtracking. Pass partial placements.
//
// Time complexity:
//			In general sudoku solver is NP-complete. Time complexity is exponential.

typedef vector<int> VI;
typedef vector<VI> VVI;

bool IsValidToAdd(int val, int row, int col, VVI& sudoku)
{
	for(int i=0 ; i< (int)sudoku.size() ; ++i) {  // check row
		if(sudoku[row][i] == val) {
			return false;
		}
	}

	for(int i=0 ; i< (int)sudoku.size() ; ++i) {  // check column
		if(sudoku[i][col] == val) {
			return false;
		}
	}

	// check region constraint
	int region_size = sqrt(sudoku.size());
	int block_row = row/region_size;
	int block_column = col/region_size;
	for(int i = block_row * region_size ; i < (block_row + 1)* region_size ; ++i ) {
		for(int j = block_column * region_size ; j < (block_column + 1) * region_size ; ++j) {
			if(sudoku[i][j] == val) {
				return false;
			}

		}
	}

	return true;
}

bool SolvePartialSudoku(int next_row, int next_col, VVI& partial_assignment)
{
	if(next_row == (int) partial_assignment.size()) {
		return true;	// Entire matrix has been filled
	}

	// Go to next row
	if(next_col >= (int) partial_assignment[0].size()) {
		return SolvePartialSudoku(next_row + 1, 0, partial_assignment);
	}

	// Skip nonempty entries
	if(partial_assignment[next_row][next_col] != 0) {
		return SolvePartialSudoku(next_row, next_col + 1, partial_assignment);
	}

	for(int val = 1; val <= (int) partial_assignment.size() ; ++val) {
		if(IsValidToAdd(val, next_row, next_col, partial_assignment)) {
			partial_assignment[next_row][next_col] = val;
			if(SolvePartialSudoku(next_row, next_col + 1, partial_assignment)) {
				return true;
			}
			partial_assignment[next_row][next_col] = 0; // back track
		}
	}

	return false;
}

bool SolveSudoku(VVI& partial_assignment)
{
	return SolvePartialSudoku(0, 0, partial_assignment);
}


int main() {
	VVI s1 =
	{
			{9,8,1,7,0,0,0,0,0},
			{6,0,0,0,9,0,5,0,0},
			{0,0,4,0,0,3,0,0,0},
			{7,0,0,0,0,0,0,6,0},
			{0,5,0,6,0,0,0,7,0},
			{0,0,0,0,0,0,2,0,1},
			{0,9,0,5,0,0,0,8,0},
			{0,0,3,0,0,0,4,0,0},
			{0,0,0,0,0,1,0,0,2}
	};

	VVI s2 =
	{
			{0,0,0,1,0,5,0,0,0},
			{1,4,0,0,0,0,6,7,0},
			{0,8,0,0,0,2,4,0,0},
			{0,6,3,0,7,0,0,1,0},
			{9,0,0,0,0,0,0,0,3},
			{0,1,0,0,9,0,5,2,0},
			{0,0,7,2,0,0,0,8,0},
			{0,2,6,0,0,0,0,3,5},
			{0,0,0,4,0,9,0,0,0}
	};

	cout << "Sudoku solvable: " << SolveSudoku(s1) << endl;
	cout << "Sudoku solvable: " << SolveSudoku(s2) << endl;
}
