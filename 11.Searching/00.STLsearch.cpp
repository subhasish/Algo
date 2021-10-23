/*
 * 00.STLsearch.cpp
 *
 * Problem: Use STL library search functions
 *
 *  Created on: Feb 5, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;

int main()
{

	VI  V = {1,2,3,4,5,6,7,8};

	// Iterative search: Returns iterator
	VI::iterator it = find(V.begin(), V.end(), 6);
	if(it == V.end()) cout << "Number not found" << endl;
	else cout << "Number found" << endl;


	// Binary search: returns bool
	bool found = binary_search(V.begin(), V.end(), 6);
	if(!found) cout << "Number not found" << endl;
	else cout << "Number found" << endl;


	// lower_bound: first element which is not less than val. Can be equal.
	// upper_bound: first element which is greater than val. Cannot be equal.
	// return type of lower_bound, upper_bound is vector<int>::iterator
	auto lb = lower_bound(V.begin(), V.end(), 6);
	vector<int>::iterator ub = upper_bound(V.begin(), V.end(), 6);
	if(lb == V.end()) cout << "No lower bound" << endl;
	else cout << "Lower bound (first one that is not less): " << *lb << endl;
	if(ub == V.end()) cout << "No upper bound" << endl;
	else cout << "Upper bound (first one that is greater) : " << *ub << endl;

	//equal_range(k) returns the range as pair of lower_bound and upper_bound
	auto ret = equal_range(V.begin(), V.end(), 6);
	cout << "Range of 31: " << *ret.first << ", " << *ret.second << endl;

}


