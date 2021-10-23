/*
 * 5.DeleteDuplicate.cpp
 *
 * Problem: Given a sorted array of duplicates remove all repeated elements.
 *          A delete requires left shifting all elements on the right.
 *          So we do not want to delete right away.
 *
 * Expected time complexity O(n), space complexity O(1)
 *
 *  Created on: Aug 17, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;

// Put all unique element side by side and keep track of the position of last of them
// Compare next element with last of of the unique element.
// If new element is found then put it next to last unique one
int DeleteDuplicates(VI& A)
{

	unsigned int last=0;
	for(unsigned int i=1 ; i<A.size() ; ++i)
	{
		if(A[last] != A[i]) { // New unique element
			A[++last] = A[i]; // Add it to last and increment last
		}
	}

	unsigned int sz = A.size();
	for(last = last +1; last<sz ; ++last) { // remove all element from last+1
		A.pop_back();
	}

	return A.size();
}

void PrintVecctor(VI& A)
{
	for(int i:A) {
		cout << i << " ";
	}
	cout << endl;
}

int main()
{
	VI A = {2,3,5,5,7,11,11,11,13};
	DeleteDuplicates(A);
	PrintVecctor(A);
}


