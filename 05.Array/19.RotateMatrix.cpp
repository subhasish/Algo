/*
 * 19.RotateMatrix.cpp
 *
 * Problem: Given a square matrix, rotate it by 90 degree clock-wise
 *
 *  Created on: Sep 11, 2017
 *      Author: subha
 */

#include<bits/stdc++.h>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

// Working through corner examples makes it clear that, after 90 degree rotation
// element at (i,j) goes to position (j, n-1-i)

// Brute force will be to place each element in an auxiliary array and then put them back.
// But it would take lot of extra space

// Working through examples also make it clear that 4 elements make a cycle.
// So we can rotate 4 elements at one go using constant amount of extra space.
void RotateMatrix(VVI& mat)
{
	int sz = mat.size();

	// Now this rotation need to be done for only one quarter of the matrix.
	// But the quarter is the upper triangle of the square (V from center to the 1st row)

	for(int i=0; i < (sz/2) ; ++i) {
		// For each row start with element (i,i)
		// and go upto (n-1-i)
		for(int j=i; j<(sz-1-i) ; ++j) {
			int temp1 = mat[i][j];
			int temp2 = mat[j][sz-1-i];
			int temp3 = mat[sz-1-i][sz-1-j];
			int temp4 = mat[sz-1-j][i];

			mat[i][j] = temp4;
			mat[j][sz-1-i] = temp1;
			mat[sz-1-i][sz-1-j] = temp2;
			mat[sz-1-j][i] = temp3;

		}
	}
}

void PrintMatrix(VVI& mat)
{
	cout<< "Matrix: " << endl;
	for(unsigned int i=0; i<mat.size() ; ++i) {
		for(unsigned int j=0; j<mat.size() ; j++) {
			cout << mat[i][j] << ", ";
		}
		cout << endl;
	}
}

int main()
{
	VVI mat1 = {
			{1,2,3},
			{4,5,6},
			{7,8,9}
	};
	RotateMatrix(mat1);
	PrintMatrix(mat1);

	VVI mat2 = {
			{1,2,3,4},
			{5,6,7,8},
			{9,10,11,12},
			{13,14,15,16}
	};
	RotateMatrix(mat2);
	PrintMatrix(mat2);
}


