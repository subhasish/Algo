/*
 * 06.BalancedParentheses.cpp
 *
 * Program: Write a program that takes as input a number and returns all the strings
 * 			with that number of matched pairs of parentheses.
 *
 *  Created on: Apr 9, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Brute force approach is to populate all strings of length 2k and see if braces match.
//			This gives 2^2k possibilities. Even if we restrict to strings to equal number of
//			left and right parenthesis, there are (2k C k) string to consider. Almost same.
//			But some strings should never be considered like the one starting with ')'.
//
//			Strings of n pairs of parentheses can be formed from all strings of (n-1) pairs.
//			This tells that it is possible to do using recursion.
//			The main problem with this approach is that we can generate duplicates and we need some
//			other mechanism like hash table to avoid that.
//
//			We can improve the running time greatly as well as avoid the duplicate issue by taking
//			more directed approach.
//			Note that if try to generate the string directly then also there is two possibilities
//			at each step, i.e., add either '(' or ')'. With only one constraint that number of
//			left parenthesis should be greater than number of right parenthesis.
//
// Time complexity:
//			Total such combinations is Catalan number , i.e., 1/(2n+1) * (2n C n).
//			But I guess this approach is taking O(2^2k) time as it is basically trying out 2
//			possibilities for each position.


typedef vector<string> VS;

void GenerateBalancedParenthesesHelper(int k, int left_remain, int right_remain, string partial, VS& result)
{
	if(right_remain == 0) {
		result.emplace_back(partial);
		return;
	}

	if(left_remain>0) {
		GenerateBalancedParenthesesHelper(k, left_remain-1, right_remain, partial+"(", result);
	}

	if(right_remain > left_remain) {
		GenerateBalancedParenthesesHelper(k, left_remain, right_remain-1, partial+")", result);
	}
}
VS GenerateBalancedParentheses(int k)
{
	VS result;
	GenerateBalancedParenthesesHelper(k,k,k,"",result);
	return result;
}

int main()
{
	VS result = GenerateBalancedParentheses(5);

	for(string s: result) {
		cout << "One match: " << s << endl;
	}

	cout << "Total number of such matching braces: " << result.size() << endl;
}
