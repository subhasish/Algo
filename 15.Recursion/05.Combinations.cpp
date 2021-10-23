/*
 * 05.Combinations.cpp
 *
 * Problem: Generate all subsets of a specific size from a given input array.
 * 			In other words it is finding all possible of combinations.
 *
 *  Created on: Apr 7, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Brute force approach is to generate all subsets as in power set and take only that
//			matches the size. But it exponential and much waste.
//
//			Given all subsets of size (k-1) made out of (n-1) elements we can add n th element to
//			all of them and create subsets of size k that include the n th element.
//			This suggests recursion.
//
//			In general there are two possibilities for a subset; in includes certain element or
//			does not include it. In first case, we compute all subsets of size (k-1) from
//			elements {1,2,3,..,n-1} and add n th element to then; and in the second case we
//			consider subsets of size k made only from element {1,2,3,..,n-1}.
//
// Time complexity:
//			There are (n C k) number of combinations. And each combinations take O(n) to compute.
//			So total time = O(n *(n C k))


typedef vector<int> VI;
typedef vector<VI> VVI;

void CombinationHelper(int k, int n, VI& A, VVI& result)
{
	if(k < 1) {
		return;
	}
	if(k > n) {
		return;
	}
	if(k == n) {
		result.emplace_back(A.begin(), A.begin()+n);
		return;
	}
	if(k == 1) {
		for(int i=0; i < n ; ++i) {
			VI single = { A[i] };
			result.emplace_back(single);
		}
		return;
	}

	VVI temp_result;
	// This will compute combinations of size k-1 with elements from 0 to n-1, that is ignoring element at position n
	CombinationHelper(k-1, n-1, A, temp_result);
	for(VI& t: temp_result) {
		t.emplace_back(A[n-1]);
		result.emplace_back(t);
	}

	CombinationHelper(k, n-1, A, result);
}


VVI Combinations(VI A, int k)
{
	VI partial_result;
	VVI result;

	CombinationHelper(k, A.size(), A, result);

	return result;
}

int main()
{
	VI A = {1, 2, 3, 4, 5};
	VVI result = Combinations(A, 1);

	for(VI& oneSol: result) {
		cout << "One combination: ";
		for(int i: oneSol) {
			cout << i << ", ";
		}
		cout << endl;
	}


	cout << "Total possible combinations: " << result.size() << endl;
}
