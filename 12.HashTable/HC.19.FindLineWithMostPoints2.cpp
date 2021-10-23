/*
 * HC.19.FindLineWithMostPoints.cpp
 *
 * Problem: You are given a set of points in the plane. Each point has an integer coordinate.
 * 			Design an algorithm for computing a line that contains the maximum number of points
 * 			in the set.
 *
 *  Created on: Dec 20, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			The last solution had O(n^2) space complexity.
//			I think it can be improved to O(n) by considering all the lines passing through a point
//			in one iteration. Track the maximum and if needed update. Then discard the whole map
//			of lines and start afresh.

struct Point {
	int x,y;

	// Equal function for hash
	bool operator== (const Point& that) const {
		return x == that.x && y == that.y;
	}
};

//Hash function for point. Needed for the unordered_set of points
struct HashPoint {
	size_t operator() (const Point& p) const {
		return hash<int>()(p.x) ^ hash<int>()(p.y);
	}
};

struct Rational {
	int numerator, denominator;

	bool operator== (const Rational& that) const {
		return numerator == that.numerator && denominator == that.denominator;
	}
};

int GCD(int, int);

Rational GetCanonicalForm(int a, int b) {
	int gcd = GCD(abs(a), abs(b));
	//**Note: be careful about computing GCD of negative numbers

	a /= gcd; b /= gcd;
	return (b<0) ? Rational{-a, -b} : Rational{a,b};
}

int GCD(int a, int b) {
	if(a<b) {
		return GCD(b, a);
	} else if(b == 0) {
		return a;
	} else if(b == 1) {
		return 1;
	} else if(a == b) {
		return a;
	} else {
		return GCD(b, a%b);
	}
}

struct Line {

	// slope is a rational number. Note that if the line is parallel to y-axis we store 1/0
	Rational slope;

	// intercept is a rational number for the y-intercept unless the line is parallel to
	// y-axis in which case it is x-intercept
	Rational intercept;

	// Line function of two points, a and b, and the equation is
	// y = x(b.y - a.y)/(b.x - a.x) + (b.x * a.y - a.x * b.y) / (b.x - a.x)
	Line(const Point& a, const Point& b) {
		slope = (a.x != b.x) ? GetCanonicalForm(b.y - a.y, b.x - a.x) : Rational {1, 0};
		intercept = (a.x != b.x) ? GetCanonicalForm(b.x * a.y - a.x * b.y, b.x - a.x) : Rational{a.x, 1};
	}

	// Equal function for line
	bool operator==(const Line& that) const {
		return slope == that.slope && intercept == that.intercept;
	}
};

// Hash function for Line. Needed for the map of lines.
struct HashLine {
	size_t operator() (const Line& l) const {
		return  hash<int>()(l.slope.numerator) ^
				hash<int>()(l.slope.denominator) ^
				hash<int>()(l.intercept.numerator) ^
				hash<int>()(l.intercept.numerator);
	}
};

Line FindLineWithMostPoints(const vector<Point>& P) {
	if(P.size() < 2) {
		throw invalid_argument("Not enough points for a line!!");
	}

	int max_count = 2;
	Line max_line(P[0],P[1]);

	for(int i=0 ; i<(int)P.size() ; ++i) {
		//Hash table for all possible Lines through point P[i], storing Points passing through them
		unordered_map<Line, unordered_set<Point, HashPoint>, HashLine> table;

		for(int j=0; j<(int)P.size() ; ++j) {
			if(i == j) continue;

			Line l(P[i], P[j]);
			table[l].emplace(P[i]);
			table[l].emplace(P[j]);
		}

		for(auto val: table) {
			if(static_cast<int>(val.second.size()) > max_count) {
				max_count = val.second.size();
				max_line = val.first;
			}
		}
	}

	return max_line;
}

int main() {
	vector<Point> P = {Point{1,1}, Point{3,1}, Point {1,3}, Point{2,2}, Point{5,2}, Point{2,7}, Point{6,6}, Point{-3,-3} };
	Line max_line = FindLineWithMostPoints(P);

	cout << "Line with maximum point has slope = " << max_line.slope.numerator << "/" << max_line.slope.denominator << endl;
	cout << "Line with maximum point has intercept = " << max_line.intercept.numerator << "/" << max_line.intercept.denominator << endl;
}
