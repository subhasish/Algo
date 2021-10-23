/*
 * 4.ClosestIntSameBitCount.cpp
 *
 * Given a number x, find a number y such that x and  has same number of 1s in
 * their binary representation and (x-y) is minimum
 *
 *  Created on: Jun 24, 2017
 *      Author: subha
 */


#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

// For minimum difference:
//  - They should differ in only two bits (swapping 0 and 1)
//  - They should differ in consecutive bits
// So, the lowest two bits that differ in x would be swapped in the result
ULL ClosestIntSameBitCount(ULL x)
{
	bool found = false;
	ULL result = x;

	for(unsigned int i=0; i < (sizeof(x)*8)-1 ; i++)
	{
		if( ((x>>i) & 1) != ((x >> (i+1)) & 1))
		{
			//NOTE: 64 bit Left shift require to write 1ULL instead of simple 32 bit 1
			result = ((1ULL << i)|(1ULL << (i+1)))^x;
			found = true;
			break;
		}
	}

	if(!found)
		cout << "Cannot find a different number with same number of bits set." << endl;
	return result;
}

int main()
{
	cout << ClosestIntSameBitCount(553535) << endl;
}


