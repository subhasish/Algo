/*
 * 0.limits.cpp
 *
 *  Created on: Jun 11, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
	cout << numeric_limits<int>::min() << endl;
	cout << numeric_limits<int>::max() << endl;
	cout << numeric_limits<float>::min() << endl;
	cout << numeric_limits<float>::max() << endl;
	cout << numeric_limits<double>::epsilon() << endl;
	cout << numeric_limits<double>::infinity() << endl;
}

