/*
 * HC.35.TrappingWater.cpp
 *
 * Problem: The goal of the problem is to compute the capacity of a type of one-dimensional container.
 * 			The one dimensional container id specified by an array of n non-negative integers, specifying
 * 			height of each unit width rectangle.
 *
 * 			Design an algorithm to compute the capacity of the container.
 *
 *  Created on: Jan 12, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * Solution:
 * 			We can get great insight by visualizing/drawing few examples of water filled container.
 * 			After water is filled the structure looks like some increasing bars (if any) followed by
 * 			some decreasing bars (if any).
 *
 * 			One idea to find the water capacity is to find the total volume of the whole structure
 * 			with water and then subtract the actual volume of the buildings.
 *
 * 			To find the total overall volume we will keep track of the increasing blocks; like we do
 * 			in stack. But for decreasing part we can remove all the blocks from the top of the
 * 			stack which are smaller than the current block.
 * 			We can keep a marker of the highest block so far in the stack, so that we do not remove
 * 			any block past it. So that we do not remove blocks that constitute the increasing part.
 *
 * 			This implementing counters so much corner cases as the computation for the decreasing
 * 			part is not as elegant as increasing part.
 *
 * 			One way to simplify the implementation is to apply the same logic for increasing and
 * 			decreasing part in reverse order. The observation that makes this easy that increasing
 * 			and decreasing parts happen around the max element.
 *
 * 			If we apply logic in parts then we can only note the difference between the current value
 * 			and running maximum and that is the volume of water. That is because there is maximum
 * 			on the other side that will hold water in between them. So we only need to consider
 * 			other side which is running maximum.
 *
 * NOTE: 	For increasing and decreasing parts. Use same logic and use iterators to reuse the logic.
 *
 * C++:
 * 			const_iterator
 * 			const_reverse_iterator
 */


template<typename Iter>
int TrappingWaterTillEnd(Iter begin, Iter end);

int TrappingWater(const vector<int>& heights) {

	//Find maximum index
	size_t max_index = 0;

	for(size_t i = 0 ; i < heights.size() ; ++i) {
		if(heights[i]> heights[max_index]) {
			max_index = i;
		}
	}

	int first_part_water = TrappingWaterTillEnd(heights.begin(), heights.begin() + max_index);
	int last_part_water  = TrappingWaterTillEnd(heights.rbegin(), heights.rbegin() + (heights.size() - 1 - max_index));

	return first_part_water + last_part_water;
}

template<typename Iter>
int TrappingWaterTillEnd(Iter begin, Iter end) {
	int sum = 0, running_max = 0;
	for(Iter it = begin ; it != end ; ++it) {
		if(*it > running_max) {
			running_max = *it;
		} else {
			sum += (running_max - *it);
		}
	}
	return sum;
}

int main() {
	vector<int> heights = {1, 2, 1, 3, 4, 4, 5, 1, 2, 0, 3};
	cout << TrappingWater(heights) << endl;
}
