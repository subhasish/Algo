/*
 * 02.MinEditDistance.cpp
 *
 * Problem: Write a program that takes two strings and compute the minimum number of edits needed
 * 			to transform one string to another. Either insert/delete/replace can be thought as
 * 			one edit.
 *
 * 			This can be used to compute similarity between two strings.
 *
 * 			Variant 1:
 * 			In DP solution use O(min(m,n)) space
 *
 * 			Variant 2:
 * 			Longest matching subsequence
 *
 * 			Variant 3:
 * 			Given a string compute the minimum number of characters to delete to make it a
 * 			palindrome
 *
 *			Variant 4:
 *			Given a string A and a regular expression r, what is the string in the language of the
 *			regular expression r that is the closest to A.
 *
 * 			Variant 5:
 * 			Check string t can be made by interleaving two strings s1 and s2
 *
 *  Created on: Apr 23, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Brute force is to compute all strings that are at 1,2,3 distance from string 1 and see
//			if it matches string 2. Worst case exponential; from n 0s to n 1s it would explore
//			at least all 2^n possible strings.
//
//			It is clear that problem is that we need to consider all possible lining ups. If there
//			two 'b's in one string and one 'b' in another string, we need to consider with which
//			'b' to line it up with also in optimal solution neither of the 'b's could line up,
//			due to other matches in the strings!!
//
//			Systematic way to align two strings and check for each possible interleaving would be
//			to start from one end of two strings and consider all possibilities.
//
//			One interesting observation is that if two characters at an end match then we can line
//			them up and consider rest of the strings. They can always be made part of optimal
//			solution.
//
//			If they do not match then we need at least one edit. But the edit can be either insert,
//			delete or replace on either of the strings. Either of the three could give optimal
//			solution. So we need to consider these three possibilities.
//
//			DP would be great way to solve this recurrence relation. In order to systematically
//			consider portions of the string from one side we can start from end. So that left index
//			is always 0 and only right index would need to be parameterized. So the two parameters
//			m and n in DP(m,n) would correspond to last index of the two strings. Both top-down and
//			bottom-up should work.
//
//			To store the result for empty string in the array we can start indexing from 1 and
//			0th index would represent empty string. So DP(m,n) would have optimal solution of
//			Str1[0,m-1] and Str2[0,n-1]. Note the difference of 1 between 2D array and string index.
//
//			Base case would be DP(m,n) = m or n when other one is 0.
//
//			For bottom-up time and space complexity will be O(mn) as we fill up the 2D array.
//
// Variant 1:
//			We look back up to last row/column. So all previous rows/columns are not needed.
//			So the space can be reused as we did in coin change problem.
//
// Variant 2:
//			Longest common subsequence is solved differently.
//
// Variant 3:
//			If character at both end match then we can safely include them in the palindrome.
//			Otherwise we need to look at the either possibilities.
//			Need to populate 2D array where DP[i][j] is solution of string from i to j.
//			Base case DP[i][i] = 0 for all i. Top down would seems easier than bottom up.
//			For bottom up we first loop has to be based on length rather than start index, and
//			second loop can be of the start index.
//
// Variant 4:
//			TODO: regular expression matching.
//
// Variant 5:
//			Interleaving check will be done separately.


int MinEditDistanceDP(const string& str1, const string str2, int m, int n)
{
	// Table to store the results of subproblems.
	// cache[i][j] stores the result of minimum edit for strings str1[0,i-1] and str2[0,j-1]
	// so that 0th index counts for empty string
	int cache[m+1][n+1];

	// Base cases: When one string is empty, edit in other is equal their length
	for(int i=0; i<=m ; ++i) {
		cache[i][0] = i;
	}
	for(int j=0 ; j<=n ; ++j) {
		cache[0][j] = j;
	}

	for(int i=1; i<=m ; ++i) {		// Start from index 1 as 0 is base case; already handled
		for(int j=1 ; j<=n ; ++j) {

			// If last characters are same, ignore them and recurse on remaining strings
			if(str1[i-1] == str2[j-1]) {	// NOTE: index of the string to consider are i-1 & j-1
				cache[i][j] = cache[i-1][j-1];
			}
			else
			{
				// Consider all possibilities and take minimum
				cache[i][j] = 1 + min(cache[i-1][j], min(cache[i][j-1], cache[i-1][j-1]));
			}
		}
	}

	return cache[m][n];
}

int MinEditDistance(const string& str1, const string& str2)
{
	// Pass last index + 1 for each string so that index 0 can correspond to empty string
	return MinEditDistanceDP(str1, str2, str1.length(), str2.length());
}


int main()
{
	string str1 = "s";
	string str2 = "t";

	cout << MinEditDistance(str1, str2) << endl;

	str1 = "Sundays";
	str2 = "Saturday";

	cout << MinEditDistance(str1, str2) << endl;

}
