/*
 * 03.Permutations.cpp
 *
 * Problem: Given an array of distinct integers generate all permutations of the array.
 *
 *  Created on: Apr 5, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			This is an enumeration problem, similar to the N Queens problem. Hinting recursion.
//			Solution of permutation of n numbers are built on top of permutation of (n-1) numbers.
//			Hence it can be solved by recursion.
//
//			As this is like enumeration, we will grow the recursion tree and when we hit a leaf
//			we know that we got a result. Going one solution to another solution is like
//			backtracking. Backtrack from one branch and explore another.
//
//			Now simple permutation logic is putting all elements in first position. And then
//			permute rest of the elements in rest of the positions.
//
//			To put element from rest of the elements we can maintain a maintain a list of elements
//			or an index as used in this solution.
//
// Time complexity:
//			The recurrence relation is T(n) = n*(T(n-1) + 1) = O(n!)
//			Unwrapping the recurrence will look like: n*((n-1) * ((n-2) * (T(n-3) +1)) + 1)


typedef vector<int> VI;
typedef vector<VI> VVI;

void PermutationHelper(int pos_to_fill, VI& A, VI& used_index, VI& partial_current, VVI& result)
{
	if(pos_to_fill == (int)A.size())
	{
		result.emplace_back(partial_current);
	}
	else
	{
		for(size_t i=0; i<used_index.size() ; ++i)
		{
			if(used_index[i] == -1)
			{
				used_index[i] = 1; // mark that entry array is used
				partial_current[pos_to_fill] = A[i];

				PermutationHelper(pos_to_fill+1, A, used_index, partial_current, result);

				used_index[i] = -1; // clear
			}
		}
	}
}

VVI Permutations(VI& A)
{
	VVI result;
	VI perm(A.size());
	VI used(A.size(),-1);

	PermutationHelper(0, A, used, perm, result);

	return result;
}

int main()
{
	VI A = {2, 3, 5, 7};
	VVI result = Permutations(A);

	for(VI& oneSol: result) {
		cout << "One permutation: ";
		for(int i: oneSol) {
			cout << i << ", ";
		}
		cout << endl;
	}


	cout << "Total possible permutations: " << result.size() << endl;
}
