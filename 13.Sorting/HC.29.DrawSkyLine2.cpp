/*
 * HC.29.DrawSkyLine2.cpp
 *
 * Problem: You are given a set of buildings, specified by its left, right coordinates, and height.
 * 			Skyline is the list of coordinates and corresponding height of what is visible.
 *
 * 			Design an efficient algorithm for computing the skyline.
 *
 *  Created on: Dec 30, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

//Solution:
//			Sounds very similar to the "view from above" problem. Skyline can change only at edges.
//			We can maintain a BST of all active buildings and fetch maximum height and define
//			skyline. This O(n log n) but complex implementation.
//			Refer to 14.BST/HC.25.ViewFromAbove.cpp
//
//			Another observation is that given a skyline, we can add a new building in O(n) time to
//			update the existing solution. To add it we just iterate the existing skyline from
//			left to right and update any height if needed. This is O(n^2).
//
//			The key to improving efficiency is the observation is that it takes linear time to merge
//			two skylines (if presented left to right order), which is same as the time to merge a
//			single skyline, but gets much more done.
//
//			So it can be treated similarly as merge sort or counting inversion to be solved by
//			divide-and-conquer algorithm. We can compute skylines for two halves of the input and then
//			merge them. This is O(n log n).
//
// Another approach:
//			Another alternative approach is to "digitize" the problem. Represent the skyline with an
//			array where the ith element of the array hold the height of the ith coordinate of the
//			skyline. Initialize this array with 0s. Then for each building update all the coordinates
//			falling in the range of that building. This has time complexity O(nW) where W is the
//			width of the widest building. If in practice, W is constant then is solution is much faster.
//
//			Define height[i] is the height between coordinate i and i+1.
//
// Key to correct solution:
//			Define height[i] to be the height of the skyline between coordinate and i and (i+1).
//			Then do not consider height of the end coordinate of a building.
//			Also at the coordinate where a rectangle of skyline ends, other rectangle should
//			begin from the same coordinate.

struct Rectangle {
	int left, right, height;
};

typedef vector<Rectangle> Skyline;

Skyline ComputeSkyline(const vector<Rectangle>& buildings) {
	int min_left = numeric_limits<int>::max();
	int max_right = numeric_limits<int>::min();

	for(const Rectangle& r: buildings) {
		min_left = min(min_left, r.left);
		max_right = max(max_right, r.right);
	}

	vector<int> heights(max_right - min_left + 1, 0);	// height[i] is the height between coordinate
														// i and i+1

	for(const Rectangle& r: buildings) {				// update the heights array using all buildings
		for(int i=r.left ; i< r.right ; ++i) {			// Do NOT update height at r.right, as building
														// is not present at (r.right + 1)
			heights[i-min_left] = max(r.height, heights[i-min_left]);
		}
	}

	Skyline result;
	int left = 0;	// maintain start of the current segment
	for(int i=1 ; i< (int)heights.size() ; ++i) {		// compute skyline from heights array
		if(heights[i] != heights [i-1]) {				// left to i is a segment, and another
														// starts at i
			result.emplace_back(Rectangle{left + min_left, i + min_left, heights[i-1]});
			left = i;
		}
	}

	result.emplace_back(Rectangle{left + min_left, max_right, heights.back()});
	return result;
}

int main() {
	vector<Rectangle> buildings = {
			Rectangle{0, 3, 1},
			Rectangle{1, 6, 3},
			Rectangle{4, 8, 4},
			Rectangle{5, 9, 2},
			Rectangle{11, 17, 1},
			Rectangle{9, 12, 6},
			Rectangle{7, 14, 3},
			Rectangle{13, 16, 2},
	};

	Skyline skyline = ComputeSkyline(buildings);

	for(const Rectangle& b: skyline) {
		cout << "[" << b.left << "," << b.right << "] -> " << b.height << endl;
	}
}
