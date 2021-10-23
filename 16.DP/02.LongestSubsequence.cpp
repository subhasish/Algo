/*
 * 02.LongestSubsequence.cpp
 *
 * Problem: Given two strings compute the longest sequence of characters that is a subsequence
 * 			of both the strings.
 *
 *  Created on: Apr 24, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			It is same as minimum Edit distance. In fact it is complimentary of the minimum edit
//			distance problem. Intuitively all the characters that are not part of the
//			longest common subsequence needs an edit.
//			Actually we are optimizing two different things. In minimum edit distance we are
//			minimizing the number of mismatches and here we are maximizing number of matches.
//
//			Looks exact compliments; needs more thought to come to conclusion.
//
//			To find the the string and not the length of the string, we need to store the
//			previous index of the search path (including match/add/replace/delete) for each
//			position that gave it the optimal result.


string LongestCommonSubsequenceDP(const string& str1, const string& str2, int m, int n)
{
	int cache[m+1][n+1];
	pair<int,int> last[m+1][n+1];

	// Base case: when either m or n is 0 the matching has 0 length
	for(int i=0 ; i<=m ; ++i) {
		cache[i][0] = 0;
		last[i][0] = {i-1, 0};
	}
	for(int j=0 ; j<=n ; ++j) {
		cache[0][j] = 0;
		last[0][j] = {0, j-1};
	}

	for(int i=1 ; i<=m ; ++i) { 	// Start with index 1 as 0 is covered in base case
		for(int j=1 ; j<=n ; ++j) {

			// If characters match then count it
			if(str1[i-1] == str2[j-1]) { // NOTE: index of the string to consider are i-1 & j-1
				cache[i][j] = 1 + cache[i-1][j-1];
				last[i][j] = {i-1, j-1};
			}
			// Did not match; consider all possibilities but does not count toward matching
			// but take the best path for mismatch
			else
			{
				if(cache[i-1][j-1] >= cache[i-1][j] && cache[i-1][j-1] >= cache[i][j-1]) {
					last[i][j] = {i-1, j-1};
					cache[i][j] = cache[i-1][j-1];
				} else if(cache[i-1][j] >= cache[i-1][j-1] && cache[i-1][j] >= cache[i][j-1]) {
					last[i][j] = {i-1, j};
					cache[i][j] = cache[i-1][j];
				} else {
					last[i][j] = {i, j-1};
					cache[i][j] = cache[i][j-1];
				}
			}
		}
	}

	cout << "Maximum match length: " << cache[m][n] << endl;
//	for(int i=0 ; i<=m ; ++i) { 	// Start with index 1 as 0 is covered in base case
//		for(int j=0 ; j<=n ; ++j) {
//			cout << cache[i][j] << ", " ;
//		}
//		cout << endl;
//	}


	// Construct the longest common subsequence from the last index
	string subsequence;
	pair<int, int> coord = {m,n};
	while(coord.first > 0 && coord.second > 0) {
		if(str1[coord.first-1] == str2[coord.second-1]) {
			subsequence = str1[coord.first-1] + subsequence;
		}
		coord = last[coord.first][coord.second];
	}

	return subsequence;
}

string LongestCommonSubsequence(const string& str1, const string& str2)
{

	return LongestCommonSubsequenceDP(str1, str2, str1.length(), str2.length());
}

int main()
{
	string str1 = "Saturday";
	string str2 = "Sundays";

	cout << "Longest common subsequence = " << LongestCommonSubsequence(str1, str2) << endl;
}
