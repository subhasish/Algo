/*
 * 04.PowerSetIterative.cpp
 *
 * Problem: Generate power set of a given set in iterative way
 * 			Assume size of the set is less than the width of an integer on the architecture/language
 *
 *  Created on: Apr 7, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			For set of n elements, consider numbers from 0 to (2^n - 1).
//			Each number can represent a set where a 1 in i th position will represent the presence of
//			i th element in the set.
//
//			Lowest set bit can be found by (x & !(x-1)). And its position can be found by taking
//			log of this result.
//
// Time complexity:
//			Total 2^n subsets and n time for each one, total O(n * 2^n)

typedef vector<int> VI;
typedef vector<VI> VVI;

VVI GeneratePowerSet(const VI& A)
{
	VVI power_set;

	for(int int_for_subset = 0; int_for_subset < (1 << A.size()) ; ++int_for_subset)
	{
		int bit_array = int_for_subset;
		VI subset;

		while(bit_array) {
			int mask_last_1 = (bit_array & ~(bit_array - 1)); // Keeps last bit
			int pos_last_1 = log2(mask_last_1);
			subset.emplace_back(A[pos_last_1]);

			bit_array = (bit_array & (bit_array-1));	// Erases last bit
		}

		power_set.emplace_back(subset);
	}

	return power_set;
}

int main()
{
	VI input = {0, 1, 2};
	VVI powerSet = GeneratePowerSet(input);

	for(VI& oneSol: powerSet) {
		cout << "One set: {";
		for(int i: oneSol) {
			cout << i << ", ";
		}
		cout << "}"<< endl;
	}


	cout << "Total possible sets in power set: " << powerSet.size() << endl;
}
