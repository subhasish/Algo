/*
 * 3.Multiply.cpp
 *
 * Problem: Given two large integers represented in a vector, multiply them
 *
 *  Created on: Aug 15, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;

// Shift of each position in either number also shifts the position
// in the result. Ex:
//     7 8
//     5 6
// -------
//     4 8
//   4 2
//   4 0
// 3 5
// -------
// 4 3 6 8
// So position of the numbers will play role in position in the result they contribute.
// Details:
//   If we measure index from right to left (LSB to MSB) then product of position i and j will be at position (i+j)
//   But problem is that index starts from left to right (MSB to LSB).
//   We could reverse the numbers and then multiply and then reverse the result.
//   But without reversing, product of position i and j will be at position (i+j+1)
//   Ex:
//          0 1
//        0 1 2
//    ---------
//    0 1 2 3 4
//   Product of position 1 and 2 will be at (1+2)+1=4

VI Multiply(VI A, VI B)
{
	// get the sign of result: negative only when one is negative other is not
	bool negative = ((A[0] < 0) ^ (B[0] < 0));

	A[0] = abs(A[0]);
	B[0] = abs(B[0]);

	unsigned int As=A.size(), Bs=B.size();
	VI result(As+Bs,0);

	// NOTE: that LSB is at the end of the vector and MSB at the start
	//       we need to start multiplication from the end
	for(int i=As-1 ; i>=0; i--) {
		for(int j=Bs-1 ; j>=0 ; j--) {

			// multiply into proper position;  AND add to previous multiplications
			result[i+j+1] = result[i+j+1] + A[i] * B[j];

			// push carry in higher digit;  AND add to previous multiplications
			result[i+j] = result[i+j] + result[i+j+1]/10;

			// remainder will remain at this position; not add
			result[i+j+1] = result[i+j+1]%10;
		}
	}

	//remove leading 0's
	for(int i: result){
		if(i==0)
			result.erase(result.begin());
		else
			break;
	}

	//sign correction
	if(negative)
		result[0] *= -1;

	return result;
}

void printInteger(VI A)
{
	for(int i: A) {
		cout << i;
	}
	cout << endl;
}

int main()
{
	printInteger(Multiply({7,8},{5,6}));
	printInteger(Multiply({-7,8},{5,6}));
	printInteger(Multiply({-7,8},{-5,6}));
	printInteger(Multiply({2,2},{3}));
}


