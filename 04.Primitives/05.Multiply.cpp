/*
 * 5.Multiply.cpp
 *
 * Compute X*Y without arithmetic operator
 *
 *  Created on: Jun 25, 2017
 *      Author: subha
 */


#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

ULL Add(ULL a, ULL b)
{
	ULL sum=0,carryin =0, k=1,temp_a=a, temp_b=b;

	while(temp_a || temp_b)
	{
		ULL ak = a & k;
		ULL bk = b & k;

		ULL carryout = (ak & bk) | (ak & carryin) | (bk & carryin);
		sum = sum | (ak ^ bk ^ carryin);
		carryin = carryout << 1;
		k = k << 1;
		temp_a = temp_a >> 1;
		temp_b = temp_b >> 1;
	}
	return sum | carryin;
}

ULL Multiply(ULL x, ULL y)
{
	//Brute force is to add x y-times. But that would depend on value of y and O(2^n)
	//Left Shifting 1 bit equal to multiplying by 2
	//So if ith bit of x is set then shift that many bits of y and add to the result

	ULL sum=0;
	while(x) {
		if(x & 1) {
			sum = sum + y;
			// sum = Add(sum,y)
		}
		x = x >> 1;
		y = y << 1;
	}
	return sum;
}

int main()
{
	cout << Multiply(43,645757) << endl;
}
