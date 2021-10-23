/*
 * 08.MaxUnderSkyline.cpp
 *
 * Problem: You are given an array of heights of adjacent buildings of unit width.
 * 			Design an algorithm to compute the area of the largest rectangle contained
 * 			in this skyline.
 *
 *  Created on: Jun 3, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			One approach is to consider each pair and find the minimum in that range and compute
//			rectangle that spans across.
//
//			Another approach is for each building see both left and right and try to grow the
//			rectangle supported by the current building.
//
//			For seeing how much a building can grow in left, we can see that we need to only
//			find the building that has less height than the height of the current one.
//			So if we keep track of the heights in increasing order then it would be easier to
//			find. It is similar to maintaining maximum/minimum in a stack problem.
//
//			So as we advance through the buildings, all we are keeping track of buildings that
//			are not blocked yet. So it would be increasing sequence.
//
//			To maintain the increasing sequence, if new element is larger than top then we can
//			readily add it. If new element is smaller then we can pop as long as it is not larger
//			than top. We can pop equals as well.
//
//			Another main thing to note that whenever a building is removed from the sequence,
//			we know exactly how far to the right the largest rectangle it supports goes to!!
//
// Time complexity:
//			Each building enter the increasing exactly once and gets removed once. O(n)!!!

bool IsSmallerThanTopOrReachedEnd(const vector<int>& heights, int current_index, int top_index);

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

int main()
{
	vector<int> heights= {1, 4, 2, 5, 6, 3, 2, 6, 6, 5, 2, 1, 3};

	cout << MaxRectangleUnderSkyline(heights) << endl;
}
