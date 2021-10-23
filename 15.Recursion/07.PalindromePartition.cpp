/*
 * 07.PalindromePartition.cpp
 *
 * Problem: Compute all palindromic decomposition of a given string
 *
 *  Created on: Apr 13, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Brute force is to try all partitioning. n character has (n-1) partitions. Choosing
//			any subset of these gives rise to the power set of the partitions. Exponential.
//
//			We can do better by only going ahead with partitions that result in only palindromes.
//
//			After taking one palindrome prefix, all solution of the suffix need to be considered.
//			Hence point to recursive solution.
//
//			This is kind of enumeration and backtracking strategy will work.
//
// Time complexity:
//			Worst case time complexity is still O(n * 2^n) if input has all same characters.
//			But it does much better when there are few palindrome decomposition.


typedef vector<string> VS;
typedef vector<VS> VVS;

bool IsPalindrome(const string& S)
{
	for(int i=0, j=S.length()-1 ; i<j ; ++i, --j) {
		if(S[i] != S[j]) {
			return false;
		}
	}
	return true;
}

void PalindromePartionHelper(const string& S, int start, VS& partial_result, VVS& result)
{
	if(start >= (int) S.length()) {
		result.emplace_back(partial_result);
		return;
	}

	for(int i = start+1; i <= (int) S.length() ; ++i) {  // The equality to add the result
		string prefix = S.substr(start,i-start);
		if(IsPalindrome(prefix)) {
			partial_result.emplace_back(prefix);
			PalindromePartionHelper(S, i, partial_result, result);
			partial_result.pop_back();	// Back track
		}
	}
}

VVS PalindromePartitions(const string& S)
{
	VVS result;
	VS partial_result;

	PalindromePartionHelper(S, 0, partial_result, result);

	return result;
}

int main()
{
	string S = "020445881";

	VVS result = PalindromePartitions(S);

	for (VS& arr: result) {
		cout << "One partition: ";
		for(string& s: arr) {
			cout << s << ", ";
		}
		cout << endl;
	}

	cout << "Total palindromic partitions: " << result.size() << endl;
}
