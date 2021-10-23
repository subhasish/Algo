/*
 * HC.06.RotateArray.cpp
 *
 * Problem: Design an algorithm to rotate an array A of n elements to the right
 * 			by i positions.
 * 			Do not use library function to rotate.
 *
 *  Created on: Nov 1, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Carefully examining few smaller examples reveal that rotation somehow retain
//			the relative order between numbers.
//			Only thing if they were two groups then they swap their positions in the array.
//
//			From this intuition we can find that if we reverse the whole array to swap the
//			two groups first. But that reverses the original order of elements within the
//			group as well. So if we can reverse the groups individually then they will
//			get back to original form and the rotation will complete.

void RotateArray(int i, vector<int>& A) {
	i %= A.size();
	if(i == 0) {
		return;
	}
	reverse(A.begin(), A.end());
	reverse(A.begin(), A.begin()+i);
	reverse(A.begin()+i, A.end());
}

// Alternative solution:
//			Rotation can be thought as a permutation of the array and can be achieved as
//			other permutation can be done. That is one permutation can be decomposed to
//			a set of cyclic permutations.
//			Each element will shift to (currtent_pos+i)%n
//
//			Running through few examples, we will notice that:
//			1. All such cyclic permutations are of same length
//			2. Number of cycles is the GCD of n and i
//
//			*The permutation cycle will meet one of the previous element or in other words
//			i will catch n, at the LCM of i and n. LCM(i,n) = (i*n)/GCD
//			So the number of cycles after i will meet its previous element from the cycle is
//			LCM/i = n/GCD = cycle_length, say.
//			So each cycle will contain element n/cycle_length which is GCD.
//
// Time complexity: O(n) as each number is operated constant amount of time

int GCD(int A, int B);
void ApplyCyclePermutation(int rotate_amount, vector<int>& A, int offset, int cycle_length);

void RotateArrayPermutation(int rotate_amount, vector<int>& A) {
	rotate_amount %= A.size();
	if(rotate_amount == 0) {
		return;
	}

	int num_cycle = GCD(A.size(), rotate_amount);
	int cycle_length = A.size() / num_cycle;

	for(int c=0 ; c<num_cycle ; ++c) {
		ApplyCyclePermutation(rotate_amount, A, c, cycle_length);
	}
}

// Somehow eclipse is not being able to find swap
void swap(int& a, int& b) {
	int t= a;
	a = b;
	b = t;
}

void ApplyCyclePermutation(int rotate_amount, vector<int>& A, int offset, int cycle_length) {
	int curr_index = offset, next_index;
	int tmp = A[curr_index];
	for(int i=0 ; i<cycle_length ; ++i) {
		next_index = (curr_index+rotate_amount)%A.size();
		swap(tmp, A[next_index]);
		curr_index = next_index;
	}
}


int GCD(int A, int B) {
	if(A>B) {
		return GCD(B,A);
	} else if(A == B) {
		return A;
	} else { //A<B
		if(A==0) {
			return B;
		} else {
			return GCD(B%A, A);
		}
	}
}

void print_vector(vector<int>& list) {
	for(int i: list) {
		cout << i << " ";
	}
	cout << endl;
}

int main()
{
	vector<int> A = {1,2,3,4,5,6};
	RotateArray(2,A);
	print_vector(A);
	RotateArrayPermutation(2,A);
	print_vector(A);
}
