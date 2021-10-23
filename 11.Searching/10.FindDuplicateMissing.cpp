/*
 * 10.FindDuplicateMissing.cpp
 *
 * Problem: An array of size n contains distinct numbers in range 0 to n-1, with one number appearing twice and one number missing.
 * 			Find the two numbers that is duplicated and missing.
 *
 * 			Use no extra storage.
 *
 *  Created on: Feb 11, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//		If extra storage was allowed then I would use hash table.
//
//		If either one number was missing or one number was duplicated then we could either take sum and compare with sum of n numbers.
//		Or, we could do xor of the number with the xor of first n numbers, then that would result in the single number.
//		But here we have two numbers!!
//
//		Let's say the two numbers are m and d.
//		One thing is that if we take difference of sums then we get (d - m).
//		We need another equation, product will not help as it will hit overflow most likely.
//
//		If we take xor of numbers with all numbers 0 to n then we left with (m xor d)
//		This does not seem very helpful at first glance, but note that the xor result will have bit set for which m and d differs.
//		This will help us to separate the search space of m and d.
//		If ith bit is set to 1 then take xor of all numbers between 0 to n whose ith bit is 1, and for all such number in the input.
//		This will result in one of m and d.

typedef vector<int> VI;
typedef pair<int, int> PII;

PII FindDuplicateMissing(const VI& arr)
{
	int n = (int) arr.size();

	int miss_xor_dup = 0;
	for(int i=0 ; i<n ; ++i) {
		miss_xor_dup ^= arr[i] ^ i;
	}

	// We need to find a bit that is set to 1 in miss_xor_dup
	// Use bit fiddling technique to find the last bit set in miss_xor_dup
	int differ_bit = miss_xor_dup & (~(miss_xor_dup-1));

	int miss_or_dup = 0;
	// Focus only on elements for which differ_bit is set 1
	for(int i=0 ; i<n ; ++i) {
		if(arr[i] & differ_bit) {
			miss_or_dup ^= arr[i];
		}
		if(i & differ_bit) {
			miss_or_dup ^= i;
		}
	}

	// Found one, get another
	int another = miss_or_dup ^ miss_xor_dup;
	for(int a: arr) {
		if(a == miss_or_dup) {
			return make_pair(miss_or_dup, another);
		}
	}

	return make_pair(another, miss_or_dup);
}


int main()
{
	VI arr = {3,2,0,1,4,6,3,7,8};  // Duplicate 3, missing 5
	PII miss_and_dup = FindDuplicateMissing(arr);

	cout << "Duplicate = " << miss_and_dup.first << ", Missing = " << miss_and_dup.second << endl;
}
