/*
 * 13.BoyerMoore.cpp
 *
 * Problem: To find first occurrence of a pattern in a text.
 *
 * There are 3 famous solutions for this, viz. KMP, Boyer-Moore and Rabin-Karp.
 * We will implement Boyer-Moore here.
 *
 * ASSUME: All in lower case. Alphabet size 26. **No space in the text or pattern
 *
 *  Created on: Oct 20, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

int KeyFromChar(char c) {
	if(!isalpha(c))
		throw string("Character '") + c + string("' not in alphabet!!");
	return tolower(c) - 'a';
}

int Base;
int *Right;
/*
 * Basic idea:
 * 	1. Can skip many characters if we match from end of pattern and find a character in text that does not exists in pattern.
 * 	2. And if we find a char that is in pattern then align it with the rightmost occurrence of it in pattern,
 * 	   as we do not want to miss out any while matching right to left
 * 	3. Edge case: do not back up while doing step 2
 *
 * Algorithm:
 * 	1. Precompute rightmost index of each character. -1 if not in pattern
 * 	2. Try to match pattern from right to left.
 * 		If mismatch occurs then skip K number of characters. Compute K programmatically as follows
 * 			- If mismatch char not in pattern then start to match from end of current match
 * 			- If in pattern, then try to match rightmost occurrence of the char, but do not backup. So at minimum skip by 1
 */
void PopulateRightMostIndex(string pattern)
{
	size_t M = pattern.length();
	Right = new int[Base];

	for(int i=0; i<Base ; ++i) {
		Right[Base] = -1;
	}

	for(size_t i=0; i<M ; ++i) {
		Right[KeyFromChar(pattern[i])] = i;
	}
}

size_t BoyerMoore(string text, string pattern)
{
	size_t N = text.length();
	size_t M = pattern.length();
	int skip;

	for(unsigned int i=0; i<=N-M ; i=i+skip) {  // NOTE: i incremented by skip
		skip = 0;  								// programmatically find value of skip
		for(int j=M-1; j>=0 ; --j) {
			if(pattern[j] != text[i+j]) {
				skip = max(1, j - Right[KeyFromChar(text[i+j])]);
				break;
			}
		}
		if(skip == 0)  // match
			return i;
	}
	return string::npos;
}

int main()
{
	Base = 26;
	size_t pos = string::npos;
	string text="aabacaababacaa";//"this is string search problem";
	string pattern = "ababac";//"search";


	try {
		PopulateRightMostIndex(pattern);

		pos = BoyerMoore(text, pattern);
	}
	catch (string& message)
	{
		cout << message << endl;
	}

	if(pos == string::npos) {
		cout << "Pattern not found!!" << endl;
	} else {
		cout << "Pattern found at position " << pos << endl;
	}

	return 0;
}


