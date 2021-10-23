/*
 * 13.CollatzConjecture.cpp
 *
 * Problem: Collatz conjecture is:  Take any natural number. If it is odd triple it and add one; if it is even then halve it.
 * 									Repeat the process indefinitely. No matter what the number you start with, you will eventually arrive at 1.
 *
 * 			Despite intense efforts, collatz conjecture has not been proved or disproved.
 *
 * 			Given a positive number n, test the collatz conjecture for first n natural numbers.
 *
 *  Created on: Feb 26, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: 	Open ended, with no definite good solution.
//				Collatz conjecture can fail in two ways:
//					1. A sequence returns to a previous number in the sequence, implying infinite loop
//					2. A sequence goes to infinity, which we would flag when overflow happens
//
//				General idea is to apply rule for each number until we reach 1. Here are some ideas to accelerate the check
//					- Reuse computation by storing all numbers so far found to reach 1. This will help to stop early.
//					- Even numbers can be skipped, as they are immediately halved and resulting number should already be checked
//					- If we have tested all number up to k then we can stop when number reaches less than k. No need to store them in hash table.
//					- If multiplication and divisions are expensive then can use bit shifting
//					- Partition search set for processing them parallelly in multiple computers.
//					- Since the number can grow use 64 bit integer and keep testing overflow.

unordered_set<long long> verified_number;			// Odd numbers; already verified to converge to 1

bool TestCollatzConjecture(int n)
{
//	unordered_set<long> verified_number;			// Odd numbers; already verified to converge to 1

	for(int i = 3; i <= n ; i += 2)
	{
		unordered_set<long long> sequence;
		long long test = i;

		// Test current i.
		while(test >= i)							// All number less than i is already verified.
		{
			if(!sequence.emplace(test).second)		// Number in the current sequence => Infinite loop!!
			{
				return false;
			}

			if(test % 2) {							// Odd number
				// As in book we could have stored the verified number set. In that case the verified number set could have some
				// wrong entries. But for the purpose of this question to return true/false it would work. This is because we are checking
				// the current sequence first to rule something out.
				if(verified_number.find(test) != verified_number.end())		// Already tested to converge
				{
					break;
				}

				long long next_test = test * 3 + 1;
				if(next_test <= test)				// Overflow!!
				{
					//throw overflow_error("Collatz sequence overflow for " + i);// to_string(i));
					cout << "Collatz sequence overflow for " <<  i << endl;
					cout << "Current test = " << test << ", next = " << next_test << endl;
					return false;
 				}

				test = next_test;
			} else {
				test /= 2;							// Even; halve it
			}
		}

		for(long long num: sequence)					// All numbers on the sequence should be marked as verified
		{
			verified_number.emplace(num);
		}
	}

	return true;
}


int main()
{
	cout << TestCollatzConjecture(2352334636) << endl;
}
