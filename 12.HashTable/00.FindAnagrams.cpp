/*
 * 00.FindAnagrams.cpp
 *
 * Problems: Anagrams are a set of words where one word from the set can be obtained by re-arranging letters of other word.
 *			 Given a set of words return group of anagrams. Only consider groups whose size is more than 2.
 *
 *  Created on: Feb 18, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Since anagrams do not depend on the ordering of letters then we can sort the letters to get unique representation for a group.
//
// C++:
//		Iterator of unordered_map container point to member type. So key and value can be accessed using 'first' and 'second' members respectively.

typedef vector<string> VS;
typedef vector<VS>     VVS;

VVS FindAnagrams(VS input)
{
	unordered_map<string, VS> sorted_str_to_anagrams;

	for(string s: input)
	{
		// Sort the string and use it as a key and then append the original string as another value into hash table
		string sorted_str(s);
		sort(sorted_str.begin(), sorted_str.end());

		sorted_str_to_anagrams[sorted_str].emplace_back(s);
	}

	VVS result;
	for(auto p: sorted_str_to_anagrams)  // Iterate over the unordered_map
	{
		if(p.second.size() >= 2)   // Found one anagram. Iterator.second point to value
		{
			result.emplace_back(p.second);
		}
	}

	return result;
}


int main()
{
	VS input = {"debitcard", "elvis", "silent", "badcredit", "lives", "freedom", "listen", "levis", "money"};

	VVS anagrams = FindAnagrams(input);

	for(VS group: anagrams) {
		cout << "Group: ";
		for(string s: group) {
			cout << s << ", ";
		}
		cout << endl;
	}
}
