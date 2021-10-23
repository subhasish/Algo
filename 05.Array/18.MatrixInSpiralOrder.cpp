/*
 * 18.MatrixInSpiralOrder.cpp
 *
 * Problem: Given a square matrix print it in spiral order
 *
 *  Created on: Sep 9, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

// One key trick is NOT to:
//    print n elements of 1st row, then n-1 element of last column and last row, and then n-2 elements of 1st column.
//    This non-uniform approach is not good for generalizing
// Instead:
//    print n-1 elements each time from 1st row, then from last column, last row and then from 1st column
void MatrixInSpriralOrder(VVI& mat)
{
	VI res;

	// Increment step for each iteration
	VVI inc = {{0,1}, {1,0}, {0,-1}, {-1,0}};

	// In each iteration:
	//    size of matrix will decrease by 2
	//    start point is (i,i) for iteration i


	int sz = mat.size();
	int offset = 0;

	cout << endl << "Matrix in spiral order: ";

	for(int n=sz; n>0 ; n -= 2) {
		int x=offset, y=offset;
		if(n==1) {
			cout << mat[x][y] << ", ";
		} else {
			// For 4 directions. Use j to pick increment from array inc
			for(int j=0; j<4 ; ++j) {
				// Print (n-1) elements
				for(int k=0; k<n-1; ++k) {
					cout << mat[x][y] << ", ";

					// in last iteration of this direction these increments will help start next direction
					x += inc[j][0];
					y += inc[j][1];
				}
			}
		}
		++offset;
	}
}

int main()
{
	VVI mat1 = {
			{1,2,3},
			{4,5,6},
			{7,8,9}
	};
	MatrixInSpriralOrder(mat1);

	VVI mat2 = {
			{1,2,3,4},
			{5,6,7,8},
			{9,10,11,12},
			{13,14,15,16}
	};
	MatrixInSpriralOrder(mat2);
}

