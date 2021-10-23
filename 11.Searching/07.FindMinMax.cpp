/*
 * 07.FindMinMax.cpp
 *
 * Problem: We are given an array of comparable objects where each object comparison is expensive.
 * 			Now we want to find both minimum and maximum objects in less than 2(n-1) comparisons.
 *
 *  Created on: Feb 10, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Tricky idea: If we compare two numbers then smaller one cannot be the largest ever, so no need to compare it with largest.
//           Take two items in pair and compare larger one with running largest and smaller with running smallest.
//
// 			 Implementation is also tricky. Have to consider odd number of elements.
//
// Time complexity: 3 comparisons for each 2 elements. So, O(3/2 n)

typedef pair<int, int> PI;
typedef vector<int> VI;

PI minmax(int& a, int& b)
{
	return (a < b) ? make_pair(a,b) : make_pair(b,a);
}

PI FindMinMax(VI arr)
{
	if(arr.size() < 1) {
		throw length_error("Array is empty!!");
	}

	PI res = { arr.front(), arr.front() };

	// Process two element at a time
	for(size_t i=0; i+1<arr.size() ; i += 2) {
		PI mm = minmax(arr[i], arr[i+1]);
		if(mm.first < res.first) {
			res.first = mm.first;
		}
		if(mm.second > res.second) {
			res.second = mm.second;
		}
	}

	// For odd length array we still need to handle last element
	if(arr.size() %2 != 0) {
		res = {min(res.first, arr.back()) , max(res.second, arr.back()) };
	}

	return res;
}

int main()
{
	VI arr = {3, 2, 5, -7, -3, 6, 1, 9, 4};
	PI res = FindMinMax(arr);
	cout << "Min = " << res.first << ", Max = " << res.second << endl;

	arr = {2};
	res = FindMinMax(arr);
	cout << "Min = " << res.first << ", Max = " << res.second << endl;
}
