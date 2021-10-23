/*
 * 13.RabinKarp.cpp
 *
 * Problem: To find first occurrence of a pattern in a text.
 *
 * There are 3 famous solutions for this, viz. KMP, Boyer-Moore and Rabin-Karp.
 * We will implement Rabin-Karp here.
 *
 *  Created on: Oct 12, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

LL Mod;        	// modulus
int Base;   	// Radix / base

LL ModularRollingHash(string key, int M) {
	LL hash = 0;
	for(int i=0; i<M ; i++) {
		hash = (hash * Base + key[i]) % Mod;
	}
	return hash;
}

void Initialize(const string& pattern, LL* patHash, int* M, LL* RM)
{
	*M = pattern.length();
	*patHash = ModularRollingHash(pattern, *M);

	LL& RMr = *RM = 1;
	for(int i=0; i<*M-1 ; ++i) {
		RMr = (Base * RMr) % Mod;
	}
}

// Returns index for first character if match, string::npos otherwise
size_t RabinKarp(string text, string pattern)
{
	LL patHash;  // pattern hash value
	int M;       // pattern length
	LL RM;       // R^(M-1) % Q, used to subtract MSB directly every time

	Initialize(pattern, &patHash, &M, &RM);

	int N = text.length();
	if(M > N) return string::npos;

	LL txtHash = ModularRollingHash(text, M);

	// NOTE: we are starting the loop from M and not 0
	//       This is matching with pattern till (i-1)
	// If not found we will compute rolling hash including ith char
	for(int i=M; i<=N ; ++i) {
		int MSB = i-M;

		// Compare the hashes
		if(patHash == txtHash) { // Hash Match
			if(text.compare(MSB,M,pattern) == 0) { // Actual match
				return MSB;
			}
		}

		// Compute rolling hash by removing char MSB and including char i
		// Steps:
		//    1. Remove RM * text[MSB] from text hash
		//    2. Multiply rest of hash with Base to do a left shift
		//    3. Add new character in LSB
		txtHash = (txtHash + Mod - ((RM*text[MSB]) % Mod)) % Mod;
		txtHash = (((txtHash * Base) % Mod) + text[i]) % Mod;
	}
	return string::npos;
}

int main()
{
	Mod = 89041;
	Base = 256;

	size_t pos = RabinKarp("This is string search problem", "search");
	if(pos == string::npos) {
		cout << "Pattern not found!!" << endl;
	} else {
		cout << "Pattern found at position " << pos << endl;
	}

}


