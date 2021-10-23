/*
 * 1.Parity.cpp
 *
 * Parity of a word is 1 if number of 1s is odd, and otherwise 0.
 * Compute parity of a number.
 *
 *  Created on: Jun 16, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

// Check one bit at a time, if LSB is 1 then XOR result to invert current result
int Parity1(ULL x)
{
	int result=0;
	while(x) {
		result = result ^ (x&1);
		x = x>>1;
	}
	return result;
}

// Bit fiddling: x & (x-1) resets the last set bit. Invert result each time
int Parity2(ULL x)
{
	int result=0;
	while(x) {
		result = result ^ 1;
		x = (x & (x-1));
	}
	return result;
}


array<int,((1<<16)+1)> precomputed_parity;
void precompute()
{
	for(unsigned int i=0; i<precomputed_parity.size() ; i++)
	{
		precomputed_parity[i] = Parity2(i);
	}
}

// Order does not matter. Parity of a part can be combined with parity with other parts
// Use pre-computed array of 16 bits
int Parity3(ULL x)
{
	const int kMaskSize = 16;
	const int kBitMask = 0xFFFF;

	//This computation should be one time
	return precomputed_parity[x >> (3 * kMaskSize)] ^
			precomputed_parity[ (x >> (2 * kMaskSize)) & kBitMask] ^
			precomputed_parity[ (x >> kMaskSize) & kBitMask] ^
			precomputed_parity[x & kBitMask];
}

// Order does not matter. Parity of a part can be combined with parity with other parts
// This is also because XOR is associative
int Parity4(ULL x)
{
	x = x ^ (x >> 32);
	x = x ^ (x >> 16);
	x = x ^ (x >> 8);
	x = x ^ (x >> 4);
	x = x ^ (x >> 2);
	x = x ^ (x >> 1);

	return x & 0x1;
}

int main ()
{
	ULL a = 35336;
	ULL b = a+1;

	cout << Parity1(a) << endl;
	cout << Parity1(b) << endl;

	cout << Parity2(a) << endl;
	cout << Parity2(b) << endl;

	precompute(); //One time pre-computation
	cout << Parity3(a) << endl;
	cout << Parity3(b) << endl;

	cout << Parity4(a) << endl;
	cout << Parity4(b) << endl;

}


