/*
 * 06.MergeIntervals.cpp
 *
 * Problem: Write a program that takes as input an array of disjoint closed intervals sorted by increasing order of left endpoint,
 * 			and an interval to be added, and returns the union of the intervals as disjoint and sorted.
 *
 *  Created on: Mar 10, 2018
 *      Author: subha
 */


#include <bits/stdc++.h>

using namespace std;

// Solution: Go in order, first all intervals before the start the one overlapping and the all after the interval
//
//			 Check interesting way to check overlapping intervals

struct Interval
{
	int start, end;
};

typedef vector<Interval> VInt;

bool DoesOverlap(Interval& a, Interval& b)
{
	//return (a.start >= b.start && a.start <= b.end) || (a.end >= b.start && a.end <= b.end);

	// Another interesting way is to check start of both are less than end of both
	return (a.start <= b.end && b.start <= a.end);
}

VInt AddInterval(VInt& intervals, Interval& add)
{
	VInt result;

	size_t i=0;

	// Add all appearing before
	while(i < intervals.size() && intervals[i].end < add.start) {
		result.emplace_back(intervals[i]);
		++i;
	}

	// Add overlaps
	if(i < intervals.size() && DoesOverlap(intervals[i], add)) {
		Interval newone;
		newone.start = min(intervals[i].start, add.start);
		while(i < intervals.size() && intervals[i].start <= add.end) {
			newone.end = max(intervals[i].end, add.end);
			++i;
		}
		result.emplace_back(newone);
	} else {
		result.emplace_back(add);
	}

	// Add all appearing after
	while(i < intervals.size()) {
		result.emplace_back(intervals[i]);
		++i;
	}

	return result;
}


int main()
{
	VInt intervals = { {-4, -1}, {0,2}, {3,6}, {7,9}, {11,12}, {14,17} };
	Interval add = {1,8};

	VInt res = AddInterval(intervals, add);

	for(const Interval& intv: res) {
		cout << "[" << intv.start << ", " << intv.end << "], ";
	}
	cout << endl;
}
