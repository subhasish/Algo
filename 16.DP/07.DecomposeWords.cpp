/*
 * 07.DecomposeWords.cpp
 *
 * Problem: Given a dictionary and a name design an efficient algorithm that checks whether the
 * 			name is a concatenation of a sequence of dictionary words. Return such concatenation
 * 			if exists. Simpler version would be to return boolean if one exists.
 *
 * 			A dictionary word may appear multiple times.
 *
 *  Created on: May 6, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Classic recursive problem; match a prefix/suffix and apply again for rest of the string.
//			But is solves for same suffix/prefix multiple times. DP can help.
//
//			For simpler boolean version, we need to check for each prefix/suffix whether a
//			sequence is possible. And that would result in final result for full string.
//
//			Unlike searching pattern in grid, here repetition is allowed, so string a single
//			decomposition for each suffix/prefix will work, instead for storing all possibilities.
//
//			If we go by prefix then for each prefix we will check if any word in dictionary
//			would be a suffix of that and if rest of the prefix already has a solution.
//
// Time complexity:
//			For each substring O(n^2), checking whether string is in set is O(n). So total O(n^3).
//			If maximum length of a possible word is W and that is smaller than n then we need not
//			to consider substrings whose length greater than W. In that case complexity would be
//			O(nW^2)

typedef vector<string> VS;

VS DecomposeWord(const string& name, unordered_set<string>& dict)
{
	// DP[i] stores the result vector for prefix name[0..i]
	vector<vector<string>> DP(name.size());

	for(int i=0; i < (int)name.size() ; ++i) {		// For all prefix of string name
		for(int j=i; j>=0 ; --j) {					// For all suffix of the prefix name[0..i]
			string suffix=name.substr(j,i-j+1);

			if(dict.count(suffix) > 0) {
				if(j>0) {
					if(!DP[j-1].empty()) {
						DP[i] = DP[j-1];
						DP[i].emplace_back(suffix);
					}
				} else if(j == 0) {
					DP[i].clear();					// Remember to clear
					DP[i].emplace_back(suffix);
				}
			}
		}
	}


	return DP[name.size()-1];
}

void PrintStrings(VS l)
{
	cout << "List of strings: ";
	for(string& s: l) {
		cout << s << ", ";
	}
	cout << endl;
}

int main()
{
	unordered_set<string> dict = {"a","ant", "an", "anti", "time", "aim"};
	VS res1 = DecomposeWord("aunt", dict);
	VS res2 = DecomposeWord("aimaanti", dict);
	VS res3 = DecomposeWord("anaimany", dict);
	VS res4 = DecomposeWord("ant", dict);

	PrintStrings(res1);
	PrintStrings(res2);
	PrintStrings(res3);
	PrintStrings(res4);
}
