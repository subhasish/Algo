/*
 * 2.PlusOne.cpp
 *
 * Problem: Given an array representing am integer, incerment it by 1
 *
 *  Created on: Aug 14, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;

VI PlusOne(VI A)
{
	//vector<int>::back gives the reference to the last element
	A.back()++;

	for(int i=A.size()-1; i>0 && A[i] == 10 ; i--) { //NOT going up to 0th digit
		A[i] = 0;
		A[i-1]++;
	}

	//first digit
	if(A[0] == 10) {
		A[0] = 0;
		A.insert(A.begin(), 1); //insert at certain position
	}

	return A;
}

void printInteger(VI A)
{
	for(int i: A) {
		cout << i;
	}
	cout << endl;
}

int main()
{
	printInteger(PlusOne({7}));
	printInteger(PlusOne({9}));
	printInteger(PlusOne({7,9}));
	printInteger(PlusOne({1,2,9}));
	printInteger(PlusOne({9,9,9,9}));
}



