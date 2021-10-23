/*
 * 02.MergeSortedArrays.cpp
 *
 * Problem: Write a program that takes two sorted arrays and updates the first one with the combined with the
 * 			combined entries of the two arrays in sorted order.
 *
 *  Created on: Mar 7, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Only challenge from traditional merge is writing the result back in input.
//			 Instead we can fill it from the end
//
// C++:
//		Parameter taking array declared as int A[]. Pass array with name as address
//		Range based iterator works for static arrays but not for dynamic arrays

typedef vector<int> VI;

void MergeSortedArrays(int A[], int m, int B[], int n) // m and n are the size of the two arrays
{
	int i=m-1, j=n-1, write_idx=m+n-1;

	while(i>=0 && j>=0) {
		A[write_idx--] = (A[i] > B[j]) ? A[i--] : B[j--];
	}

	while(j>=0) {
		A[write_idx--] = B[j--];
	}
}

int main()
{
	//int* A = new int[11] { 1,3,5,7,33,99 };
	int A[30] = { 1,3,5,7,33,99 };
	int B[5] = { -9,-5,0,44,55};

	MergeSortedArrays(A, 6, B, 5);

	for(int i: A) {
		cout << i << ", ";
	}
	cout << endl;
}
