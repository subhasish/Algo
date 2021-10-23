/*
 * 03.MinIntervalCover.cpp
 *
 * Problem: We are given a number of closed intervals of times. We are to find the minimum number
 * 			instants such that those cover all the intervals.
 *
 *  Created on: May 20, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Note that one instant has to appear before first interval finishes, to cover that one.
//			So the first instant has be on that end point. Now if we remove all intervals that
//			got covered and apply the same algorithm again we will be getting the optimal result.
//
//			Smart way to do this without actually removing intervals is following:
//			Sort the intervals based on right end points. Select the first right end point.
//			Iterate through the intervals, looking for the first interval not covered by this
//			right end point. As soon as such interval is found that would be the next instant
//			to select. Continue like this.

typedef vector<int> VI;
typedef pair<int, int> Interval;

VI MinimumIntervalCover(vector<Interval> intervals)
{
	// Sort based on finish time
	sort(intervals.begin(), intervals.end(),
			[](const Interval& a, const Interval& b) {return a.second < b.second; });

	VI result;
	int last = numeric_limits<int>::min();

	for(const Interval& i: intervals) {
		if(i.first > last) {
			// Last instant do not cover this interval. As they are in order of the finish time
			// finish time of this interval should go in.

			result.emplace_back(i.second);
			last = i.second;
		}
	}

	return result;
}

int main()
{
	VI res = MinimumIntervalCover({Interval{1,2}, Interval{2,3}, Interval{3,4}, Interval{4,5}});
	cout << res.size() << endl;
}
