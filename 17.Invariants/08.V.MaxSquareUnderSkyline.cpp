/*
 * 08.V.MaxSquareUnderSkyline.cpp
 *
 * Problem: You are given an array of heights of adjacent buildings of unit width.
 * 			Design an algorithm to compute the area of the largest square contained
 * 			in this skyline.
 *
 * 			This is a variant of the problem 08.MaxUnderSkyline.cpp
 *
 *  Created on: Jun 3, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			We have solve the problem for largest rectangle in 08.MaxUnderSkyline.cpp.
//			For square, the same logic can be utilized.
//
//			When we have found the height and width supported by the current building,
//			we will take the minimum of the two as side of the square.

bool IsSmallerThanTopOrReachedEnd(const vector<int>& heights, int current_index, int top_index);

int MaxSquareUnderSkyline(const vector<int>& heights)
{
	stack<int> active;
	int max_rec_area = 0;

	for(int i=0 ; i <= (int) heights.size() ; ++i) // Run until heights.size() to remove last
	{
		// Remove until we see smaller or reached end
		while(!active.empty() && IsSmallerThanTopOrReachedEnd(heights, i, active.top()))
		{
			int height = heights[active.top()];
			active.pop();

			// Width is NOT from [old top, right]. Old top was the building position and not
			// the left end of the range. Left end is the current top after pop.
			int width = active.empty() ? i : i - active.top() -1;
			int side = min(height, width);

			max_rec_area = max(max_rec_area, side * side);
		}

		// Place the current one on top
		active.emplace(i);
	}

	return max_rec_area;
}

bool IsSmallerThanTopOrReachedEnd(const vector<int>& heights, int current_index, int top_index) {
	return (current_index < (int) heights.size()) ?
			(heights[current_index] <= heights[top_index]) :
			true;
}

int main()
{
	vector<int> heights= {1, 4, 2, 5, 6, 3, 2, 6, 6, 5, 2, 1, 3};

	cout << MaxSquareUnderSkyline(heights) << endl;
}
