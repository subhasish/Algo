/*
 * 03.PermutationWithDups.cpp
 *
 * Problem: Given an array of integers with duplicates, generate all permutations of the array.
 *
 *  Created on: Apr 7, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Given an permutation if we generate the next permutation based on logic used in
//			05.Array/11.NextPermutation.cpp then we will essentially ignore the duplicates.
//
//			So this will be an iterative solution for finding all permutations where we can
//			start with the sorted version and then continuously find the next permutation.
//
//			Finding next permutation can be done as in Array/11.NextPermutation.cpp
//			Or we can use next_permutation in STL
//
// Time complexity:
//			Total number of such permutation is n!/(..) and each next permutation will take O(n)
//			So T(n) = O(n * n!)

typedef vector<int> VI;
typedef vector<VI> VVI;

VVI PermutationIterative(VI A)
{
	VVI result;

	// Generate the first permutation by sorting
	sort(A.begin(), A.end());

	do{
		result.emplace_back(A);
	} while(next_permutation(A.begin(), A.end()));

	return result;
}

int main()
{
	VI A = {2, 3, 3, 7};
	VVI result = PermutationIterative(A);

	for(VI& oneSol: result) {
		cout << "One permutation: ";
		for(int i: oneSol) {
			cout << i << ", ";
		}
		cout << endl;
	}


	cout << "Total possible permutations: " << result.size() << endl;
}
