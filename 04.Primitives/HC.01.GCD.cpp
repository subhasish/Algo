/*
 * HC.01.GCD.cpp
 *
 * Problem: Design an efficient algorithm to compute the GCD (greatest common divisor) of
 * 			two numbers without using multiplication, division, and modulo operation.
 *
 *  Created on: Oct 23, 2018
 *      Author: subha
 */

// Solution:
//			Straightforward algorithm is based on recursion. If x==y, then GCD(x,y)=x,
//			otherwise assuming x>y, GCD(x,y)=GCD(x-y,y)
//			This is very slow, for example if x=2^n and y=2 then this will make 2^(n-1)
//			recursive calls.
//			It can be improved by repeated subtraction of y from x unless (x-y) becomes
//			less than x. But time complexity still in the order of the magnitude of x and y.
//
//			A fast solution comes from the observation of two facts:
//				1. If x and y are even then GCD(x,y) = GCD(x/2,y/2) * 2
//				2. If x is even but y is not then GCD(x,y) = GCD(x/2,y)
//			Division can be done by bit shifting and even checking can be done by bit manipulation.
//			Here we are repetitively reduce the combined bit length of the two numbers.
//			So time complexity is T(log x + log y)

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL GCD(LL x, LL y)
{
	//cout << x << ", " << y << endl;

	if(x<y) {
		return GCD(y,x);
	}
	else if(x == y) {
		return x;
	} else if (y == 0) {
		return x;
	}
	//x>y
	else if(!(x&1) && !(y&1)) {
		return (GCD((x>>1), (y>>1)) << 1);
	} else if(!(x&1) && (y&1)) {
		return GCD((x>>1),y);
	} else if((x&1) && !(y&1)) {
		return GCD(x,(y>>1));
	}

	//both are odd
	return GCD(x-y,y);
}


int main()
{
	cout << GCD(21,49) << endl;
	cout << GCD(1241525262,2) << endl;
	cout << GCD(97,11) << endl;
}
