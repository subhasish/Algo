/*
 * 07.SmallestCoveringOnline.cpp
 *
 * Problem: Same as previous problem of smallest covering:
 * 			Consider the digest of a page returned by a search engine. It is the more or less smallest text that cover all query words.
 * 			Similarly, write a program that takes an Stream of string (input text) and a set of string (query) and
 * 			returns the starting and ending index of the smallest sub-array that covers the set.
 *
 * 			One problem we had with previous solution as we were keeping the subarray in memory. Not scalable if subarray is large.
 * 			How to solve the online version of the problem.
 *
 *  Created on: Feb 24, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//				One useful observation is that only the last appearance of keywords matter.
//				If we could maintain the keywords in order of their appearance then difference between first and last entry
//				in that order is the length of the sequence.
//
//				As we have seen in LRU cache problem, it is also similar to that. We need to maintain a double linked list
//				so that whenever we see a keyword we can move that to the front of the list.

typedef vector<string> VS;
typedef pair<int, int> PII;
typedef unordered_set<string> USS;

PII FindSmallestCoveringSubsetOnline(istringstream* iss, const USS& keys)
{
	list<int> last_occurrence;							// Stores the last occurrence. Order will be maintained
	unordered_map<string, list<int>::iterator> Table;	// Maps keywords to the list. The list has the last occurrence. So effectively keyword to last occurrence.

	PII result = make_pair<int,int>(-1, -1);

	for(string s: keys) {
		Table[s] = last_occurrence.end();
	}

	int index = 0;
	string s;
	while(*iss >> s)
	{
		// If it is a keyword then we want to update its last occurrence and then recompute the smallest distance

		auto it = Table.find(s);
		if(it != Table.end())				// It is a keyword. So "it" points to the node.
		{
			list<int>::iterator l_it = it->second;

			if(l_it != last_occurrence.end()) {			// remove if previously seen
				last_occurrence.erase(l_it);
			}
			last_occurrence.push_front(index);			// Move to front
			it->second = last_occurrence.begin();

			if(last_occurrence.size() == keys.size())	// Have seen all keywords
			{
				if((result.first == -1 && result.second == -1) ||
						(index - last_occurrence.back() < result.second - result.first))
				{
					result.first = last_occurrence.back();
					result.second = index;
				}
			}


		}
		++index;
	}
	return result;
}

int main()
{
	PII result;
	USS keywords = {"banana", "cat"};
	VS v_para = {"apple", "banana", "apple", "apple", "dog", "cat", "apple", "dog", "banana", "apple", "cat", "dog"};
	string para;
	for (string s: v_para) {
		para += s + " ";
	}
	istringstream iss(para);

	result = FindSmallestCoveringSubsetOnline(&iss, keywords);

	for(int i=result.first ; i<= result.second; ++i) {
		cout << v_para[i] << " ";
	}
}
