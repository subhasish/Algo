/*
 * 9.GeneratePrimes.cpp
 *
 * Problem: Given a number n, generate all prime number upto n
 *
 *  Created on: Aug 19, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;


void print_vector(vector<int> list)
{
	for(int i: list)
	{
		cout << i << endl;
	}
}



// Brute force: For each number test whether it is prime or not. O(n^1.5)
// Sieve of Eratosthenes: When we figure out something is prime, mark all its multiple as non-prime.
//                        If we start from 2 and do for all numbers incrementally then when
//                        encounter a number NOT marked as non-prime, is actually a prime
VI GeneratePrimes(long long n)
{
	VI primes;
	vector<bool> isPrime(n+1, true);

	isPrime[0] = false;
	isPrime[1] = false;

	for(long long i=2; i<=n ; ++i) {
		if(isPrime[i] == true) {
			primes.push_back(i);

			for(long long j=2; i*j<=n ; j++) {
				isPrime[i*j] = false;
			}
		}
	}

	return primes;
}

int main()
{
	print_vector(GeneratePrimes(10000000));
}


