/*
 * 13.KMP.cpp
 *
 * Problem: To find first occurrence of a pattern in a text.
 *
 * There are 3 famous solutions for this, viz. KMP, Boyer-Moore and Rabin-Karp.
 * We will implement KMP (Knuth-Morris-Pratt) here.
 *
 * ASSUME: All in lower case. Alphabet size 26. **No space in the text or pattern
 *
 *  Created on: Oct 15, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Basic idea:
//   1. When a mismatch occurs, text matched until current char. So we know the text until now. So we can potentially avoid backing up in text.
//   2. For mismatch we want to skip one character in text in then try to match it again. That means we are trying to match with pat[1..j-1] followed by current char
//   3. So we can construct a DFA of the pattern and detect the next character in pattern to match in case of mismatch without backing up in text

int **DFA;
int Base;

int KeyFromChar(char c) {
	if(!isalpha(c))
		throw string("Character '") + c + string("' not in alphabet!!");
	return tolower(c) - 'a';
}

// DFA construction:
//   Definition: DFA[c][j] = State to go from state j on reading character c
//   1. State number = number of characters matched
//   2. At state i, for the mismatch of char c the machine would go the same state where it would have gone from with pattern[1..i-1]+c
//   3. This transition would be already computed and we can copy that result
//   4. Avoid simulation of pattern[1..i-1] each time:
//      Maintain a state X for pattern[1..i-1] and take its transitions to find mismatch transition from state i
void ConstructDFAforKMP(string pattern)
{
	const int M = pattern.length();
	DFA = new int*[Base];

	//Initialize the DFA, including transitions from 1st state
	for(int i=0; i<Base ; ++i) {
		DFA[i] = new int[M]();
		//fill_n(DFA[i],M,22);
	}
	DFA[KeyFromChar(pattern[0])][0] = 1;
	int X = 0;

	//Now take care of state 1, X is in state 0 as expected
	for(int j=1; j<M ; ++j) {
		//Copy all mismatch transitions from state X
		for(int i=0; i<Base ; ++i) {
			DFA[i][j] = DFA[i][X];
		}

		//Now overwrite/fix the matching transition
		DFA[KeyFromChar(pattern[j])][j] = j+1;

		//Update X, where machine would go from X when pattern[j] is found
		X = DFA[KeyFromChar(pattern[j])][X];
	}
}

void PrintDFA(int M)
{
	cout << "DFA: " << endl;
	for(int i=0; i<Base; ++i) {
		for(int j=0; j<M ; ++j) {
			cout << DFA[i][j] << " ";
		}
		cout << endl;
	}
}

// Implementation:
//   If in state j and reads character c
//     if j is last/halt state then stop and accept
//     else move to state DFA[c][j]

// Returns index for first character if match, string::npos otherwise
size_t KMP(string text, string pattern)
{
	size_t i=0; // iterate over text never backs up
	size_t j=0; // goes back and forth over pattern based on DFA
	int M=pattern.length();

	for(; i< text.length() && j<pattern.length() ; ++i) {
		j = DFA[KeyFromChar(text[i])][j];
	}

	if(j == pattern.length())
		return i-M;
	else
		return string::npos;
}

int main()
{
	Base = 26;
	size_t pos = string::npos;
	string text="aa bacaababacaa";//"this is string search problem";
	string pattern = "ababac";//"search";


	try {
		ConstructDFAforKMP(pattern);
		//PrintDFA(pattern.length());

		pos = KMP(text, pattern);
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


}


