/*
 * 20.GeneratePascalTriangle.cpp
 *
 * Problem: Given an integer n we need to form a Pascal Triangle with n rows.
 *
 * Pascal triangle looks like following:
 *       1
 *      1 1
 *     1 2 1
 *    1 3 3 1
 *   1 4 6 4 1
 *  Property of Pascal Triangle is following:
 *    1. Each row has one more element than its previous row
 *    2. Value at each element is the sum of its parents
 *
 *  Created on: Sep 12, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;
typedef vector<VI>  VVI;

void PrintPascalTriangle(VVI arr) {
	double sz=arr.size();
	for(int i=0; i<sz ; ++i) {
		//Each row increased one space. So (size-i) space for row i.
		for(int j=0; j<(sz-i); ++j) {
			cout << " ";
		}
		for(unsigned int j=0; j<arr[i].size() ; ++j) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

// Trying to store element as shown in the figure is problematic; as assigning indices.
// We can store them from start of the row.
// Then j th element in i th row is the sum of (j-1) and j th elements in (i-1) row
VVI GeneratePascalTriangle(int n)
{
	VVI pascalTriangle;

	for(int i=0; i<n ; ++i) {
		VI row;

		//row i has (i+1) elements
		for(int j=0 ; j <= i ; ++j) {
			if(j==0 || j==i) {
				row.push_back(1);
			} else {
				row.push_back(pascalTriangle[i-1][j-1] + pascalTriangle[i-1][j]);
			}
		}

		pascalTriangle.push_back(row);
	}

	return pascalTriangle;
}

int main()
{
	PrintPascalTriangle(GeneratePascalTriangle(15));
}



