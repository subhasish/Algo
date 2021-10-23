/*
 * 04.PowerSetMulti.cpp
 *
 * Problem: Generate power set of a multiset. Multiset is where items may appear multiple times.
 * 			The result power set should not repeat a multiset.
 *
 *  Created on: Apr 7, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			The fundamental difference between this problem and power set problem is that
//			in normal set an item can appear 0 time or 1 time. But in multiset an element can
//			continue to appear at most its frequency in the input.
//
//			This is the generic version of normal power set problem where each item has frequency 1.

typedef vector<int> VI;
typedef vector<VI> VVI;

void MultiPowerSetHelper(int item_to_consider, VI& input, VI& frequency, VI& partial_result, VVI& power_set)
{
	if(item_to_consider == (int)input.size())
	{
		power_set.emplace_back(partial_result);
	}
	else
	{
		for(int i=0; i<=frequency[item_to_consider] ; ++i) {

			// Include the current item in different frequencies
			for(int j=0 ; j<i ; ++j) {
				partial_result.emplace_back(input[item_to_consider]);
			}

			MultiPowerSetHelper(item_to_consider+1, input, frequency, partial_result, power_set);

			// Back track
			for(int j=0 ; j<i ; ++j) {
				partial_result.pop_back();
			}
		}
	}
}

VVI GenerateMultiPowerSet(VI input)
{
	VVI power_set;
	VI partial_result;

	unordered_map<int, int> freq_map;
	for(int i: input) {
		++freq_map[i];
	}

	VI unique;
	VI freq;
	for(auto it: freq_map) {
		unique.emplace_back(it.first);
		freq.emplace_back(it.second);
	}


	MultiPowerSetHelper(0, unique, freq, partial_result, power_set);

	return power_set;
}


int main()
{
	VI input = {1, 2, 3, 2};
	VVI powerSet = GenerateMultiPowerSet(input);

	for(VI& oneSol: powerSet) {
		cout << "One set: {";
		for(int i: oneSol) {
			cout << i << ", ";
		}
		cout << "}"<< endl;
	}


	cout << "Total possible sets in power set: " << powerSet.size() << endl;
}

