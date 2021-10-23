/*
 * HC.25.ViewFromAbove.cpp
 *
 * Problem: You are given a set of line segments. Each segment consists of a closed interval of the
 * 			x-axis, a color, and a height. When viewed from above the color of point x is the
 * 			color of the highest segment that include point x.
 *
 * 			Write a program that takes line segment as input and output the view from above for these'
 * 			segments. You can assume no two segments whose intervals overlap has same height.
 *
 *  Created on: Dec 25, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Key observation is that color can change when something gets added to or removed from top.
//			At least to discretize the problem we only need to consider endpoints.
//
//			At certain point only need to consider the segments that overlap with the points. So we
//			can try to maintain a collection of such overlapping segments.
//			We can keep that collection sorted by height so that we can get the color efficiently.
//
//			Specifically, we scan the endpoints, maintaining a set of line segments that intersect with
//			current end point. The set is stored in a BST with height as key. When we encounter a left
//			endpoint we add it to the BST and when encounter a right endpoint we remove the corresponding
//			segment.
//
//			For removal we need to find the segment in BST efficiently, so we can use a map from
//			endpoint to BST.
//
//			***Another way is to use the fact that there cannot be two segments overlapping at same height.
//			So the set of overlapping segments can use height as the key.***
//			If there can be duplicates, like building skyline, use a struct with height and id. Id can
//			used to break the tie in case height is same. See other programs for similar example.
//
//			While encountering endpoints, we need to keep track of previous segment. For a new endpoint
//			besides adding it to the active set of segments, we may need to either extend previous top
//			segment or terminate previous segment and start new segment.
//
//			The change needs to happen if previous height and color is different than current top's
//			height and color.
// 			Handle new endpoint. Cases are:
//				1. Left endpoint: See if it is higher than the current max. If yes, end previous segment.
//								  and start a new one.
//				2. Right endpoint: See if it were the max, if yes end the previous segment and
//								   start a new one.
//
//
// Complexity:
//			Sorting is O(n log n). Assuming library implementation of BST is height balanced, the insertion
//			and deletion is O(log n) for each point. So overall O(n log n).

struct LineSegment {
	int left, right;
	int color;
	int height;
};

struct EndPoint {
	const LineSegment* line;
	bool isLeft;

	int Value() const { return isLeft ? line->left : line->right; }

	// operator< needed to sort the endpoints in increasing order
	bool operator< (const EndPoint& that) const {
		if(Value() == that.Value()) {	// consider the ending point first, in case of tie
			return !isLeft;
		} else {
			return (Value() < that.Value());
		}
	}
};

typedef vector<LineSegment> VLS;

VLS CalculateViewFromAbove(const VLS& A) {
	vector<EndPoint> sorted_endpoints;
	for(const LineSegment& l: A) {
		sorted_endpoints.emplace_back(EndPoint{&l, true});
		sorted_endpoints.emplace_back(EndPoint{&l, false});
	}
	sort(sorted_endpoints.begin(), sorted_endpoints.end());

	VLS results;
	map<int, const LineSegment*> active_line_segments;		// map of height -> line segment for active segments

	EndPoint first = sorted_endpoints.front();
	active_line_segments.emplace(first.line->height, first.line);	//initialize with first point to ease computation
	int prev_position = first.Value(); 				// previous end point, from which current line needs to be drawn


	for(size_t i=1 ; i<sorted_endpoints.size() ; ++i) {
		EndPoint& p = sorted_endpoints[i];

		// Handle new endpoint. Cases are:
		//		1. Left endpoint: See if it is higher than the current max. If yes, end previous segment.
		//						  and start a new one.
		//		2. Right endpoint: See if it were the max, if yes end the previous segment and
		//						  start a new one.

		const LineSegment* top = active_line_segments.rbegin()->second;

		if(p.isLeft) {

			if(p.line->height > top->height) {
				results.emplace_back(LineSegment{prev_position, p.Value(), top->color, top->height});
				prev_position = p.Value();
			}

			active_line_segments.emplace(p.line->height, p.line);
		} else {
			if(p.line->height == top->height) {
				results.emplace_back(LineSegment{prev_position, p.Value(), top->color, top->height});
				prev_position = p.Value();
			}
			active_line_segments.erase(p.line->height);
		}
	}

	return results;
}

int main() {
	LineSegment a = LineSegment{0,4,1,1};
	LineSegment b = LineSegment{1,3,2,3};
	LineSegment c = LineSegment{2,7,3,2};
	LineSegment d = LineSegment{4,5,4,4};
	LineSegment e = LineSegment{5,7,5,1};
	LineSegment f = LineSegment{6,10,6,3};
	LineSegment g = LineSegment{8,9,7,2};
	LineSegment h = LineSegment{9,18,8,1};
	LineSegment i = LineSegment{11,13,9,3};
	LineSegment j = LineSegment{12,15,10,2};
	LineSegment k = LineSegment{14,15,11,3};
	LineSegment l = LineSegment{16,17,12,3};

	VLS arr = {a, b, c, d, e, f, g, h, i, j, k, l};
	VLS res = CalculateViewFromAbove(arr);

	for(const LineSegment& l: res) {
		cout << "[" << l.left << "," << l.right << ": "<< l.color <<"]" << endl;
	}

}
