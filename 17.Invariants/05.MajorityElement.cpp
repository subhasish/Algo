/*
 * 05.MajorityElement.cpp
 *
 * Problem: You are reading a sequence of strings. You know a priori that more than half the strings
 * 			are repetition of a single string (majority element). But the positions where
 * 			majority element occur is unknown.
 *
 * 			Write a program that takes a single pass over the elements and identifies the majority
 * 			element.
 *
 *  Created on: Jun 2, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Brute force is to store the count of each element in a hash table and then search.
//			But it takes additional storage.
//
//			Another intuition is there should be at least one copy of the majority element
//			given any other copy of another element.
//			So if we see two different elements then we can discard both as if one canceling another.
//
//			Algorithm would be we will keep track of candidate element and its count. When see
//			another same element we would increment the count and decrement when see different
//			element.
//			If count becomes 0 then next element seen can be treated as candidate.

string MajoritySearch(istringstream* input_stream)
{
	string candidate, iter;
	int candidate_count = 0;

	while(*input_stream >> iter) {
		if(candidate_count == 0) {
			candidate = iter;
			candidate_count = 1;
		} else {
			if(candidate == iter) {
				++candidate_count;
			} else {
				-- candidate_count;
			}
		}
	}

	return candidate;
}


int main()
{
	istringstream is("b a c a a b a a c a");
	string  m = MajoritySearch(&is);

	cout << m << endl;
}
