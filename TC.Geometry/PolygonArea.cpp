/*
 * PolygonArea.cpp
 *
 *  Created on: Jul 15, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

struct MyPoint
{ double x,y; };

struct MyVector
{
	double a,b;
};

double dot(MyVector A, MyVector B)
{
	return A.a * B.a + A.b * B.b;
}

double cross(MyVector A, MyVector B)
{
	return A.a * B.b - A.b * B.a;
}

double distance(MyPoint A, MyPoint B)
{
	double d1=A.x-B.x;
	double d2=A.y-B.y;
	return sqrt(d1*d1 + d2*d2);
}

double PolygonArea(vector<MyPoint> Poly)
{
	double area = 0;

	for(unsigned int i=1; i < Poly.size()-1 ; i++)
	{
		MyVector AB = {(Poly[i].x - Poly[0].x), (Poly[i].y - Poly[0].y)};
		MyVector AC = {(Poly[i+1].x - Poly[0].x), (Poly[i+1].y - Poly[0].y)};

		double areaTriangleDoubled = cross(AB, AC);
		area += areaTriangleDoubled;
	}

	return abs(area / 2.0);
}

int main()
{
	vector<MyPoint> P;
	P.push_back({1,2});
	P.push_back({1,5});
	P.push_back({5,5});
	P.push_back({5,2});
	P.push_back({3,3});

	cout << PolygonArea(P) << endl;
}


