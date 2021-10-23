/*
 * 07.EnumerateSmallest.cpp
 *
 * Problem: Design an algorithm for efficiently computing the k smallest numbers of the form
 * 			(a + b * root(2)) for nonnegative integers a and b.
 *
 * 			In general, this same algorithm should be applied to any monotonic function of 2 inputs.
 *
 *  Created on: Mar 24, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Brute force is to generate all k^2 possible combinations and sort them.
//
//			The minimum is 0. Then we have two options: either we can increment a or b.
//			Each time we select the smallest from a set of elements we generated previously by incrementing a and b.
//
//			We could use priority queue to find minimum each time. But one number can be generated in multiple ways.
//			Priority queue will report duplicate multiple times. So use BST map instead.

struct ABSqrt2
{
	int A, B;
	double val;

	ABSqrt2(int a, int b): A(a), B(b), val(a + b * sqrt(2)) {}

	bool operator< (const ABSqrt2& that) const { return val < that.val; }
};

typedef vector<double> VD;

VD EnumerateSmallestABSqrt2(int k)
{
	VD result;
	set<ABSqrt2> candidate;
	candidate.emplace(ABSqrt2(0,0));

	for(int i=0; i<k ; ++i) {
		ABSqrt2 min = *candidate.begin();
		result.emplace_back(min.val);
		candidate.erase(candidate.begin());
		candidate.emplace(ABSqrt2(min.A+1,min.B));
		candidate.emplace(ABSqrt2(min.A,min.B+1));
	}

	return result;
}

int main()
{
	VD res = EnumerateSmallestABSqrt2(6);
	for(double d: res) {
		cout << d << ", ";
	}
	cout << endl;
}
