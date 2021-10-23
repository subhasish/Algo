/*
 * 10.ApplyPermutation.cpp
 *
 * Problem: Given an array and a permutation sequence, apply the permutation sequence to the array
 * 			Do NOT use helper array.
 *
 *  Created on: Aug 21, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;

// It is easy to do using an helper array. But still can be done in O(1) space and O(n) time
// Every permutation is a set of cycles.
//	We can always put first element in its proper position.Then put element in that position to its proper position and so on.
//  This can go on until we reach the first position, when we want to stop and look for next cycle.
// To detect whether that element is moved, we can use the permutation array itself.
//  Once an element is moved we can subtract size from the element, making it negative
void ApplyPermutation(VI& A, VI& perm)
{
	unsigned int sz = perm.size();
	//loop over all the cycles
	for (unsigned int i=0; i<perm.size() ; ++i) {
		//If cycle is not started
		if(perm[i] >= 0) {
			// initialize the cycle
			int currPos = i;
			int nextPos = perm[i];
			int currElement = A[i];
			int nextElement = A[perm[i]];

			//while the position to move the is a valid one, i.e., not already taken care of
			while(perm[currPos] >= 0) {
				A[nextPos] = currElement;  // Put element in its position
				perm[currPos] -= sz;       // mark the position as taken care of

				//Prepare for next one
				currPos = nextPos;         // save current position
				nextPos = perm[nextPos];   // get next position
				currElement = nextElement; // save current element
				nextElement = A[nextPos];  // save next element whose position will be overwritten
			}

		}
	}

	// Optionally restore permutation array
	for(unsigned int i=0; i < perm.size() ; ++i)
		perm[i] += sz;
}

void print_vector(vector<int>& list)
{
	for(int i: list)
	{
		cout << i << " ";
	}
	cout << endl;
}

int main()
{
	VI A = {1,2,3,4,5,6,7,8}, B = {5,2,7,0,1,6,3,4};
	ApplyPermutation(A,B);
	print_vector(A);
}



