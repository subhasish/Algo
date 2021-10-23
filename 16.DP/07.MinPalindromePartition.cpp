/*
 * 07.MinPalindromePartition.cpp
 *
 * Problem: Earlier we have seen finding all possible palindromic partitioning in
 * 			Recursion/07.PalindromePartition.cpp. One of them is minimum decomposition
 * 			that has the minimum number of palindromes in result.
 *
 * 			How to find the minimum decomposition given a string?
 *
 *  Created on: May 7, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			It is clear that having optimal solution for string [0..n-1] may not give the
//			optimal solution for string [0..n]. So we need to consider all possible decompositions.
//
//			So if we have all solution ready for all possible for prefix/suffix then an iteration
//			can grow the solution for next character. So it is another variant of decomposing
//			string in to dictionary keywords.
//
// Time complexity:
//			O(n^3) same as decompose word.


typedef vector<string> VS;

bool IsPalindrome(const string& S)
{
	for(int i=0, j=S.length()-1 ; i<j ; ++i, --j) {
		if(S[i] != S[j]) {
			return false;
		}
	}
	return true;
}

VS DecomposeMinimumPalindrome(const string& name)
{
	// DP[i] stores the result vector for prefix name[0..i]
	vector<vector<string>> DP(name.size());

	for(int i=0; i < (int)name.size() ; ++i) {		// For all prefix of string name
		size_t min_length = numeric_limits<size_t>::max();

		for(int j=i; j>=0 ; --j) {					// For all suffix of the prefix name[0..i]
			string suffix = name.substr(j,i-j+1);

			if(IsPalindrome(suffix)) {
				if(j>0 && (!DP[j-1].empty()) && (DP[j-1].size() < min_length)) {
					min_length = DP[j-1].size();
					DP[i] = DP[j-1];
					DP[i].emplace_back(suffix);
				}
				else if(j==0) {
					DP[i].clear();		// Remember to clear
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
	VS res1 = DecomposeMinimumPalindrome("aunt");
	VS res2 = DecomposeMinimumPalindrome("0204451881");

	PrintStrings(res1);
	PrintStrings(res2);
}
