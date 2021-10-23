/*
 * 07.UnionOfIntervals.cpp
 *
 * Problem: Design an algorithm that takes a set of intervals as input and returns their unions as set of disjoint intervals
 *
 *  Created on: Mar 10, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Applying same kind of logic we did for finding maximum simultaneous events.
//			We can think of it as matching braces problem.
//			When there is no overlap then number of current open interval will be 0.

enum class EndType { START, END };
// Not:  enum EndType { START, END };
// Not:  typedef enum { START, END } EndType;

struct Interval {
	int start, end;
};

struct EndPoint {
	int point;
	EndType type;

	//EndPoint(int p, EndType t) : point(p), type(t) {}

	bool operator< (const EndPoint& that) const
	{
		return (point == that.point) ? ((type == EndType::START && that.type == EndType::END)) : (point < that.point);
	}
};

typedef vector<Interval> VInt;

VInt UnionOfIntervals(VInt& intervals)
{
	VInt result;
	vector<EndPoint> points;
	for(const Interval& e: intervals)
	{
		// Writing with () will require constructor but not with {}. Ex: points.emplace_back(EndPoint(e.start, EndType::START));
		points.emplace_back(EndPoint{e.start, EndType::START});
		points.emplace_back(EndPoint{e.end, EndType::END});
	}

	sort(points.begin(), points.end());


	int current_count = 0;
	int current_start;
	for(size_t i=0 ; i < points.size() ; ++i)
	{
		// If count == 0 at the start we start a new interval
		if(current_count == 0 && points[i].type == EndType::START) {
			current_start = points[i].point;
		}

		if(points[i].type == EndType::START) {
			++current_count;
		} else {
			--current_count;
		}

		// If count == 0 at the end then end the existing interval
		if(current_count == 0 && points[i].type == EndType::END) {
			result.emplace_back(Interval{current_start, points[i].point});
		}
	}

	return result;
}


int main()
{
	VInt intervals = { {0,3}, {1,1}, {2,4}, {3,4}, {5,7}, {7,8}, {8,11}, {9,11}, {12,14}, {12,16}, {13,15}, {16,17}, };
	VInt res = UnionOfIntervals(intervals);

	for(const Interval& intv: res) {
		cout << "[" << intv.start << ", " << intv.end << "], ";
	}
	cout << endl;
}
