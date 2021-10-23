/*
 * Rotation.cpp
 *
 *  Created on: Jul 22, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

const double PI = 3.14159265;

struct MyPoint
{ double x,y; };

MyPoint Rotate(MyPoint origin, MyPoint p, double angle)
{
	if(angle == 0)
		return p;

	double rad = angle * PI /180.0;  //One radian is equivalent to 180/PI degrees
	MyPoint np = {p.x - origin.x, p.y - origin.y}; //shift the origin

	//rotate the point
	double nx = np.x * cos(rad) - np.y * sin(rad);
	double ny = np.x * sin(rad) + np.y * cos(rad);

	return {nx+origin.x, ny+origin.y};
}

int main()
{
	MyPoint res = Rotate({4,4}, {2,6}, 180);
	cout << "New rotated point: (" << res.x << ", " << res.y << ")" << endl;
}


