/*
 * 9.IsPalindromeNumber.cpp
 *
 *	Check if a number is a palindrome
 *
 *  Created on: Jun 27, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

bool IsPalindromeNumber1(int x)
{
	//Number of digits = floor(log10(x))+1
	int numDigits = log10(x)+1;
	int k=1;
	while(numDigits-1 > k)
	{
		int lsb = x%10;
		int msb = x/((int)pow(10, numDigits-1));

		if(lsb != msb)
			return false;

		x = x/10;  // get rid of lsb
		x = x% ((int)pow(10,numDigits-2)); // get rid of msb

		numDigits -= 2;
	}
	return true;
}

bool IsPalindromeNumber2(int x)
{
	if(x<0)
		return false;

	const int num_digits = static_cast<int>(floor(log10(x))+1);
	int msd_mask = static_cast<int>(pow(10, num_digits-1));

	for(int i=0; i<(num_digits/2); ++i)
	{
		if(x/msd_mask != x%10)
			return false;

		x = x % msd_mask; // get rid of msb
		x = x/10; // get rid of lsb
		msd_mask = msd_mask/100;
	}

	return true;
}

int main()
{
	cout << IsPalindromeNumber1(235323) << endl;
	cout << IsPalindromeNumber1(23532) << endl;

	cout << IsPalindromeNumber2(235323) << endl;
	cout << IsPalindromeNumber2(23532) << endl;

}

