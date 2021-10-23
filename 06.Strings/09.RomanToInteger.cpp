/*
 * 09.RomanToInteger.cpp
 *
 * Problem: Convert a Roman numeral to its integer form. Assume it is a valid literal.
 *
 * Roman number: I(1), V(5), X(10), L(50), C(100), D(500), M(1000)
 * 				 Symbols appear in non-increasing order, with some exceptions.
 * 				 Exceptions: I can immediately precede V and X.
 * 				             X can immediately precede L and C.
 * 				             C can immediately precede D and M.
 * 				 There can be multiple representation of the same number:
 * 				 	XXXXXIIIIIIIII, LVIIII, LIX all are valid representation of 59.
 *
 *  Created on: Oct 10, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

map<char, int> roman = {
		{'I', 1},
		{'V', 5},
		{'X', 10},
		{'L', 50},
		{'C', 100},
		{'D', 500},
		{'M', 1000},
};

// Once number is in increasing form we will have to subtract the previous one
// So better to start from the back so that we never have to backtrack
int RomanToInteger(string str)
{
	int result=roman[str.back()];
	for(int i=str.length()-2; i>=0 ; i--) {
		if(roman[str[i]] < roman[str[i+1]]) {
			result -= roman[str[i]];
		} else {
			result += roman[str[i]];
		}
	}
	return result;
}

int main()
{
	cout << RomanToInteger("LIX") << endl;
	cout << RomanToInteger("LVIIII") << endl;
	cout << RomanToInteger("XXXXXIIIIIIIII") << endl;

}


