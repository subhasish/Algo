/*
 * 00.GCD.cpp
 *
 * Problem: Compute GCD of two numbers
 *
 *  Created on: Mar 31, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Euclidean algorithm for GCD is if y>x then GCD of x and y is the GCD of x and y-x.
//			This will go on until the one of the two numbers become 0
//
//			Time complexity: Each time one of the argument is at least halved. So time complexity
//							 is O(log max(x,y)). In another words, O(n) where n is the number of
//							 bits needed to represent the input.

int GCD(int x, int y)
{
	if(x > y) return GCD(y,x);

	if(x == 0) return y;
	return GCD(x, y%x);
}

int main()
{
	cout << "GCD of 21 and 77 is: " << GCD(77,21) << endl;
	cout << "GCD of 21 and 63 is: " << GCD(63,21) << endl;
	cout << "GCD of 21 and 47 is: " << GCD(47,21) << endl;
}
