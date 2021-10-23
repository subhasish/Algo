/*
 * 05.SquareRootDouble.cpp
 *
 * Problem: Given a floating point number find its square root that is accurate up to some tolerance
 *
 *  Created on: Feb 10, 2018
 *      Author: subha
 */


#include <bits/stdc++.h>

using namespace std;

// Solution: The fundamental difference between integer square root and floating square root is that for numbers
//			 less than 1, the square root can be larger than the number itself.
//           So for that what would be high? Not Float.Max but 1 can be the max.
//
// Time complexity: O(log n/t) where t is the tolerance

// C++:		 Floating point comparison is tricky. Due to machine representation of floating point number there would be precision error.
//			 To tackle that we need to see if numbers are too close to be equal. We would compare the difference with epsilon.
//
//           The comparison with epsilon has to be relative as the difference between two nearest floating point number change with
//           the magnitude of the numbers. The epsilon constant provided by the language represent smallest tolerance between 1 and 2.

typedef enum {SMALLER, EQUAL, LARGER} Ordering;

// Note: It does not work when one number is 0.
Ordering CompareDouble(double a, double b) {
	double max = a > b ? a : b;
	double diff = a - b;

	diff = diff / max; // Relative to handle precision error of epsilon
					   // NOTE: that it does not work with one number being 0, Then this division will result in either 1 or -1.
	                   // So even if how close the number gets, the diff variable will never be less than epsilon

	if (fabs(diff) < numeric_limits<double>::epsilon()) {
		return EQUAL;
	} else if(a < b) {
		return SMALLER;
	} else {
		return LARGER;
	}
}

double SquareRoot(double number) {
	double lo, hi;

	if(number < 0) return -1;
	if(number == 0) return 0;

	if(number > 1) {
		lo = 1; hi = number;
	} else {
		lo = 0; hi = 1;   // For number smaller than 1
	}

	// Be careful about making epsilon relative to what we are operating with
	while(CompareDouble(lo, hi) == SMALLER) {
		double mid = lo + (hi - lo + (numeric_limits<double>::epsilon() * (hi-lo))) / 2;  // move towards hi
		double sq = mid * mid;
		if(CompareDouble(sq, number) == SMALLER) {
			lo = mid;
		} else {
			hi = mid - (numeric_limits<double>::epsilon() * mid);
		}
	}

	return lo;
}


int main()
{
	cout << "Square root of 25.36346 = " << SquareRoot(25.36346) << endl;
	cout << "Square root of 0.36346 = " << SquareRoot(0.36346) << endl;
	cout << "Square root of 1 = " << SquareRoot(1) << endl;
	cout << "Square root of 100 = " << SquareRoot(100) << endl;
	cout << "Square root of 0 = " << SquareRoot(0) << endl;
}

