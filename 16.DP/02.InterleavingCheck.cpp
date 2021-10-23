/*
 * 02.InterleavingCheck.cpp
 *
 * Problem:
 * 			A string t can be defined as interleaving of two string s1 and s2, if there is an way
 * 			to interleave the characters of s1 and s2 keeping the left-to-right order of each,
 * 			to obtain t. Design an algorithm that takes s1, s2 and t and determines if t is
 * 			interleaving of s1 and s2.
 *
 *  Created on: Apr 28, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Variant of minimum edit distance problem. String matching; can be done from one end.
//
//			The first/last character of t has to match with either of the two strings. Otherwise no
//			solution is possible. If matches with both then need to consider both the possibilities.
//
//			Similar to minimum edit distance problem the problem can have 3 parameters where
//			DP(x,a,b) would represent solution of t[0,x-1], s1[0,a-1] and s2[0,b-1]. There would be
//			difference of 1 between the index of 3D DP array and index of strings to account for
//			empty string in index 0.

bool InterleavingCheck(const string& t, const string& s1, const string& s2, int x, int a, int b)
{
	// DP[k][i][j] correspond to solution of t[0,k-1], s1[0,i-1] and s2[0,j-1]
	// So that index 0s in DP array correspond to empty strings
	bool DP[x+1][a+1][b+1];

	// Base cases
	for(int i=0; i<=a ; ++i) {
		for(int j=0 ; j<=b ; ++j) {
			DP[0][i][j] = false;	// Empty t cannot be formed from non empty strings
		}
	}
	DP[0][0][0] = true; 			// Everything is empty

	for(int k=1; k<=x ; ++k) {
		for(int i=1 ; i<=a ; ++i) {
			for(int j=1 ; j<=b ; ++j) {

				//If there is length mismatch then it is not feasible
				if(i + j != k) {
					DP[k][i][j] = false;
					continue;
				}

				// Check if last characters match
				if(t[k-1] == s1[i-1] || t[k-1] == s2[j-1]) {
					bool m1=false, m2=false;
					if(t[k-1] == s1[i-1]) {
						m1 = DP[k-1][i-1][j];
					}
					if(t[k-1] == s2[j-1]) {
						m2 = DP[k-1][i][j-1];
					}
					DP[k][i][j] = (m1 || m2);		// True if either matches
				} else {
					DP[k][i][j] = false;			// False if neither matches
				}

			}
		}
	}

	return DP[x][a][b];
}


int main()
{
	string s1 = "gtaa";
	string s2 = "atc";

	string t  = "gattaca";
	cout << InterleavingCheck(t, s1, s2, t.length(), s1.length(), s2.length()) << endl;

	t  = "gatacta";
	cout << InterleavingCheck(t, s1, s2, t.length(), s1.length(), s2.length()) << endl;
}
