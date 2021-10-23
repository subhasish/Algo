/*
 * 10.GrayCode.cpp
 *
 * Problem: A n-bit gray code is a permutation of {0, 1, 2, .., 2^n - 1} such that binary
 *			representation of successive integers in the sequence differ in only one place.
 *			The first and last should also differ in only one place.
 *
 *			Write a program that generates n-bit Gray code.
 *
 *  Created on: Apr 16, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			It is a possibility that the Gray code for (n-1) bit will help in building Gray
//			code of n bits. Doing simple case analysis of n=2,3 helps to find the rule.
//
//			For n=2, one code is {00, 01, 11, 10}. Now if we add 0 and 1 as prefix to these
// 			and append then they do not form Gray code as 010 and 100 differ in two positions,
//			as well as first 000 and last 110.
//
//			One observation is that, to make differ in only one position 010 should be followed
//			by 110. So if we reverse the sequence and prefix 1 with each of them and then append
//			then it would result in Gray code.
//
// Time complexity:
//			T(n) = T(n-1) + O(2^n - 1) = O(2^n)
//
// C++:
//			Printing integer in binary format: bitset<32>(i)


typedef vector<int> VI;

VI GrayCode(int n)
{
	if(n == 0) {
		return {0};
	}
	if(n == 1) {
		return {0, 1};
	}

	VI res_n_1 = GrayCode(n-1);
	VI result = res_n_1;

	// Now mask 1 at n th bit position
	int leading_bit = 1 << (n-1);
	for(int i = (int) res_n_1.size()-1; i >= 0 ; --i) {
		result.emplace_back(leading_bit | res_n_1[i]);
	}

	return result;
}


int main()
{
	VI result = GrayCode(5);

	for(int i: result) {
		cout << "Code: " << bitset<5>(i) << endl;

	}
	cout << endl;
}
