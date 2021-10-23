/*
 * 04.PowerSet.cpp
 *
 * Problem: Power set of a set is the set of all subsets of that set.
 * 			Given a set generate its power set.
 *
 *  Created on: Apr 7, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			From power set of (n-1) elements we can easily generate power set of n elements.
//			This suggests recursion. Add nth element in each sets and then take union.
//
//			It is also enumeration kind of problem. So we can grow the recursion tree and at
//			leaf add it to the result. To grow recursion tree at each level consider a new element.
//			It has two possibilities the new element can be present or absent for each node so far.
//
// Time complexity:
//			There are 2^n possible solutions. The recursive paths are shared. But Total nodes
//			in the tree is O(2^n) as it is a binary tree. O(1) computation in each intermediate
//			nodes but O(n) at leaves to add result. The average subset size is n/2 and 2^n leaves.
//			So, T(n) = O(n * 2^n)

typedef vector<int> VI;
typedef vector<VI> VVI;

void PowerSetHelper(int item_to_consider,VI& input, VI& partial_result, VVI& power_set)
{
	if(item_to_consider == (int)input.size())
	{
		power_set.emplace_back(partial_result);
	}
	else
	{
		// Do not include the current item
		PowerSetHelper(item_to_consider+1, input, partial_result, power_set);

		// Include the current item
		partial_result.emplace_back(input[item_to_consider]);
		PowerSetHelper(item_to_consider+1, input, partial_result, power_set);

		// Back track for
		partial_result.pop_back();
	}
}

VVI GeneratePowerSet(VI input)
{
	VVI power_set;
	VI partial_result;

	PowerSetHelper(0, input, partial_result, power_set);

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
