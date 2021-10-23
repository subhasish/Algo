/*
 * HC.33.MaxRectangle.cpp
 *
 * Problem: The problem has application to image processing.
 * 			Let A be an n X m boolean 2D array.
 *
 * 			Design an algorithm for computing the largest 2D array subarray containing only 1s.
 *
 *  Created on: Jan 10, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

//Solution:
//			We solved this the problem traditionally in DP/HC.33.MaxRectangle.cpp.
//			This problem can also be solved using a very different approach, as we try here.
//			Essentially we reduce our problem to n instances of the largest rectangle under skyline
//			problem we did solve in 17.Invariants/08.MaxUnderSkyline.cpp
//
//			First for each A[i][j] we determine the largest h such that A[i,i-(h-1)] is feasible.
//			That is h will represent the height of the building at (i,j).
//			Then for each n rows, starting with top most row, we compute the largest 2D subarray
//			whose bottom edge is on that row in O(m) time.
//			Doing this for each of the n rows will take total time O(m * n).
//
//			Computing the h values will also take O(m * n) time. Also we can compute the h values
//			for a row when we perform operation on the row. We can use only O(m) memory for the
//			current row and update it from the old values of itself, that is values of previous row.
//
//			Details about the O(m) algorithm is that for each building in the array we try to see
//			how much left and right that building supports. That is the rectangle that has same
//			height as the building. For left, a stack of increasing height can represent the
//			building that still can support rectangle till current building. When current building
//			is of smaller height and we remove some other building of higher height, we actually
//			found the right side point of the other building that it supports. Each building goes
//			into the stack once and comes out of it once, so O(m).


bool IsSmallerThanTopOrReachedEnd(const vector<int>& heights, int current_index, int top_index);
int MaxRectangleUnderSkyline(const vector<int>& heights);

int MaxRectangle(const vector<vector<bool>>& A) {

	// Array of the heights up to current row, starting from top row
	vector<int> heights(A.front().size(), 0);

	int max_rect_area = 0;

	for(int i=0 ; i < (int)A.size() ; ++i) {
		for(int j=0 ; j < (int)A[i].size() ; ++j) {
			heights[j] = A[i][j] ? (i>0 ? heights[j]+1 : 1) : 0;
		}
		int current_max = MaxRectangleUnderSkyline(heights);
		max_rect_area = max(max_rect_area, current_max);
	}

	return max_rect_area;
}


int MaxRectangleUnderSkyline(const vector<int>& heights)
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

			max_rec_area = max(max_rec_area, height*width);
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




int main() {
	vector<vector<bool>> A =
	{
			{ false, false,  true,  true, false,  true, false, false},
			{  true,  true,  true,  true, false, false,  true,  true},
			{ false,  true,  true,  true,  true, false,  true,  true},
			{ false,  true,  true,  true, false,  true,  true,  true},
			{  true, false,  true,  true, false, false,  true, false},
			{ false, false, false,  true,  true,  true, false, false},
			{ false,  true, false, false,  true, false,  true, false},
			{  true,  true,  true, false,  true,  true, false,  true},
			{  true,  true, false, false, false, false,  true,  true},
	};

	cout << "Maximum rectangle has area = " << MaxRectangle(A) << endl;
}
