/*
 * HC.28.CountInversions.cpp
 *
 * Problem: In an array a pair of indices (i,j) is called inverted if (i<j) but (A[i] > A[j]).
 * 			Intuitively the number of inverted pairs in an array is a measure of how unsorted it is.
 *
 * 			Design an efficient algorithm that takes an array of integers and return the number
 * 			of inverted pairs.
 *
 * 			ASSUME: we can modify the array
 *
 *  Created on: Dec 29, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Brute-force is to consider each O(n^2) pairs.
//			But one way to recognize that brute force is inefficient is that how we check if an array
//			is sorted. We do not check every pair. We only check next element, as greater than or equal
//			relation is transitive.
//
//			This suggests the use of sorting to speed up the counting; sorting can be done in O(n log n)
//			which is better than O(n^2).
//
//			Think about the merge process of the two sorted arrays. If the first element of the second
//			array is smaller than the first element of the first array then it is smaller than
//			all remaining elements of the array. So we directly get the number of inversions of that
//			element. But if element in first arrays is smaller then there is no inversion.
//
//			If we keep the counts of inversions while merging then we will get the count while sorting.
//
// C++:
//			The copy function and the back_inserter function

int CountSubArrayInversions(int start, int end, vector<int>* A_ptr);
int MergeSortAndCountInversions(int start, int mid, int end, vector<int>* A_ptr);

int CountInversions(vector<int>& A) {
	return CountSubArrayInversions(0, A.size()-1, &A);
}

int CountSubArrayInversions(int start, int end, vector<int>* A_ptr) {
	if(start >= end) {
		return 0;
	}

	int mid = start + (end-start)/2;

	return  CountSubArrayInversions(start, mid, A_ptr) +
			CountSubArrayInversions(mid+1, end, A_ptr) +
			MergeSortAndCountInversions(start, mid, end, A_ptr);
}

int MergeSortAndCountInversions(int start, int mid, int end, vector<int>* A_ptr) {
	vector<int> sorted_A;
	int left_start=start, right_start = mid+1, inversion_count = 0;

	vector<int>& A = *A_ptr;
	while(left_start <= mid && right_start <= end) {
		if(A[left_start] <= A[right_start]) {
			sorted_A.emplace_back(A[left_start++]);
		} else {
			//A[left_start, mid] are inversion of A[right_start]
			inversion_count += (mid - left_start + 1);
			sorted_A.emplace_back(A[right_start++]);
		}
	}

	// Add remaining element
	copy(A.begin()+left_start, A.begin()+mid+1, back_inserter(sorted_A));
	copy(A.begin()+right_start, A.begin()+end+1, back_inserter(sorted_A));

	// Update A with sorted A
	copy(sorted_A.begin(), sorted_A.end(), A.begin() + start);
	return inversion_count;
}


int main() {
	vector<int> A = {3, 6, 4, 2, 5, 1};
	cout << "Inversion count = " << CountInversions(A) << endl;
}
