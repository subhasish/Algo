/*
 * 07.SmallestCovering.cpp
 *
 * Problem: Consider the digest of a page returned by a search engine. It is the more or less smallest text that cover all query words.
 * 			Similarly, write a program that takes an array of string (text) and a set of string (query) and
 * 			returns the starting and ending index of the smallest sub-array that covers the set.
 *
 *  Created on: Feb 23, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//				Could try to see if for each range they cover the set or not. Even using hash table total time O(n^3).
//
//				Can improve by growing the subarray incrementally, starting for each index we search until we cover all keywords.
//				We can track of remaining keyword. This gives overall time complexity O(n^2)
//
//				However we can however improve more by reusing the computation of index i for index i+1.
//				The only keyword we need to remove in that case is word i and find until we see that character.
//				Note that it may be the case that we had other occurrences of word i, in that case we readily have have better solution.

typedef pair<int, int> PII;
typedef vector<string> VS;
typedef unordered_set<string> USS;

PII FindSmallestCoveringSubset(const VS& para, const USS keys)
{
	unordered_map<string, int> count_keywords_in_range;  // we need to store the actual frequencies of elements in the range
	PII result = make_pair<int,int>(-1,-1);

	// Populate
	for(string s: keys) {
		count_keywords_in_range[s] = 0;
	}

	int left = 0, right = 0;								// left to right is the range currently under consideration
	int count_to_cover = keys.size();  						// count to ease computation
	while(right < (int)para.size())
	{
		// New character is right
		if(keys.count(para[right])) {  						// It is one of the words that matters
			++count_keywords_in_range[para[right]];

			if(count_keywords_in_range[para[right]] == 1) {		// We are seeing it for he first time in the range. So count it
				--count_to_cover;
			}
		}

		while(count_to_cover == 0) {						// If we have covered all keywords then we can move the left
			if( (result.first == -1 && result.second == -1) ||
				(right - left  < result.second - result.first))
			{
				result.first = left;
				result.second = right;
			}

			if(keys.count(para[left])) {  					// Left had a keyword. See if removing it still covers the set
				--count_keywords_in_range[para[left]];

				if(count_keywords_in_range[para[left]] == 0) // Check if it is no more present in the range
				{
					++count_to_cover;
				}
			}
			++left;
		}

		++right;
	}
	return result;
}

int main()
{
	PII result;
	VS para = {"apple", "banana", "apple", "apple", "dog", "cat", "apple", "dog", "banana", "apple", "cat", "dog"};
	USS keywords = {"banana", "cat"};

	result = FindSmallestCoveringSubset(para, keywords);

	for(int i=result.first ; i<= result.second; ++i) {
		cout << para[i] << " ";
	}
}
