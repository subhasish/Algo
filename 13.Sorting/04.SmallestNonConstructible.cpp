/*
 * 04.SmallestNonConstructible.cpp
 *
 * Problem: Write a program that takes an array of positive integers and
 * 			returns the smallest number which is not the sum of subset of elements in the array.
 *
 *  Created on: Mar 8, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Few observations: the sum_of_all+1 is never constructible, upper bound. The lowest element puts a lower bound.
//			Playing with few examples gives the generic formula:
//				Suppose a collection of elements can produce every value up to and including V but not V+1.
//				Now consider effect of adding a new element u:
//					If u <= V+1 then we can still produce every value up to and including u+V
//					Else if u>V+1 then V+1 is still the smallest constructible value
//
//			Another observation is that order of the element in the array does not matter for constructing amounts.
//			However, by sorting the array allows us to stop when we reach a value that is too large to help.

int SmallestNonConstructible(vector<int> nums)
{
	sort(nums.begin(), nums.end());

	int smallest_constructible = 0;
	for(int i: nums) {
		if(i <= smallest_constructible + 1) {	// Case 1
			smallest_constructible += i;
		} else {
			return smallest_constructible + 1;
		}
	}
	return smallest_constructible + 1;
}

int main()
{
	vector<int> A = {12,2,1,15,2,4};

	cout << "Cannot construct: " << SmallestNonConstructible(A) << endl;
}
