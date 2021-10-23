/*
 * 08.SmallestSequentialCovering.cpp
 *
 * Problem: Problem is similar to the previous problem to find smallest covering, but the keywords should appear sequentially.
 * 			For recap here is the problem statement of smallest covering:
 * 			Consider the digest of a page returned by a search engine. It is the more or less smallest text that cover all query words.
 * 			Similarly, write a program that takes an array of string (text) and a set of string (query) and
 * 			returns the starting and ending index of the smallest sub-array that covers the set.
 *
 * Assumption: Each keyword is distinct.
 *
 *  Created on: Feb 24, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Key observation is that when we see i-th keyword, the last occurrence of (i-1)th keyword is part of the solution.
//			 When we see the first keyword then it can potentially start another sequence. Then if we see second keyword then it must consider the
//			 last occurrence of first keyword, and not any of its previous occurrences.
//
//			 Only thing to be aware that, after seeing optimal result up to 5th keyword, we may start seeing 1st and 2nd keyword,
//			 we keep them but should not alter solution of 5th keyword. Solution for 5th keyword will only gets updated when we see 5th keyword again.
//			 And we should update the solution even if it larger than previous distance AS WE HAVEN'T SEEN LAST KEYWORD.
//			 Let's say 6th is the last keyword, then it must consider latest occurrence of 5th keyword.
//
//			 So if we can store last occurrence of each keyword and the length of the sequence up to it then we can keep on computing incrementally.
//			 Key is to do it incrementally.

typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int, int> PII;

PII FindSmallestSequentialCovering(const VS& para, const VS& keys)
{
	unordered_map<string, int> keyword_to_index;					// Map each keyword to its index
	for(size_t i=0; i<keys.size() ; ++i) {							// initialize the keyword_to_index
		keyword_to_index[keys[i]] = i;
	}

	VI last_occurrence(keys.size(), -1);							// Last occurrence map, as vector with keyword as index

	VI shortest_length(keys.size(), numeric_limits<int>::max());	// Length of shortest sub-array ending at most recent occurrence

	PII result = make_pair<int,int>(-1, -1);
	int shortest_dist = numeric_limits<int>::max();

	for(int i=0 ; i<(int)para.size() ; ++i) {
		if(keyword_to_index.count(para[i])) {
			int keyword_idx = keyword_to_index[para[i]];

			if(keyword_idx == 0) 									// First keyword, start over
			{
				shortest_length[keyword_idx] = 1;
			}
			else if(shortest_length[keyword_idx-1] != numeric_limits<int>::max())	// We have seen all previous keywords
			{
				int distance_from_last = i - last_occurrence[keyword_idx-1];
				shortest_length[keyword_idx] = shortest_length[keyword_idx-1] + distance_from_last;
			}
			last_occurrence[keyword_idx] = i;


			if(keyword_idx == (int)keys.size()-1 && shortest_length.back() < shortest_dist)		// Last keyword, look for improved subarray
			{
				shortest_dist = shortest_length.back();
				result.second = i;
				result.first  = i - shortest_dist + 1;
			}
		}
	}

	return result;
}


int main()
{
	PII result;
	VS para = {"apple", "banana", "apple", "apple", "dog", "cat", "apple", "dog", "banana", "apple", "cat", "dog"};
	VS keywords = {"cat", "banana"};

	result = FindSmallestSequentialCovering(para, keywords);

	for(int i=result.first ; i<= result.second; ++i) {
		cout << para[i] << " ";
	}
}
