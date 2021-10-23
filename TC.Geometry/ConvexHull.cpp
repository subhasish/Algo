/*
 * ConvexHull.cpp
 *
 *  Created on: Jul 29, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

const double PI = 3.14159265;

struct MyPoint
{ double x, y; };

typedef vector<MyPoint> vmp;

struct Vector
{ double a,b; };

double Dot(Vector A, Vector B)
{
	return A.a * B.a + A.b * B.b;
}

double Cross(Vector A, Vector B)
{
	return A.a * B.b - A.b * B.a;
}

double Distance(MyPoint a, MyPoint b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

// Returns the angle a vector makes with x axis.
// RESTRICTION: The vector has to be in the first two quadrants.
//              This works for our case as our origin is the bottom most point.
double Angle(Vector ab)
{
	if(ab.b == 0 && ab.a >= 0)
		return 0;
	if(ab.b == 0 && ab.a < 0)
		return 180;

	//Inverse tangent does not work!!! After 90 it again starts from -infinity
	//if(ab.a == 0) return 90;
	//double slope = (ab.b / ab.a);
	//double radian = atan(slope);

	//So, instead of tan we will use cos which is a monotonic function in [0,180]
	//We know A.B=|A|*|B|*Cos(angle), so we can find cos of angle as follows:
	//Taking dot product with x-axis vector (1,0)
	double dot = Dot(ab,{1,0});
	double cosAb = dot / (Distance({ab.a, ab.b}, {0,0}) * 1.0);
	double radian = acos(cosAb);
	return radian * 180 / PI;
}

Vector CreateVector(MyPoint a, MyPoint b)
{
	return {b.x-a.x, b.y-a.y};
}

MyPoint origin = {0,0};

// Returns true if point a makes less angle with origin
//         false otherwise
bool LessByAngle(MyPoint a, MyPoint b)
{
	double aAngle,bAngle;

	//Angle of a point with another point is same as the angle of the
	//vector made by the two points
	aAngle = Angle(CreateVector(origin,a));
	bAngle = Angle(CreateVector(origin,b));

	if(aAngle < bAngle) {
		return true;
	} else if (aAngle == bAngle) {
		// If angles are same them take consider distance from the origin
		if(Distance(origin,a) < Distance(origin,b)) {
			return true;
		}
	}

	return false;
}

// Sorts points in pList based on their angles with point start
vmp SortByAngle(vmp pList, MyPoint start)
{
	origin = start;

	// Uses c++ STL sort from <algorithms>
	sort(pList.begin(), pList.end(), LessByAngle);

	return pList;
}

// Finds bottom most point and for tie picks the left most among them
MyPoint FindLeftBottomMost(vmp pList)
{
	MyPoint res = pList[0];

	for(unsigned int i=1; i<pList.size() ; i++)
	{
		if(pList[i].y < res.y) {
			res = pList[i];
		} else if (pList[i].y == res.y) {
			if(pList[i].x < res.x) {
				res = pList[i];
			}
		}
	}

	return res;
}

void PrintPoint(MyPoint p)
{
	cout << "(" << p.x << ", " << p.y << ")" << endl;
}

void PrintPoints(vmp pList)
{
	for(unsigned int i=0; i<pList.size() ; i++)
	{
		PrintPoint(pList[i]);
	}
}


vmp ConvexHull(vmp pList)
{
	MyPoint start;
	unsigned int last;
	vmp hull;

	// Find the bottom most point. For tie take the left most one
	start = FindLeftBottomMost(pList);

	// Sort all other points based on the angle that makes with bottom most point
	pList = SortByAngle(pList, start);



	//1st and 2nd point are always part of the hull
	hull.push_back(pList[0]);
	hull.push_back(pList[1]);
	last = 1;

	//Add points to the hull in sorted order
	//If adding a point makes clock-wise turn then
	//   keep removing points from the hull until the tuen becomes counter clockwise
	for(unsigned int i=2; i<pList.size() ; i++) {
		MyPoint p = pList[i];
		while(last >= 1) {
			MyPoint p1 = hull[last];
			MyPoint p2 = hull[last-1];


			Vector A = CreateVector(p2,p1); // previous vector
			Vector B = CreateVector(p1,p); // new vector

			// cross product negative means clockwise turn
			double cross = Cross(A, B);
			if(cross < 0) {
				last = last-1;
				hull.pop_back();
			} else {
				break;
			}
		}

		hull.push_back(p);
		last++;
	}

	return hull;
}

int main()
{
	vmp P;
	P.push_back({2,5});
	P.push_back({4,5});
	P.push_back({5,6});
	P.push_back({2,4});
	P.push_back({4,4});
	P.push_back({6,4});
	P.push_back({5,3});

	vmp hull = ConvexHull(P);

	cout << "Hull: " << endl;
	PrintPoints(hull);
}
