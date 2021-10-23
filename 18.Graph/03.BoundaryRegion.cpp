/*
 * 03.BoundaryRegion.cpp
 *
 * Problem: Let A a 2D array whose entries are either B or W. Write a program
 * 			that takes A and replaces all Ws that cannot reach boundary with a B.
 *
 *  Created on: Jun 23, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Growing all internal cells may take time to decide whether it can reach a boundary.
//			Then we need to again get back and mark all in the region. This is not efficient.
//
//			Instead we can start from boundary cells and mark all that can reach boundary.
//			In another pass, we can find out who else cannot reach.
//
//			Can be done easily using BFS with an initial set of cells connected to boundary.

typedef vector<vector<char>> Grid;

struct Coordinate {
	int x,y;
};

bool IsValid(const Coordinate& curr, const Grid& grid)
{
	return curr.x >=0 && curr.x < (int)grid.size() &&
			curr.y >=0 && curr.y < (int)grid[curr.x].size() &&
			grid[curr.x][curr.y] == 'W';
}

void FillSurroundedRegion(Grid* board_ptr)
{
	Grid& board = *board_ptr;
	int lastRow = (int)board.size()-1;
	int lastCol = (int)board[0].size() - 1;
	queue<Coordinate> Q;
	vector<vector<int>> dir = {{0,1}, {1,0}, {0,-1}, {-1,0}};

	// Put all the border elements in the queue to get the initial set.
	for(int i=0; i<(int)board.size() ; ++i) {
		// Look first and last column
		if(board[i][0] == 'W') {
			Q.emplace(Coordinate{i,0});
		}
		if(board[i][lastCol] == 'W') {
			Q.emplace(Coordinate{i, lastCol});
		}
	}
	for(int i=1; i<lastCol ; ++i) {
		// Look first and last row. But skip the corner cells, as they are already counted.
		if(board[0][i] == 'W') {
			Q.emplace(Coordinate{0,i});
		}
		if(board[lastRow][i] == 'W') {
			Q.emplace(Coordinate{lastRow, i});
		}
	}

	while (!Q.empty()) {
		Coordinate curr = Q.front();
		Q.pop();

		board[curr.x][curr.y] = 'T';

		for(size_t i=0 ; i<dir.size() ; ++i) {
			Coordinate neighbor = {curr.x + dir[i][0], curr.y + dir[i][1]};
			if(IsValid(neighbor, board)) {
				Q.emplace(neighbor);
			}
		}
	}

	// Now only mark the 'T' with 'W' and 'W' with 'B'
	for(size_t i=0 ; i<board.size() ; ++i) {
		for(size_t j=0; j<board[i].size() ; ++j) {
			board[i][j] = (board[i][j] == 'T') ? 'W' : 'B';
		}
	}
}

void PrintGrid(const Grid& grid) {
	cout << "Grid: " << endl;
	for(const vector<char>& line: grid) {
		for(const char c: line) {
			cout << ((c == 'W') ? "W" : "B") << " ";
		}
		cout << endl;
	}
	cout << endl;
}


int main()
{
	char w='W', b='B';
	Grid board = {
			{b,b,b,b},
			{w,b,w,b},
			{b,w,w,b},
			{b,b,b,b}
	};

	PrintGrid(board);

	FillSurroundedRegion(&board);

	PrintGrid(board);
}
