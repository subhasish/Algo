/*
 * 17.IsSudokuValid.cpp
 *
 * Problem: Given a partially filled Sudoku, determine whether it is a valid one or not
 *
 *  Created on: Sep 9, 2017
 *      Author: subha
 */

#include<bits/stdc++.h>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

bool HasDuplicate(VVI& sudoku, int start_row, int end_row, int start_col, int end_col)
{
	deque<bool> isPresent(sudoku.size()+1, false);

	for(int i=start_row; i<end_row ; ++i) {
		for(int j=start_col; j<end_col ; ++j) {
			if(sudoku[i][j] != 0 && isPresent[sudoku[i][j]] == true)
				return true;

			isPresent[sudoku[i][j]] = true;
		}
	}
	return false;
}

// The value 0 in Sudoku represent empty cell
bool IsValidSudoku(VVI& sudoku)
{
	int sz = sudoku.size();

	//check row constraints
	for(int i=0; i<sz ; i++) {
		if(HasDuplicate(sudoku,i,i+1,0,sz))
			return false;
	}

	//check column constraints
	for(int i=0; i<sz ; ++i) {
		if(HasDuplicate(sudoku,0,sz,i,i+1))
			return false;
	}

	//check region constraints
	int rgSz = sqrt(sz);
	for(int i=0; i<sz ; i += rgSz) {
		for(int j=0; j<sz ; j += rgSz ) {
			if(HasDuplicate(sudoku,i,i+rgSz,j,j+rgSz))
				return false;
		}
	}

	return true;
}

int main()
{
	VVI sudoku = {
			{5,3,0,0,7,0,0,0,0},
			{6,0,0,1,9,5,0,0,0},
			{0,9,8,0,0,0,0,6,0},
			{8,0,0,0,6,1,0,0,3},
			{4,0,0,8,0,3,0,0,1},
			{7,0,0,0,2,0,0,0,6},
			{0,6,0,0,0,0,2,8,0},
			{0,0,0,4,1,9,0,0,5},
			{0,0,0,0,8,0,0,7,9}};

	cout << IsValidSudoku(sudoku) << endl;

}



