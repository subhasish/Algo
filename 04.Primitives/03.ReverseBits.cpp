/*
 * 3.ReverseBits.cpp
 *
 * Reverse the bits position in a 64 bit number
 *
 *  Created on: Jun 21, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

// From problem 4.2 EPI
ULL SwapBits(ULL x,int i, int j)
{
	if( ((x>>i) & 1) != ((x>>j) & 1))
	{
		//inverting the bit can be done by XOR ing with 1s
		// NOTE: ULL suffix after 1 is very important. Otherwise shifting would operate on 32 bit constant
		ULL bit_mask = ((1ULL << i) | (1ULL << j));
		x = x ^ bit_mask;
	}
	return x;
}

// Use SwapBits to swap positions bits
ULL ReverseBits1(ULL x)
{
	for(int i=0; i<32 ; i++) {
		x = SwapBits(x,i,63-i);
	}
	return x;
}


array<unsigned int,((1<<16)+1)> precomputed_reverse;
void precompute()
{
	for(unsigned int i=0; i<precomputed_reverse.size() ; i++)
	{
		precomputed_reverse[i] = i;
	}
	for(unsigned int i=0; i<precomputed_reverse.size() ; i++)
	{
		//Swap within 16 bytes
		for(int j=0; j<8 ; j++) {
			precomputed_reverse[i] = SwapBits(precomputed_reverse[i],j,15-j);
		}
	}
}

// Order does not matter. Parity of a part can be combined with parity with other parts
// Use pre-computed array of 16 bits
ULL ReverseBits2(ULL x)
{
	const int kMaskSize = 16;
	const int kBitMask = 0xFFFF;



	ULL a = (x >> (3 * kMaskSize));
	ULL b = ((x >> (2 * kMaskSize)) & kBitMask);
	ULL c = ((x >> kMaskSize) & kBitMask);
	ULL d = (x & kBitMask);

	a = precomputed_reverse[a];
	b = precomputed_reverse[b];
	c = precomputed_reverse[c];
	d = precomputed_reverse[d];

	b = (b << kMaskSize);
	c = (c << (2 * kMaskSize));
	d = (d << (3 * kMaskSize));

	//This computation should be one time
	return a | b | c | d;
}


int main()
{
	cout << ReverseBits1(5658772931791028000) << endl;
	cout << ReverseBits1(4466) << endl;

	precompute();
	cout << ReverseBits2(5658772931791028000) << endl;
	cout << ReverseBits2(4466) << endl;

}

