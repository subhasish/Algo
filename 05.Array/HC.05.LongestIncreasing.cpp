/*
 * HC.05.LongestIncreasing.cpp
 *
 * Problem: Implement an algorithm that takes as input an array A of n elements and returns
 * 			beginning and ending indices of a longest increasing subarray of A.
 *
 *  Created on: Nov 1, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

struct SubArray {
	int start = 0, end = 0;
};

// Solution:
//			Simple O(n) solution would be track maximum increasing length and increment it if
//			next element is greater than current one. Otherwise reset the count.

SubArray LongestIncreasingSubarray(const vector<int>& A)
{
	int max_length = 1;
	SubArray result;
	int curr_length = 1;
	for(size_t i=0; i<(A.size()-1) ; ++i) {
		if(A[i] < A[i+1]) {
			++curr_length;
			if(max_length < curr_length) {
				max_length = curr_length;
				result.start = i+1-max_length+1;
				result.end = i+1;
			}
		} else {
			curr_length=1;
		}
	}
	return result;
}

// Solution:
//			This can be improved for certain cases to be better than O(n)
//			Suppose we see longest sequence early in the array and we rest of the elements
//			are decreasing, then instead of checking forward in A[i+1] if we check
//			backward from A[i+max_length] then we can quit early and may skip checking all elements!
//
//			We can quit if (Array size - max_length) is greater than i. So from i we cannot beat the
//			current max.

SubArray LongestIncreasingSubarrayOpt(const vector<int>& A)
{
	SubArray result;
	int max_length = 1;
	int start = 0;

	while(start < (int)(A.size()-max_length)) {     // quit if current starting index is not good enough
		bool check_forward = false;
		// check backwards
		for(int j=start+max_length; j>start ; --j) {	//checking [i,i+max_length]. So if succeeds,
														// already max_length is one more than current.
			if(A[j] <= A[j-1]) {
				break;
			} else {
				if(j == start+1) {						// succeeded for whole sequence
					check_forward = true;
				}
			}
		}

		// check forward and increment max_length
		if(check_forward) {
			++max_length; // All good means max_length is one more than previous
			result.start = start;
			result.end = start+max_length-1;
			for(int j=start+max_length-1; j<(int)(A.size()-1) ; ++j) {
				if(A[j] < A[j+1]) {		// One more
					++max_length;
					result.start = start;
					result.end = start+max_length-1;
				} else {
					break;
				}
			}
		}
		start += max_length;	//Next start can be after current sequence [start, start+max_legth-1]
	}

	return result;
}

int main()
{
	vector<int> A = {2,11,3,5,13,7,19,17,23};
	SubArray result = LongestIncreasingSubarray(A);
	cout << "[" << result.start << ", " << result.end << "]" << endl;

	result = LongestIncreasingSubarrayOpt(A);
	cout << "[" << result.start << ", " << result.end << "]" << endl;
}
