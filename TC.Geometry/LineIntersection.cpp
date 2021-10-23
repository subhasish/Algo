/*
 * LineIntersection.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

const double Epsilon = 1e-6;

struct MyPoint
{ double x,y; };

struct LineSegment
{ MyPoint one, two; };

struct LineEq
{ double A,B,C; };

LineEq FormLineEquation(LineSegment ln)
{
	double A = ln.two.y - ln.one.y;
	double B = ln.one.x - ln.two.x;
	double C = A * ln.one.x + B * ln.one.y;

	return {A, B, C};
}

bool LessThanEqual(double a, double b)
{
	if( b-a > Epsilon )
		return true;
	else
		return false;
}

bool PointWithinLine(MyPoint p, LineSegment AB)
{
	if(min(AB.one.x, AB.two.x) <= p.x &&
			p.x <= max(AB.one.x, AB.two.x) &&
			min(AB.one.y, AB.two.y) <= p.y &&
			p.y <= max(AB.one.y, AB.two.y))
	{
		return true;
	} else {
		return false;
	}
}

//bool PointWithinLine(MyPoint p, LineSegment AB)
//{
//	if(LessThanEqual( min(AB.one.x, AB.two.x), p.x) &&
//			LessThanEqual(p.x, max(AB.one.x, AB.two.x)) &&
//			LessThanEqual(min(AB.one.y, AB.two.y), p.y) &&
//			LessThanEqual(p.y, max(AB.one.y, AB.two.y)))
//	{
//		return true;
//	} else {
//		return false;
//	}
//}


bool FindIntersection(LineSegment AB, LineSegment CD, MyPoint& intersect)
{
	LineEq p = FormLineEquation(AB);
	LineEq q = FormLineEquation(CD);

	double det = p.A*q.B - q.A*p.B;
	//if(abs(det) < Epsilon) {       // Do it instead of comparing equality with 0
	if(det == 0) {
		//lines are parallel
		return false;
	} else {
		intersect.x = (q.B*p.C - p.B*q.C)/det;
		intersect.y = (p.A*q.C - q.A*p.C)/det;
	}

	if(PointWithinLine(intersect, AB) && PointWithinLine(intersect, CD))
	{
		return true;
	} else {
		return false;
	}

}

int main()
{
	MyPoint res;
	bool doesIntersect;

	doesIntersect = FindIntersection( {{1,5},{5,5}}, {{1,2},{5,6}}, res);
	if(!doesIntersect) {
		cout << "Lines does not intersect" << endl;
	} else {
		cout << "Lines intersect at: (" << res.x << ", " << res.y << ")" << endl;
	}
}


