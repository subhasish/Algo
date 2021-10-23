/*
 * LinePointDistance.cpp
 *
 *  Created on: Jul 15, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

struct MyPoint
{ double x,y; };


struct Vector
{
	double a,b;
};

double dot(Vector A, Vector B)
{
	return A.a * B.a + A.b * B.b;
}

double cross(Vector A, Vector B)
{
	return A.a * B.b - A.b * B.a;
}

double distance(MyPoint A, MyPoint B)
{
	double d1=A.x-B.x;
	double d2=A.y-B.y;
	return sqrt(d1*d1 + d2*d2);
}

// Computes distance of point C from the line segment AB
double LinePointDistance(MyPoint A, MyPoint B, MyPoint C)
{
	Vector AB = {B.x-A.x, B.y-A.y};
	Vector BC = {C.x-B.x, C.y-B.y};

	double ABCdot = dot(AB,BC);
	if(ABCdot >=0) //Cos theta of AB and BC is positive => nearest point is B
		return distance(B,C);

	Vector BA = {-AB.a, -AB.b};
	Vector AC = {C.x-A.x, C.y-A.y};

	double BACdot = dot(BA,AC);
	if(BACdot >=0) //Cos theta of BA and AC is positive => nearest point is A
		return distance(A,C);

	//If both above is false => nearest point is on the line segment
	//Find the area of the triangle using cross product then divide by base to get the height
	double areaPolygon = cross(AB,BC);
	if (areaPolygon < 0) areaPolygon = -areaPolygon;
	return areaPolygon / distance(A,B);
}

int main()
{
	cout << LinePointDistance({1,2}, {4,5}, {1,1}) << endl;
	cout << LinePointDistance({1,2}, {4,5}, {5,5}) << endl;
	cout << LinePointDistance({1,2}, {4,5}, {4,3}) << endl;
}


