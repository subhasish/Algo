/*
 * 8.AlternateRearrange.cpp
 *
 * Problem: Given an array A of numbers, rearrange them so that
 *          A[0] <= A[1] >= A[2] <= A[3] >= A[4] and so on
 *  Created on: Aug 19, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;

void print_vector(vector<int> list)
{
	for(int i: list)
	{
		cout << i << " ";
	}
	cout << endl;
}

// O(n log n) solution: could be sort and then rearrange (A[1],A[2]),(A[3],A[4]),..
// O(n) alternative solution: Find median and put elements in even and odd position
//                            by comparing it with median
// Simpler solution: If an element breaks the rule w.r.t. its previous element then
//                   just swap that two. Ex: 3,4,5 => 3,5,4; 5,4,3 => 5,3,4

void swap(int& A, int& B)
{
	//Note that NOT int& t=A;
	int t=A;  A = B;   B = t;
}


void AlternateRearrange(VI& A)
{
	for(unsigned int i=1; i<A.size(); ++i) {
		if(i%2 != 0) {
			if(A[i-1] > A[i]) {
				swap(A[i-1], A[i]);
			}
		} else {
			if(A[i-1] < A[i]) {
				swap(A[i-1], A[i]);
			}
		}
	}

}



int main()
{
	VI A = {1,2,3,4,5,6,7,8};
	AlternateRearrange(A);

	print_vector(A);
}


