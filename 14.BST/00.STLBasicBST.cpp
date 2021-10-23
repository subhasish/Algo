/*
 * 00.STLBasicBST.cpp
 *
 * Problem: STL for BST is map and set. Use their basic functions.
 *
 *  Created on: Mar 19, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			*begin()/*rbegin() gives the minimum and maximum keys
//			lower_bound(k)/upper_bound(k) gives first element >= and > than the argument
//			equal_range(k) returns the range as pair of lower_bound and upper_bound

int main()
{
	set<int> collection;
	collection.emplace(19);
	collection.emplace(7);
	collection.emplace(43);
	collection.emplace(3);
	collection.emplace(11);
	collection.emplace(23);
	collection.emplace(47);
	collection.emplace(2);
	collection.emplace(5);
	collection.emplace(17);
	collection.emplace(37);
	collection.emplace(53);
	collection.emplace(13);
	collection.emplace(29);
	collection.emplace(41);
	collection.emplace(31);

	cout << "Minimum: " << *collection.begin() << endl;
	cout << "Maximum: " << *collection.rbegin() << endl;

	cout << "Lower bound of 31: " << *collection.lower_bound(31) << endl;
	cout << "Upper bound of 31: " << *collection.upper_bound(31) << endl;

	auto ret = collection.equal_range(31);
	cout << "Range of 31: " << *ret.first << ", " << *ret.second << endl;



}
