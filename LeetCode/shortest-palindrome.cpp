/*
 * shortest-palindrome.cpp
 *
 *  Created on: Jan 23, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;


bool isPalindrome(string& s) {
	for(size_t i=0, j=s.length()-1 ; i<j ; ++i, --j) {
		if(s[i] != s[j]) {
			return false;
		}
	}
	return true;
}
string shortestPalindrome(string s) {
	if (s == "") return "";
	size_t palin = s.length()-1;
	string res;
	res.reserve(s.length()*2);
	while(palin > 0) {
		string sub = s.substr(0, palin+1);
		if(isPalindrome(sub)) {
			break;
		} else {
			res += s[palin];
		}
		--palin;
	}

	res += s;
	return res;
}

int main() {
	cout << shortestPalindrome("aacecaaa") << endl;
	cout << shortestPalindrome("") << endl;
	cout << shortestPalindrome("abcd") << endl;
	cout << shortestPalindrome("a") << endl;
}
