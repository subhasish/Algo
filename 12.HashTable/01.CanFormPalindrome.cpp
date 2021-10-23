/*
 * 01.CanFormPalindrome.cpp
 *
 * Problem: Given a string test whether a palindrome can be formed by permuting the letters of the string.
 *
 *  Created on: Feb 20, 2018
 *      Author: subha
 */

#include<bits/stdc++.h>

using namespace std;

// Solution: All the characters except one has to be of even number.
//
//			 Alternative solution could use set. That keep on adding and removing elements. Ultimately size of set should be less than 2.

bool CanFormPalindrome(string str)
{
	unordered_map<char, int> char_to_count;
	for(char c: str) {
		++char_to_count[c];
	}

	int number_of_odd = 0;
	for(auto pair: char_to_count)
	{
		if(pair.second % 2 != 0)
		{
			++number_of_odd;
		}
		if(number_of_odd > 1)
		{
			return false;
		}
	}

	return true;
}

int main()
{
	cout << CanFormPalindrome("level") << endl;
	cout << CanFormPalindrome("foobaraboof") << endl;
	cout << CanFormPalindrome("rotator") << endl;
	cout << CanFormPalindrome("leveler") << endl;
}
