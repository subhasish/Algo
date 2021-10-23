/*
 * HC.26.RegexMatching.cpp
 *
 * Problem: Design an algorithm that takes a regular expression and a string, and checks if the
 * 			regular expression (RE) matches the string.
 *
 *  Created on: Dec 26, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			The key insight is that regular expression (RE) is defined recursively. This suggests that
//			we use recursion to do the matching.
//
//			Matching can be done by looping over starting offset. And then logic takes care of the
//			ending offset while trying to match substring.
//
//			The following cases need to be handled:
//				1. length-0 RE: return true immediately
//				2. RE starting with ^ or ending with $: Single match with starting of the string or
//							some checking for ending with $.
//				3. RE starting with * match, e.g., a* or .*: check prefix of the string matches with
//							zero or more occurrences of the character or dot(any) until some
//							suffix matches the remainder of the expression.
//				4. RE starting with a character or a dot: involves examining the character and matching
//							of the suffix.
//
// Complexity:
//			At each step we need to explore all possibilities. So exponential.

bool IsRegexMatchHere(const string& regex, size_t regex_offset, const string& s, size_t s_offset);

bool IsRegexMatch(const string& regex, const string s) {
	if(regex[0] == '^') {			// Case 2: starting with ^
		return IsRegexMatchHere(regex, 1, s, 0);
	} else {
		for(size_t i=0; i<s.size() ; ++i) {
			if(IsRegexMatchHere(regex, 0, s, i)) {
				return true;
			}
		}
	}
	return false;
}

bool IsRegexMatchHere(const string& regex, size_t regex_offset, const string& s, size_t s_offset) {

	if(regex_offset == regex.size()) {	// Case 1: empty regex matches all string
		return true;
	}

	if(regex_offset == regex.size()-1 && regex[regex_offset] == '$') {
										// Case 2: end with $
		return s_offset == s.size();
	}

	if(regex_offset < regex.size()-1 && regex[regex_offset+1] == '*') {
										// Case 3: * following a character of dot
		if(regex[regex_offset] == '.') {
			for(size_t i=s_offset ; i<s.size() ; ++i) {
				if(IsRegexMatchHere(regex, regex_offset+2, s, i)) {
					return true;
				}
			}
		} else {
			// consider 0 matching case
			if(IsRegexMatchHere(regex, regex_offset+2, s, s_offset)) {
				return true;
			}
			// consider non-zero matching case
			for(size_t i=s_offset ; i<s.size() ; ++i) {
				if(regex[regex_offset] != s[i]) {
					break;
				} else {
					if(IsRegexMatchHere(regex, regex_offset+2, s, i+1)) {
						return true;
					}
				}
			}
		}
	} else {
										// Case 4: regex beginning with single character
		if(s_offset < s.size() && (regex[regex_offset] == '.' || regex[regex_offset] == s[s_offset])) {
			return IsRegexMatchHere(regex, regex_offset+1, s, s_offset+1);
		}
	}

	return false;
}


int main() {
	string r1 = "aW*9";
	string s11 = "ab8aWWW9W9aa";
	string s12 = "aXW9Wa";

	cout <<"regex -" << r1 << "- match string -" << s11 << "- : " << IsRegexMatch(r1, s11) << endl;
	cout <<"regex -" << r1 << "- match string -" << s12 << "- : " << IsRegexMatch(r1, s12) << endl;

	string r2 = "aW.9$";
	string s21 = "aWW9abcaWz9";
	string s22 = "aWcc90";

	cout <<"regex -" << r2 << "- match string -" << s21 << "- : " << IsRegexMatch(r2, s21) << endl;
	cout <<"regex -" << r2 << "- match string -" << s22 << "- : " << IsRegexMatch(r2, s22) << endl;

}
