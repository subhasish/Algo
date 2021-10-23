/*
 * 2.SwapBits.cpp
 *
 * Swap ith and jth bits of a word.
 *
 *  Created on: Jun 20, 2017
 *      Author: subha
 */


#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

// For swapping bits:
//   if bits are same then no change is needed
//   if different then inverting bits is sufficient
// NOTE: positions are in 0 based index from LSB
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

int main()
{
	cout << SwapBits(1622,1,5) << endl;
	cout << SwapBits(23353,2,6) << endl;
}


