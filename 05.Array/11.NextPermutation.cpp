/*
 * 11.NextPermutation.cpp
 *
 * Problem: Given a list of numbers we need to find the next permutation in lexicographic sorted order.
 *          Once largest permutation is reached return the smallest one.
 * Example: 2,4,3,1 => 3,1,2,4
 *          4,3,2,1 => 1,2,3,4
 *
 *  Created on: Aug 23, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;

void swap(int& A, int& B)
{
	int t=A;  A = B;   B = t;
}

void print_vector(vector<int> list)
{
	for(int i: list)
	{
		cout << i << " ";
	}
	cout << endl;
}


VI NextPermutation(VI A)
{
	// First find k from right such that A[k] < A[k+1].
	// This guarantees numbers A[k+1] onwards are decreasing in order
	int k=-1;
	for(int i=A.size()-1; i > 0 ; --i) {
		if(A[i-1] < A[i]) {
			k = i-1;
			break;
		}
	}
	//auto inversion_point = is_sorted_until(A.rbegin(),A.rend());


	if(k == -1) { // largest permutation
		reverse(A.begin(),A.end());
		return A;
	}
	//if(inversion_point == A.rend())
	//    return reverse(A.begin(),A.end())


	// Now find just next larger number than A[k] in the numbers right to k.
	// Such number exists as A[k] < A[k+1]. But there could be numbers smaller than A[k].
	// Ex: 2,4,3,1
	int m=-1;
	for(unsigned int j=k+1; j<A.size() ; ++j) {
		if(A[j] < A[k]) {
			m = j-1;
			break;
		}
	}
	//auto least_upper_bound = upper_bound(A.rbegin(), inversion_point, *inversion_point);

	// Now swap positions k and m. This will make 2,4,3,1 => 3,4,2,1
	swap(A[k], A[m]);
	//iter_swap(inversion_point, least_upper_bound);

	// Now reverse all the elements after position k
	// 3,4,2,1 => 3,1,2,4
	reverse(A.begin()+k+1, A.end());
	//reverse(A.rbegin(), inversion_point);

	return A;
}

int main()
{
	VI A = NextPermutation({8,5,9,7,6,2,4,3,1});
	print_vector(A);

	VI B = NextPermutation({1,1});
	print_vector(B);

	VI C = NextPermutation({4,3,2,1});
	print_vector(C);
}


