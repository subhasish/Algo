/*
 * 01.IntToString.cpp
 *
 *  Problem: Convert a integer to a string and vice versa.
 *           Assume non-negative numbers
 *
 *  Created on: Oct 8, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Can compute from MSB using number of digits
// Otherwise we had to do the reverse of the strings populated
// NOTE: We always do not want to insert in the beginning of the string
//       As that would cause shifting of the subsequent characters
string IntToString(int n) {
	int numDigits = floor(log10(n)) +1;
	int divisor = pow(10, numDigits);
	divisor /= 10;
	string res = "";

	for(int i=numDigits; i>0 ; i--) {
		int digit = n / divisor;

		res.push_back('0'+digit);

		n = n % divisor;
		divisor = divisor/10;
	}

	return res;
}

int StringToInt(string str) {
	int res=0;
	for(unsigned int i=0; i<str.length() ; i++) {
		res = res*10 + (str[i] - '0');
	}
	return res;
}

int main()
{
	cout << IntToString(12345) << endl;
	cout << StringToInt("12345") << endl;
}


