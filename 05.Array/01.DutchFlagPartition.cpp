/*
 * 1.DutchFlagPartition.cpp
 *
 * Problem: It is 3 way partitioning done in Quick sort Sedgewick course
 *
 *  Created on: Aug 13, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef enum  {
	Red,
	White,
	Blue,
	Green
} Color;

void swap(Color& A, Color& B)
{
	Color t=A;  A = B;   B = t;
}

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr)
{
	vector<Color>& A = *A_ptr;
	Color pivot = A[pivot_index];

	int i=0,lo=0,hi=A.size()-1;

	// Smaller:      A[0, lo-1]
	// Equal:        A[lo, i-1]
	// Unclassified: A[i, hi]
	// Larger:       A[hi+1, A.size()-1]

	while(i<=hi) {
		if(A[i] < pivot) {
			swap(A[lo],A[i]);
			lo++; i++;
		} else if(A[i] == pivot) {
			i++;
		} else {
			swap(A[hi--],A[i]);  // NO i++
		}
	}

}

int main()
{
	vector<Color> vec = {Blue, Red, Blue, White, Blue,Blue, Green, Red, Red, White};

	DutchFlagPartition(3, &vec);

	for(unsigned int i=0; i< vec.size() ; i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}


