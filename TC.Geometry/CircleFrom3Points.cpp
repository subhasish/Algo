/*
 * CircleFrom3Points.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

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

bool FindInterSectionEq(LineEq p, LineEq q, MyPoint& intersect)
{
	double det = p.A*q.B - q.A*p.B;
	if(det == 0) {
		//lines are parallel
		return false;
	} else {
		intersect.x = (q.B*p.C - p.B*q.C)/det;
		intersect.y = (p.A*q.C - q.A*p.C)/det;

		return true;
	}
}

bool FindIntersection(LineSegment AB, LineSegment CD, MyPoint& intersect)
{
	LineEq p = FormLineEquation(AB);
	LineEq q = FormLineEquation(CD);

	bool res = FindInterSectionEq(p, q, intersect);
	if(!res)
		return false;

	if(PointWithinLine(intersect, AB) && PointWithinLine(intersect, CD))
	{
		return true;
	} else {
		return false;
	}
}

bool IsParallel(LineEq AB, LineEq CD)
{
	if(AB.B == 0 && CD.B == 0)
		return true;
	else if(AB.B == 0 || CD.B == 0)
		return false;
	else if(AB.A/AB.B == CD.A/CD.B)
		return true;
	else
		return false;
}

LineEq PerpendicularBisector(MyPoint X, MyPoint Y)
{
	LineEq XYq  = FormLineEquation({X,Y});
	double A = -XYq.B;
	double B = XYq.A;
	double midX = (X.x + Y.x)/2.0;
	double midY = (X.y + Y.y)/2.0;
	double C = A*midX + B*midY;
	return {A,B,C};
}

bool FindCircleFrom3Points(MyPoint X, MyPoint Y, MyPoint Z, MyPoint& center)
{
	//The 3 points has to be non co-linear
	LineEq XYq = FormLineEquation({X,Y});
	LineEq YZq = FormLineEquation({Y,Z});
	if(IsParallel(XYq, YZq))
		return false;

	LineEq XYpb = PerpendicularBisector(X,Y);
	LineEq YZpb = PerpendicularBisector(Y,Z);

	return FindInterSectionEq(XYpb, YZpb, center);
}

int main()
{
	MyPoint center;
	bool res = FindCircleFrom3Points({2,2}, {2,6}, {6,2}, center);

	if (res) {
		cout << "Center is at: (" << center.x << ", " << center.y << ")" << endl;
	} else {
		cout << "No circle possible" << endl;
	}
}


