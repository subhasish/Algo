/*
 * 05.PatternInGridUnique.cpp
 *
 * Problem: This is a variant of original problem of searching a pattern in a grid.
 * 			Here the pattern in the grid cannot use one cell multiple times.
 *
 * 			Tell us either how many such different instances of the pattern exists in the
 * 			grid, or just tell whether such pattern exists or not.
 *
 *  Created on: May 5, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Building on the original solution, that is building on the matching of the suffix of
//			the string. There we were only looking at the boolean solution in neighbor cells.
//
//			But here we need to know the whether the cells had earlier matched to any path of the
//			suffix as well, to detect the duplicate.
//			To do that we can store the paths matched instead of the boolean for each state.
//
//			When exploring next character we need to look the existing solutions for the neighbors.
//			If current position already exists in the path then we discard that solution, if not
//			then we add current position and add that to the solution.


typedef pair<int, int> Pos;
typedef vector<Pos> Path;
typedef vector<Path> PathList;

bool PathContains(const Path& path, const Pos& coor) {
	for(const Pos& p: path) {
		if(p.first == coor.first && p.second == coor.second) {
			return true;
		}
	}
	return false;
}

void CheckAndAddPathToPathList(PathList& pl, const Path& p, const Pos& c) {
	if(!PathContains(p, c)) {
		Path np = p;
		np.emplace_back(c);
		pl.emplace_back(np);
	}
}

Path ReversePath(const Path& p)
{
	Path pr(p.crbegin(),p.crend());
	return pr;
}

PathList EnumerateUniquePatternInGrid(const vector<vector<int>>& grid, const vector<int>& pattern)
{
	PathList DP[grid.size()][grid[0].size()][pattern.size()];

//	memset(DP, false, sizeof(DP));
//	cout << "Sizes: " << sizeof(DP[0][0][0]) << " " << sizeof(DP[0][0]) << " " << sizeof(DP[0]) << " " << sizeof(DP) << endl;


	// Base case: for last one char suffix
	int offset = pattern.size()-1;
	for(int x=0; x < (int) grid.size() ; ++x) {
		for(int y=0; y < (int) grid[0].size() ; ++y) {
			if(grid[x][y] == pattern[offset]) {
				DP[x][y][offset].emplace_back(Path{Pos{x,y}});
			} else {
				//DP[x][y][offset] = false;
			}
		}
	}


	// Recursive case: See if neighbors match the suffix after this character
	for(int offset = pattern.size()-2 ; offset>=0 ; --offset) {
		for(int x=0; x < (int) grid.size() ; ++x) {
			for(int y=0; y < (int) grid[0].size() ; ++y) {
				if(grid[x][y] == pattern[offset]) {
					if(x>0 && !DP[x-1][y][offset+1].empty())  {
						for(const Path& p: DP[x-1][y][offset+1]) {
							CheckAndAddPathToPathList(DP[x][y][offset], p, Pos{x,y});
						}
					}
					if (y>0 && !DP[x][y-1][offset+1].empty()) {
						for(const Path& p: DP[x][y-1][offset+1]) {
							CheckAndAddPathToPathList(DP[x][y][offset], p, Pos{x,y});
						}
					}
					if((x < (int)grid.size()-1) && !DP[x+1][y][offset+1].empty()) {
						for(const Path& p: DP[x+1][y][offset+1]) {
							CheckAndAddPathToPathList(DP[x][y][offset], p, Pos{x,y});
						}
					}
					if((y < (int)grid[0].size()-1) && !DP[x][y+1][offset+1].empty()) {
						for(const Path& p: DP[x][y+1][offset+1]) {
							CheckAndAddPathToPathList(DP[x][y][offset], p, Pos{x,y});
						}
					}
				} else {
					//DP[x][y][offset] = false;
				}
			}
		}
	}

	PathList result;
	// Final result: search if matched at any cell for offset 0
	for(int x=0; x < (int) grid.size() ; ++x) {
		for(int y=0; y < (int) grid[0].size() ; ++y) {
			if(!DP[x][y][0].empty()) {
				for(const Path& p: DP[x][y][0]) {
					result.emplace_back(ReversePath(p));
				}
			}
		}
	}
	return result;
}

void PrintPathList(const PathList& pl) {
	if(pl.empty()) {
		cout << "Path list is empty." << endl;
	} else {
		for(const Path& p: pl) {
			cout << "Path: ";
			for(const Pos& c: p) {
				cout << "(" << c.first << ", " << c.second << ")";
			}
			cout << endl;
		}
	}
	cout << endl;
}

int main()
{
	vector<vector<int>> grid =
	{
			{ 1, 2, 3, 2, 3, 5},
			{ 3, 5, 7, 9, 2, 7},
			{ 1, 3, 5, 7, 4, 3}
	};

	vector<int> pat1 = {3,7,5,3,5,7,4};
	vector<int> pat2 = {3,7,5,3,5,7,4,7};
	vector<int> pat3 = {3,7,5,3,5,8};
	vector<int> pat4 = {1};
	vector<int> pat5 = {3,5,7};


	PathList pl1 = EnumerateUniquePatternInGrid(grid, pat1);
	PathList pl2 = EnumerateUniquePatternInGrid(grid, pat2);
	PathList pl3 = EnumerateUniquePatternInGrid(grid, pat3);
	PathList pl4 = EnumerateUniquePatternInGrid(grid, pat4);
	PathList pl5 = EnumerateUniquePatternInGrid(grid, pat5);

	PrintPathList(pl1);
	PrintPathList(pl2);
	PrintPathList(pl3);
	PrintPathList(pl4);
	PrintPathList(pl5);
}
