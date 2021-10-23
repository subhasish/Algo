/*
 * 07.PhoneMnemonic.cpp
 *
 *  Problem: Each digit, other than 0 and 1, in phone keypad correspond to 3 to 4 characters.
 *           So each phone number will correspond to multiple words.
 *           Given a phone number return list of all the words.
 *
 *  Created on: Oct 8, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<string> VS;

const int numDigits = 10;

// mapping from digit to corresponding characters
const VS mapping = {
		"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"
};

void PhoneMenmonicRecurse(const string phNum, string* partialResult, unsigned int nextIndex, VS* mnemonicList)
{
	if(nextIndex >= phNum.size()) // Base case: add to the result
	{
		mnemonicList->emplace_back(*partialResult);
	}
	else
	{
		// Loop to add all characters
		for(char c: mapping[phNum[nextIndex] - '0']) {
			// Add another character
			(*partialResult)[nextIndex] = c;
			// Recurse to add next characters
			PhoneMenmonicRecurse(phNum, partialResult, nextIndex+1, mnemonicList);
		}
	}
}

// In general such enumeration best work with recursion.
//   Each step will pass the partial result.
//   Base case will add to the result.
VS PhoneMnemonic(const string phNum)
{
	string partial_mnemonic(phNum.size(), 0);
	VS mnemomicList;
	PhoneMenmonicRecurse(phNum,&partial_mnemonic,0,&mnemomicList);
	return mnemomicList;
}

int main()
{
	VS resultArr = PhoneMnemonic("23");
	for(string s: resultArr) {
		cout << s << endl;
	}
}


