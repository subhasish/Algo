/*
 * 8.ReverseInt.cpp
 *
 * Given an integer return integer with digitsin reverse order
 *  Created on: Jun 27, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

int ReverseInt(int x)
{
	int result= 0;
	bool isNegative = false;
	if(x<0) {
		isNegative = true;
		x= -x;
	}

	//Take one digit from lsb. Add that to result.
	//At each iteration multiply 10 with existing result
	while(x) {
		int lsb = x%10;
		result = result*10 + lsb;
		x = x/10;
	}

	if(isNegative)
		result = -result;

	return result;
}

int main()
{
	cout << ReverseInt(34456) << endl;
	cout << ReverseInt(-3456) << endl;
}


