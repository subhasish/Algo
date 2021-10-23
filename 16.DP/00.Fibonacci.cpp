/*
 * 00.Fibonacci.cpp
 *
 * Problem: Find nth Fibonacci number. Fibonacci(n) = Fibonacci(n-1) + Fibonacci(n-2)
 * 			Fibonacci number for 0 is 0 and 1 for 1.
 *
 *  Created on: Apr 21, 2018
 *      Author: subha
 */

# include <bits/stdc++.h>

using namespace std;

// Solution:
//			Use the recursive definition.
//			Top-down: 	Recurse as in definition and save all previous results in a map.
//			Bottom-up: 	Compute from 0 up to n. Can store all values in map. Also can cache only
//						last two values

unordered_map<int, int> Fib_cache;

int FibonacciTopDown(int n)
{
	if(n==0) return 0;
	if(n==1) return 1;

	if(!Fib_cache.count(n)) {
		Fib_cache[n] = FibonacciTopDown(n-1) + FibonacciTopDown(n-2);
	}
	return Fib_cache[n];
}

int FibonacciBotUp(int n)
{
	if(n==0) return 0;
	if(n==1) return 1;

	int fib_2=0, fib_1=1;  // Caching last two is enough
	int f;
	for(int i=2; i<=n ; ++i) {
		f = fib_1+fib_2;
		fib_2 = fib_1;
		fib_1 = f;
	}
	return f;
}

int main()
{
	cout << "Fibonacci number for 7 = " << FibonacciTopDown(7) << endl;
	cout << "Fibonacci number for 8 = " << FibonacciBotUp(8) << endl;
	cout << "Fibonacci number for 9 = " << FibonacciTopDown(9) << endl;
}
