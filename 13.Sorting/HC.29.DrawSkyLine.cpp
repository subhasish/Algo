/*
 * HC.29.DrawSkyLine.cpp
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
//			Representation of the skyline can be array of pairs consisting <point_i, height_i>, where
//			it represents the fact that height of the skyline between point i and (i+1) is height_i.
//
//			While merging two skylines if we consider only the current running maximum height then
//			we will be wrong. Because, when current maximum ends, there can be another building hidden,
//			that should be visible instead of next building from current skyline.
//			But here we only need to track two running heights.
//
//			But one observation is that only change of heights will take place in one of the original
//			point of changes. So at each point of change if we compare the two running heights and take
//			their maximum then we get final merged skyline.
//			This may have duplicates and repetitions, but can be merged consecutive ranges.
//
//			This way instead of handling all the active points, we are handling two at a time and
//			keep merging, like merge sort.


struct Rectangle {
	int left, right, height;
};

struct PointHeight {
	int point, height;
};

typedef vector<PointHeight> Skyline;

void ComputeSkylineHelper(const vector<Rectangle>& buildings, size_t start, size_t end, Skyline& result);
void MergeSkylines(Skyline& result1, Skyline& result2, Skyline& final_result);

Skyline ComputeSkyline(const vector<Rectangle>& buildings) {
	Skyline result;
	ComputeSkylineHelper(buildings, 0, buildings.size()-1, result);
	return result;
}

void ComputeSkylineHelper(const vector<Rectangle>& buildings, size_t start, size_t end, Skyline& result) {
	if(start > end) {
		return;
	}
	if(start == end) {
		result.emplace_back(PointHeight{buildings[start].left, buildings[start].height});
		result.emplace_back(PointHeight{buildings[start].right, 0});
		return;
	}

	Skyline result1, result2;
	size_t mid = start + (end - start)/2;
	ComputeSkylineHelper(buildings, start, mid, result1);
	ComputeSkylineHelper(buildings, mid+1, end, result2);
	MergeSkylines(result1, result2, result);
}

void MergeSkylines(Skyline& result1, Skyline& result2, Skyline& final_result) {
	size_t left_idx = 0, right_idx = 0;
	int left_height = 0, right_height = 0;
	int current_point = 0;

	while(left_idx < result1.size() && right_idx < result2.size()) {
		if(result1[left_idx].point <= result2[right_idx].point) {
			left_height = result1[left_idx].height;
			current_point = result1[left_idx].point;
			++left_idx;
		} else {
			right_height = result2[right_idx].height;
			current_point = result2[right_idx].point;
			++right_idx;
		}
		final_result.emplace_back(PointHeight{current_point, max(left_height, right_height)});
	}

	// Put rest back
	while(left_idx < result1.size()) {
		final_result.emplace_back(result1[left_idx++]);
	}
	while(right_idx < result2.size()) {
		final_result.emplace_back(result2[right_idx++]);
	}
}

int main() {
	vector<Rectangle> buildings = {
			Rectangle{0, 3, 1},
			Rectangle{1, 6, 3},
			Rectangle{4, 8, 4},
			Rectangle{5, 9, 2},
			Rectangle{11, 17, 1},
			Rectangle{10, 12, 6},
			Rectangle{7, 14, 3},
			Rectangle{13, 16, 2},
	};

	Skyline skyline = ComputeSkyline(buildings);

	for(size_t i=0; i< skyline.size()-1 ; ++i) {
		cout << "[" << skyline[i].point << "," << skyline[i+1].point << "] -> " << skyline[i].height << endl;
	}
	size_t sz = skyline.size();
	cout << "[" << skyline[sz-2].point << "," << skyline[sz-1].point << "] -> " << skyline[sz-2].height << endl;
}
