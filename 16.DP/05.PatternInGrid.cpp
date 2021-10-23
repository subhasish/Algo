/*
 * 05.PatternInGrid.cpp
 *
 * Problem: Write a program that takes as argument a 2D array and a 1D array, and checks whether
 * 			the 1D array occurs in the 2D array.
 * 			Each character in the pattern can be any adjacent (4 directions) of the previous
 * 			character.
 * 			Assume repeating a cell in the 2D array is allowed.
 *
 * 			Variant 1:
 * 			Repetition of a cell in the 2D array is not allowed.
 *
 * 			Variant 2:
 * 			Enumerate all solutions when you cannot visit a cell more than once.
 *
 *
 *  Created on: May 1, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
// 			The pattern can start from each cell. So we need to look each cell as start point.
//			Then we need to consider all neighbors for next character.
//
//			As we consider all these possibilities note that same suffix can be matched at a
//			position multiple times. So it can be avoided using DP.
//			Given a position and rest of the string to match, there would be a unique solution
//			that all encompassing problems can use.
//
//			The state parameter rest of the string can be simplified by using only integer
//			offset that denotes start of the suffix.
//
//			Can be easily done by top-down recursive calls. For bottom up we need to start from
//			the smallest string and then grow for larger string, i.e., offset will go down from
//			(string length - 1) to 0. While growing we will look for solution in neighbors for
//			offset=current offset - 1. Final result will be looking for any solution in the grid
//			for offset == 0.
//
// Time complexity: The state space need to be
//
// Variant : It is solved separately.

bool SearchPatternInGrid(const vector<vector<int>>& grid, vector<int> pattern)
{
	bool DP[grid.size()][grid[0].size()][pattern.size()];

//	memset(DP, false, sizeof(DP));
//	cout << "Sizes: " << sizeof(DP[0][0][0]) << " " << sizeof(DP[0][0]) << " " << sizeof(DP[0]) << " " << sizeof(DP) << endl;


	// Base case: for last one char suffix
	int offset = pattern.size()-1;
	for(int x=0; x < (int) grid.size() ; ++x) {
		for(int y=0; y < (int) grid[0].size() ; ++y) {
			if(grid[x][y] == pattern[offset]) {
				DP[x][y][offset] = true;
			} else {
				DP[x][y][offset] = false;
			}
		}
	}


	// Recursive case: See if neighbors match the suffix after this character
	for(int offset = pattern.size()-2 ; offset>=0 ; --offset) {
		for(int x=0; x < (int) grid.size() ; ++x) {
			for(int y=0; y < (int) grid[0].size() ; ++y) {
				if(grid[x][y] == pattern[offset]) {
					if((x>0 && DP[x-1][y][offset+1]) ||
							(y>0 && DP[x][y-1][offset+1]) ||
							((x< (int)grid.size()-1) && DP[x+1][y][offset+1]) ||
							((y< (int)grid[0].size()-1) && DP[x][y+1][offset+1])) {

						DP[x][y][offset] = true;
					} else {
						DP[x][y][offset] = false;
					}
				} else {
					DP[x][y][offset] = false;
				}
			}
		}
	}

	// Final result: search if matched at any cell for offset 0
	for(int x=0; x < (int) grid.size() ; ++x) {
		for(int y=0; y < (int) grid[0].size() ; ++y) {
			if(DP[x][y][0] == true) {
				return true;
			}
		}
	}
	return false;
}

int main()
{
	vector<vector<int>> grid =
	{
			{ 1, 2, 3, 4, 5, 6},
			{ 3, 5, 7, 9, 2, 4},
			{ 1, 3, 5, 7, 4, 3}
	};

	vector<int> pat1 = {3,7,5,3,5,7,4,7};
	vector<int> pat2 = {3,7,5,3,5,7,4};
	vector<int> pat3 = {3,7,5,3,5,8};
	vector<int> pat4 = {1};

	cout << SearchPatternInGrid(grid, pat1) << endl;
	cout << SearchPatternInGrid(grid, pat2) << endl;
	cout << SearchPatternInGrid(grid, pat3) << endl;
	cout << SearchPatternInGrid(grid, pat4) << endl;
}
