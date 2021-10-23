/*
 * 05.IsPalindrome.cpp
 *
 * Problem: Test if a string is a palindrome, ignoring the non-alphanumeric characters and case of a character
 *
 *  Created on: Oct 8, 2017
 *      Author: subha
 */

#include<bits/stdc++.h>

using namespace std;

bool IsPalindrome(string str)
{
	int i=0, j=str.size()-1;

	while(i<j) {
		if(!isalnum(str[i])) {
			++i; continue;
		}
		if(!isalnum(str[j])) {
			--j; continue;
		}

		if(tolower(str[i]) != tolower(str[j]))
			return false;

		++i; --j;
	}
	return true;
}

int main()
{
	cout << IsPalindrome("A man, a plan, a canal, Panama.") << endl;
	cout << IsPalindrome("Ray a Ray") << endl;
}



