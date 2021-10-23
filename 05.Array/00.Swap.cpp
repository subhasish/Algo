/*
 * 0.Swap.cpp
 *
 * Problem: Swap two element in an array
 *
 *  Created on: Aug 19, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

void swap(int& A, int& B)
{
	//Note that NOT int& t=A;
	int t=A;  A = B;   B = t;
}

int main()
{
	vector<int> A = {0,1,2,3,4,5,6};
	swap(A[1],A[5]);

	for(int i: A){
		cout << i << " ";
	}
	cout << endl;
}
