/*
 * 01.FindPath.cpp
 *
 * Problem: Given a search maze with black cell meaning blocked and white meaning open and a
 * 			start and end, find path from start to end if possible.
 *
 *  Created on: Jun 23, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			DFS or BFS. Lets do DFS here.
//			Time complexity is also same as DFS O(|V|+|E|)

enum class Color {WHITE, BLACK};

struct Coordinate {
	int x,y;

	bool operator== (const Coordinate& that) const {
		return x == that.x && y == that.y;
	}
};

typedef vector<Coordinate> VC;
typedef vector<vector<Color>> Grid;

bool IsFeasible(const Coordinate& curr, const Grid& maze)
{
	return curr.x >=0 && curr.x < (int)maze.size() &&
			curr.y >=0 && curr.y < (int)maze[curr.x].size() &&
			maze[curr.x][curr.y] == Color::WHITE;
}

bool FindPathDFS(const Coordinate& curr, const Coordinate& end, Grid* maze_ptr, VC* path_ptr)
{
	Grid& maze = *maze_ptr;
	if(!IsFeasible(curr, maze)) {
		return false;
	}

	path_ptr->emplace_back(curr);			// push in current path
	maze[curr.x][curr.y] = Color::BLACK;	// mark visited

	if(curr == end) {
		return true;
	}

	// Explore all directions
	const vector<vector<int>> dir = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	for(size_t i=0; i<dir.size() ; ++i) {
		if(FindPathDFS({curr.x + dir[i][0], curr.y + dir[i][1]}, end, maze_ptr, path_ptr)) {
			return true;
		}
	}

	path_ptr->pop_back();
	return false;
}


// This is not guaranteed to find the shortest path
VC FindPath(Grid& maze, const Coordinate& start, const Coordinate& end)
{
	VC path;
	FindPathDFS(start, end, &maze, &path);
	return path;
}

void PrintPath(const VC& path) {
	for(const Coordinate& c: path) {
		cout << "(" << c.x << ", " << c.y << ")" << endl;
	}
}

int main()
{
	Grid maze = Grid(6, vector<Color>(5, Color::WHITE));
	maze[3][0] = Color::BLACK;
	maze[4][0] = Color::BLACK;
	maze[1][1] = Color::BLACK;
	maze[1][2] = Color::BLACK;
	maze[1][3] = Color::BLACK;
	maze[1][4] = Color::BLACK;

	VC path = FindPath(maze, {5,0}, {0,4});

	PrintPath(path);
}
