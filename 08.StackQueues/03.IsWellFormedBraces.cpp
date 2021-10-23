/*
 * 03.IsWellFormedBraces.cpp
 *
 * Problem: Given a list of consecutive braces, tell whether they are well formed.
 *
 *  Created on: Jan 2, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Classis case of LIFO and hence stack

bool IsWellFormedBraces(string s)
{
	stack<char> leftChars;

	map<char,char> kLookup = {
			{'(',')'}, {'{', '}'}, {'[',']'}
	};

	for(unsigned int i=0; i<s.size() ; ++i) {
		if(kLookup.count(s[i])) {
			leftChars.push(s[i]);
		} else {
			if(leftChars.empty() || kLookup[leftChars.top()] != s[i]) {
				return false;
			}
			leftChars.pop();
		}
	}

	return true;
}

int main() {
	cout << "(()[]) = " << IsWellFormedBraces("(()[])") << endl;
	cout << "(()][) = " << IsWellFormedBraces("(()][)") << endl;

}
