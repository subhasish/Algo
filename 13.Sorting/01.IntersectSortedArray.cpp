/*
 * 01.IntersectSortedArray.cpp
 *
 * Problem: Given two sorted arrays find the intersection of the arrays.
 * 			Remove duplicates as well.
 *
 * 			Application of this would be the merging the result of two indices during a search of multiple keywords.
 *
 *  Created on: Mar 6, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			If one is very small than other then doing binary search of smaller in the larger one makes sense.
//			Otherwise doing merge kind of algorithm makes sense.

typedef vector<int> VI;

// Large one is very larger than the smaller one
VI IntersectSmallLargeSorted(const VI& small, const VI& large)
{
	VI intersect;
	for(int i=0; i< (int) small.size() ; ++i) {
		if(i==0 || small[i] != small[i-1]) {
			if(binary_search(large.begin(), large.end(), small[i])) {
				intersect.emplace_back(small[i]);
			}
		}
	}
	return intersect;
}

// For generic one use merge kind of logic
VI IntersectTwoSortedArrays(const VI& A, const VI& B)
{
	VI intersect;
	unsigned int i=0, j=0;
	while(i<A.size() && j<B.size()) {
		if(A[i] == B[j] && (i == 0 || A[i] != A[i-1])) {
			intersect.emplace_back(A[i]);
			++i; ++j;
		} else if(A[i] > B[j]) {
			++j;
		} else {
			++i;
		}
	}

	return intersect;
}

int main()
{
	VI A = {2,3,3,5,7,11};
	VI B = {3,3,7,7,7,15,31};

	VI res = IntersectSmallLargeSorted(A,B);
	for(int i: res) {
		cout << i << ", ";
	}
	cout << endl;

	res = IntersectTwoSortedArrays(A,B);
	for(int i: res) {
		cout << i << ", ";
	}
	cout << endl;
}
