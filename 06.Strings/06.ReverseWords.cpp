/*
 * 06.ReverseWords.cpp
 *
 * Problem: Reverse all the words in a string.
 * Ex: "Alice likes Bob" will transform to "Bob likes Alice"
 *
 *  Created on: Oct 8, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

//Trick:
//  Step 1: Reverse the whole sentence. Relative position fix.
//  Step 2: Reverse each words individually
void ReverseWord(string* s)
{
	//First reverse the whole string
	reverse(s->begin(), s->end());

	size_t start=0, end;
	while((end = s->find(" ", start)) != string::npos) {
		// Now reverse each word individually
		reverse(s->begin()+start, s->begin()+end);

		start = end+1;
	}

	//Reverse last word
	reverse(s->begin()+start, s->end());
}

int main()
{
	string s = "Alice likes Bob";
	ReverseWord(&s);
	cout << s << endl;
}


