/*
 * 09.LongestDistinctSubArray.cpp
 *
 * Problem: Write a program that takes an array and return the length of longest subarray containing only distinct entries.
 *
 *  Created on: Feb 25, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: 	To be able to update the max after each character read I want to keep track of
//				subarray with distinct elements ending at the current element
//				Can use two indices left and right to mark the interval and a hash table to keep
//				those distinct elements
//
//				If new element is present then remove all elements from window until the old
//				element is not encountered on the left.
typedef vector<int> VI;
typedef pair<int, int> PII;

PII FindLongestDistinctSubArray(const VI& array)
{
	int left = 0, right = 0;
	unordered_set<int> distinct_upto_current;

	PII result = make_pair<int, int> (-1, -1);
	int longest_length = 0;

	while(right < (int)array.size())
	{
		int n = array[right];
		auto it = distinct_upto_current.find(n);

		if(it != distinct_upto_current.end())				// Already in the distinct set
		{
			while(array[left] != n)							// Remove all elements up to that one, so that we can include current entry
			{
				distinct_upto_current.erase(array[left]);
				++left;
			}
			distinct_upto_current.erase(n);
			++left;
		}

		assert(distinct_upto_current.find(n) == distinct_upto_current.end());

		distinct_upto_current.emplace(n);					// Add the current element

		if(longest_length < (int)distinct_upto_current.size())
		{
			longest_length = distinct_upto_current.size();
			result.first = left;
			result.second = right;
		}

		++right;
	}

	return result;
}


int main()
{
	VI arr = {1, 2, 1, 3, 4, 5, 3, 6, 5, 3};
	PII result = FindLongestDistinctSubArray(arr);

	for(int i = result.first ; i <= result.second; ++i) {
		cout << arr[i] << ", ";
	}
}
