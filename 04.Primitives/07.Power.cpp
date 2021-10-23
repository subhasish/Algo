/*
 * 7.Power.cpp
 *
 * Compute x^y without exponentiation operator
 *  Created on: Jun 25, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;


double Power(double x, int y)
{
	//Brute force would be multiply x y-times.
	//Depends on value of y and O(2^n)
	//But more work can be done in one iteration.
	//Ex: instead of x*x*x*x do x^2*x^2

	//If LSB of y is 0 then x^y = (x^(y/2))^2
	//If LSb of y is 1 then x^y = x * (x^(y/2))^2
	double result=1.0;
	int power=y;

	if(y<0){
		power = -power;
		x = 1/x;
	}

	while(power) {
		if(power & 1) {
			// This multiplication as LSB has 1
			result = result * x;
		}

		// This multiplication is as we are dividing power by 2 in the next line
		x = x*x;
		power = power >> 1;
	}
	return result;
}


int main()
{
	cout << Power(444,34) << endl;
}
