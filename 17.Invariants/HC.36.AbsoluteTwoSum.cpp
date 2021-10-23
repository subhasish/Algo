/*
 * HC.36.AbsoluteTwoSum.cpp
 *
 * Problem: An abs-sorted array is an array of numbers in which |A[i]| < |A[j]| for all i<j.
 * 			That means array is sorted based on absolute values, but may not be actually sorted.
 *
 * 			Design an algorithm that takes an abs-sorted array and a number K, and returns a pair
 * 			of indices of elements that sum to K. Output (-1,-1) if not found.
 *
 *  Created on: Jan 13, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * Solution:
 * 			Brute-force solution to check each pair is O(n^2).
 * 			But we have solved the problem for actual sorted array in 17.Invariants/00.TwoSum.cpp
 * 			that does it in O(n).
 *
 * 			So it is better to use that O(n) algorithm on the different cases of the problem.
 * 			Data is jumbled up, we can make decompose the data to make exhaustive cases on which
 * 			this algorithm can be applied.
 *
 * 			The cases will be:
 * 			1) Both numbers are positive
 * 			2) Both numbers are negative
 * 			3) One number is positive and another negative
 *
 * 			For cases 1 and 2 we can run the previous algorithm separately by just limiting ourselves
 * 			to positive and negative entries.
 *
 * 			For case 3 we can use the same approach where we have one index for negative number and
 * 			another for positive number. They both can start from end of array and then go down.
 * 			Starting from end of array indicate that positive one is pointing to largest one and
 * 			negative one starting from the smallest one. So we can use the previous algorithm.
 *
 * C++:
 * 			template type compare can be used to pass less<int>() and greater_equal<int>()
 * 			Another way would be to have type function<bool(int,int)>
 */

struct IndexPair {
	int index_1, index_2;
};
IndexPair FindPairUsingCompare(const vector<int>& A, int k, function<bool(int,int)> comp);
IndexPair FindPositiveNegativePair(const vector<int>& A, int k);

IndexPair FindTwoSumInAbsoluteSortedArray(const vector<int>& A, int k) {
	// First try case when one number is positive and another is negative
	IndexPair result = FindPositiveNegativePair(A, k);

	if(result.index_1 == -1) {	// Not found
		if(k >= 0) {
			return FindPairUsingCompare(A, k, greater_equal<int>());
		} else {
			return FindPairUsingCompare(A, k, less<int>());
		}
	}
	return result;
}

IndexPair FindPairUsingCompare(const vector<int>& A, int k, function<bool(int,int)> comp) {
	IndexPair result = IndexPair{0, static_cast<int>(A.size()-1)};
	while(result.index_1 < result.index_2) {
		while(!comp(A[result.index_1], 0)) {
			++result.index_1;
		}
		while(!comp(A[result.index_2], 0)) {
			--result.index_2;
		}

		int sum = A[result.index_1] + A[result.index_2];
		if(sum == k) {
			return result;
		} else if(sum < k) {
			++result.index_1;
		} else { 	// sum > k
			--result.index_2;
		}
	}
	return {-1, -1};
}

IndexPair FindPositiveNegativePair(const vector<int>& A, int k) {
	IndexPair result = IndexPair{static_cast<int>(A.size()-1), static_cast<int>(A.size()-1)};
	while(result.index_1 >=0 && result.index_2 >= 0) {
		while(A[result.index_1] >= 0) {
			--result.index_1;
		}
		while(A[result.index_2] < 0) {
			--result.index_2;
		}

		int sum = A[result.index_1] + A[result.index_2];
		if(sum == k) {
			return result;
		} else if(sum < k) {
			--result.index_1;
		} else { 	// sum > k
			--result.index_2;
		}
	}
	return {-1, -1};
}

int main()
{
	vector<int> A = {-49, 75, 103, -147, 164, -197, -238, 314, 348, -422};

	IndexPair x = FindTwoSumInAbsoluteSortedArray(A, 167);
	cout << x.index_1 << "," << x.index_2 << endl;

	x = FindTwoSumInAbsoluteSortedArray(A, 42);
	cout << x.index_1 << "," << x.index_2 << endl;

}
