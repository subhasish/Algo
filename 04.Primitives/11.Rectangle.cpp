/*
 * 11.Rectangle.cpp
 *
 * Given two rectangles whose sides are parallel to axes, compute
 * 1. whether they intersect
 * 2. the area between their intersection
 *
 *  Created on: Jun 29, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

struct Rectangle
{
	int x,y,height,width;
};

bool IsIntersect(const Rectangle& R1, const Rectangle R2)
{
	//Interesting
	return R1.x <= R2.x + R2.width && R2.x <= R1.x + R1.width &&
			R1.y <= R2.y + R2.height && R2.y <= R1.y + R1.height;
}

Rectangle IntersectRectangle(const Rectangle& R1, const Rectangle& R2)
{
	if(!IsIntersect(R1,R2)) {
		return {0,0,-1,-1};
	}

	Rectangle Ret;
	//Interesting!!!!!
	Ret.x = max(R1.x,R2.x);
	Ret.y = max(R1.y,R2.y);
	Ret.width = min(R1.x+R1.width, R2.x+R2.width) - Ret.x;
	Ret.height = min(R1.y+R1.height, R2.y+R2.height) - Ret.y;

	return Ret;
}

void PrintRectangle(const Rectangle& R)
{
	cout << "x=" << R.x << ", y=" << R.y << ", width=" << R.width << ", height=" << R.height << endl;
}

int main()
{
	Rectangle R1 = IntersectRectangle({1,1,2,2},{2,2,2,2});
	PrintRectangle(R1);
	Rectangle R2 = IntersectRectangle({1,1,2,2},{4,2,2,2});
	PrintRectangle(R2);
}
