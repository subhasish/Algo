/*
 * 02.UnSynched.cpp
 *
 * Problem: Thread t1 and t2each increment an integer variable N times, as shown in the code
 * 			below. This program yields non-deterministic results.
 *
 * 			What are the maximum and minimum value can be printed?
 *
 *  Created on: Jul 29, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			The maximum value is 2N when they two threads are run sequentially.
//			The minimum value is 2. That will happen as follows:
//				t1 and t1 reads 0. Then t1 increments (N-1) times.
//				Now t2 writes 1. Then t1 reads 1 for its final increment.
//				Then t2 does its rest of the (N-1) increments.
//				Then t1 does its final increment from 1 to 2 and writes it.

static int counter = 0;

void IncrementCounter(int N)
{
	for(int i=0; i<N ; ++i) {
		++counter;
	}
}


int main()
{
	thread t1(IncrementCounter, 1000000);
	thread t2(IncrementCounter, 1000000);
	t1.join();
	t2.join();

	cout << "Final counter value => " << counter << endl;
}
