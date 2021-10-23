/*
 * 04.SquareRootInt.cpp
 *
 * Problem: Given a non-negative integer return the largest integer whose square is less than or equal to the given integer
 *
 *  Created on: Feb 9, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: It is the second case of binary search where we need to find the last element for which predicate is false,
//           given an array of consecutive false followed by consecutive trues.
//           Here the predicate would be: square greater than given number

int SquareRoot(int number)
{
	if(number < 0)
		return -1;

	int lo = 0, hi = number;

	while(lo < hi) {
		int mid = lo + (hi - lo + 1) / 2;

		if(mid*mid <= number) {
			lo = mid;
		} else {
			hi = mid - 1;
		}
	}

	//Search reduced to single number
	return lo;
}


int main()
{
	cout << "Square root of 36 is: " << SquareRoot(36) << endl;
	cout << "Square root of 76 is: " << SquareRoot(76) << endl;
	cout << "Square root of 35 is: " << SquareRoot(35) << endl;
	cout << "Square root of 0 is: " << SquareRoot(0) << endl;
	cout << "Square root of 1 is: " << SquareRoot(1) << endl;
	cout << "Square root of -36 is: " << SquareRoot(-36) << endl;
}
