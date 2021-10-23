/*
 * 02.FlipRegionColor.cpp
 *
 * Problem: Implement a routine that takes an n X m Boolean array with an entry (x,y) and
 * 			flips the color of the region associated with (x,y)
 *
 *  Created on: Jun 23, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Explore the connected region by BFS or DFS and flip color in the process. Try BFS here.

enum class Color { WHITE, BLACK };

struct Coordinate {
	int x,y;

	bool operator== (const Coordinate& that) const {
		return x == that.x && y == that.y;
	}
};

typedef vector<Coordinate> VC;
typedef vector<vector<Color>> Grid;

bool IsValid(const Coordinate& curr, const Grid& grid, Color matchColor)
{
	return curr.x >=0 && curr.x < (int)grid.size() &&
				curr.y >=0 && curr.y < (int)grid[curr.x].size() &&
				grid[curr.x][curr.y] == matchColor;
}

void FlipColor(int x, int y, Grid& grid)
{
	vector<vector<int>> dir = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	Color clr = grid[x][y];
	Color newColor = (clr == Color::WHITE) ? Color::BLACK : Color::WHITE;

	queue<Coordinate> Q;
	Q.emplace(Coordinate{x,y});

	while(!Q.empty()) {
		Coordinate curr = Q.front();  // NOTE: front() and not top()
		Q.pop();
		grid[curr.x][curr.y] = newColor;

		for(size_t i=0 ; i<dir.size() ; ++i) {
			Coordinate neighbor = {curr.x + dir[i][0], curr.y + dir[i][1]};
			if(IsValid(neighbor, grid, clr)) {
				Q.emplace(neighbor);
			}
		}
	}
}

void PrintGrid(const Grid& grid) {
	cout << "Grid: " << endl;
	for(const vector<Color>& line: grid) {
		for(const Color c: line) {
			cout << ((c == Color::WHITE) ? "W" : "B") << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	Color w = Color::WHITE, b = Color::BLACK;

	Grid grid = {
			{b,w,b,w,w,w,b,b,b,b},
			{w,w,b,w,w,b,w,w,b,b},
			{b,b,b,w,w,b,b,w,b,b},
			{w,b,w,b,b,b,b,w,b,w},
			{b,w,b,w,w,w,w,b,w,w},
			{b,w,b,w,w,b,w,b,b,b},
			{w,w,w,w,b,w,b,w,w,b},
			{b,w,b,w,b,w,b,w,w,w},
			{b,w,b,b,w,w,w,b,b,b},
			{w,w,w,w,w,w,w,b,b,w}
	};

	PrintGrid(grid);

	FlipColor(5,4,grid);

	PrintGrid(grid);
}
