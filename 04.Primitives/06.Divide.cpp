/*
 * 6.Divide.cpp
 *
 * Compute x/y without using arithmetic operator
 *
 *  Created on: Jun 25, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

ULL Divide(ULL x, ULL y)
{
	//Brute force can be to subtract y from x repeatedly.
	//But it would be O(2^n) as it depends on values of x and y
	//Better would be to subtract multiples of y at one go

	ULL result=0;
	int power=32;

	ULL y_power = y << power;
	while(x>=y) { //till we can subtract more from x
		while(y_power > x) { //we want to decrease power until (y << power) less than x
			y_power = y_power >> 1;
			--power;
		}

		result = result + (1ULL << power);
		x = x - y_power;
	}
	return result;
}

int main()
{
	cout << Divide(343637373, 556) << endl;
}


