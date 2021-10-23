/*
 * 02.AnonymousLetter.cpp
 *
 * Problem: Write a program that takes text of a anonymous letter and a magazine and determines
 * 			whether it is possible to write that letter using the letters from the magazine.
 *
 * 			Ignore whitespace??
 *
 *  Created on: Feb 20, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Form a map of counts of letters in the letter. Magazine is supposed to have more letters, so traverse letter first.
//			 Then decrement count as we see a character in magazine.

bool IsAnonymousLetterPossible(string letter, string magazine)
{
	unordered_map<char, int> char_count;

	for(char c: letter)
	{
		++char_count[c];
	}

	for(char c: magazine)
	{
		auto it = char_count.find(c);
		if(it != char_count.end())
		{
			--it->second;
			if(it->second == 0) {
				char_count.erase(it);
			}
		}

		if(char_count.empty())
		{
			// All characters matched
			break;
		}
	}

	return char_count.empty();
}


int main()
{
	cout << IsAnonymousLetterPossible("abc def", "gowa eggb ceyk dfewg") << endl;
	cout << IsAnonymousLetterPossible("abc def", "gowa eggb ceyk dewg") << endl;
}
