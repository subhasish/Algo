/*
 * max-points-on-a-line.cpp
 *
 *  Created on: Feb 4, 2019
 *      Author: subha
 */

// It allows duplicate points and solution should count duplicate points accordingly
// That is the only difference between this one and 12.HashTable/HC.19.FindLineWithMostPoints2.cpp

#include <bits/stdc++.h>
using namespace std;


struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

int GCD(int a, int b) {
    if(a > b) {
        return GCD(b, a);
    }
    if(a == 0) {
        return b;
    } else {
        return GCD(b%a, a);
    }
}

struct Rational {
    int num, dem;

    bool operator== (const Rational& that) const {
        return num == that.num && dem == that.dem;
    }
};

Rational GetCanonical(int a, int b) { // get in mutually prime form
    int gcd = GCD(abs(a), abs(b));
    a /= gcd; b /= gcd;
    return (b < 0) ? Rational{-a, -b} : Rational{a,b};
}
struct MyPoint : public Point {
	MyPoint() : Point(0,0) {}
    MyPoint(int a, int b) : Point(a,b) {}
    MyPoint(Point a): Point(a.x, a.y) {}

    bool operator== (const MyPoint& that) const {
        return x == that.x && y == that.y;
    }
};

struct HashPoint {
    size_t operator() (const MyPoint& a) const {
        return hash<int>()(a.x) ^ hash<int>()(a.y);
    }
};

struct Line {
    Rational slope;
    Rational intercept;

    bool operator== (const Line& that) const {
        return slope == that.slope && intercept == that.intercept;
    }

    Line(const Point& a, const Point& b) {
    slope = (a.x != b.x) ? GetCanonical(b.y - a.y, b.x - a.x) : Rational {1, 0};
    intercept = (a.x != b.x) ? GetCanonical(b.x * a.y - a.x * b.y, b.x - a.x) : Rational{a.x, 1};
    }
};

struct HashLine {
    size_t operator() (const Line& l) const {
        return hash<int>()(l.slope.num) ^
            hash<int>()(l.slope.dem) ^
            hash<int>()(l.intercept.num) ^
            hash<int>()(l.intercept.dem);
    }
};
class Solution {


public:
    int maxPoints(vector<Point>& points) {
    	if(points.size() < 2) {
    		return points.size();
    	}
        vector<MyPoint> P(points.begin(), points.end());

        unordered_map<MyPoint, int, HashPoint> dup_count;
        for(size_t i=0; i<P.size() ; ++i) {
        	++dup_count[P[i]];
        }

        unordered_map<Line, vector<MyPoint>, HashLine> table;

        int max_size = 0;
        for(size_t i=0; i<P.size() ; ++i) {
        	int dc = dup_count[P[i]];
            int current_max = 0;
            for(size_t j=i+1 ; j<P.size() ; ++j) {
                if(P[i] == P[j]) {
                    continue;
                }
                Line l(P[i], P[j]);
                table[l].emplace_back(P[j]);
                current_max = max(current_max, (int)table[l].size());
            }
            max_size = max(max_size, current_max + dc);
            table.clear();
        }
        return max_size;
    }
};

int main() {
	Solution obj;
	vector<Point> A = {Point(1,1), Point(2,2), Point(5,5), Point(1,5) } ;
	cout << obj.maxPoints(A) << endl;
}

