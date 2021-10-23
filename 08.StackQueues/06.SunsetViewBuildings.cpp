/*
 * 06.SunsetViewBuildings.cpp
 *
 * Problem: Given an array of heights of buildings east to west, process them east to west to determine the
 *          buildings that have the sunset view (means can be visible from west).
 *          Input can also be thought as an online stream of buildings from east to west.
 *
 *
 *  Created on: Jan 2, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//           If we had process them in west to east then we could maintain a running maximum and the buildings
//           that are greater than current maximum are ones that gets the sunset view.
//
//           But from east to west we need to maintain the stack of such buildings. When a new building is encountered
//           we will continuously pop all the buildings that are smaller or equal that one, because it would hide them.
//           Resulting the stack will always keep buildings in the order of decreasing height.

typedef vector<int> VI;

VI SunsetViewBuildings(istringstream sin)
{
	VI buildingStack;
	int height;

	while(sin >> height) {
		while(!buildingStack.empty()) {
			if(buildingStack.back() > height) {
				break;
			} else {
				buildingStack.pop_back();
			}
		}
		buildingStack.push_back(height);
	}

	return buildingStack;
}

string VItoString(VI v) {
	ostringstream oss;
	for (int i: v) {
		oss << i <<  " ";
	}
	return oss.str();
}


int main() {
	string heights;

	heights = "22 5 11 5 9 4 6 2";
	cout << "Buildings=   " << heights << endl;
	cout << "Sunset view= " << VItoString(SunsetViewBuildings(istringstream(heights))) << endl;
}


