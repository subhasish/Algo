/*
 * 05.MaxSimultaneousEvents.cpp
 *
 * Problem: Write a program that takes a set of events and determine the maximum number of events that take place concurrently.
 *
 *  Created on: Mar 10, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Comparing each interval with all other is O(n^2) and it does not take advantage of locality
//
//			We can improve running time by sorting end points. It does not matter which start point belongs to which end point.
//			So we we can mark each point whether it is start or end. And then we can iterate them in ascending order.
//			When encountering start point we will increase the count and decrease the count for an end point.
//
//			We will have to be careful about points where a interval starts and another ends. If we want to count that as overlap then
//			while sorting we would put the start point before the end point.
//
// C++:
//			Strongly typed enumerations: enum class T { A, B, C};
//			Structure initialization: T(a,b) will require a constructor but not T{a,b}

enum class EndType { START, END };
// Not:  enum EndType { START, END };
// Not:  typedef enum { START, END } EndType;

struct Event {
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

int MaximumSimultaneousEvents(vector<Event>& events)
{
	vector<EndPoint> points;
	for(const Event& e: events) {
		// Writing with () will require constructor but not with {}. Ex: points.emplace_back(EndPoint(e.start, EndType::START));
		points.emplace_back(EndPoint{e.start, EndType::START});
		points.emplace_back(EndPoint{e.end, EndType::END});
	}

	sort(points.begin(), points.end());

	int current_count = 0;
	int max_count = 0;
	for(const EndPoint& p: points) {
		if(p.type == EndType::START) {
			++current_count;
			if(max_count < current_count) {
				max_count = current_count;
			}
		} else {
			--current_count;
		}
	}

	return max_count;
}

int main()
{
	vector<Event> events = { {1,5}, {2,7}, {4,5}, {6,10}, {8,9}, {9,17}, {11,13}, {12,15}, {14,15} };

	cout << "Maximum overlapping is: " << MaximumSimultaneousEvents(events) << endl;
}
