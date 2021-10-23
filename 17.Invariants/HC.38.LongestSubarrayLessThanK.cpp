/*
 * HC.38.LongestSubarrayLessThanK.cpp
 *
 * Problem: Design an algorithm that takes an array A and a key k and returns the longest subarray
 * 			of A that has sum less than or equal to k.
 *
 *  Created on: Jan 13, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * Solution:
 * 			There is one special case for this solution when all numbers are positive. This case can
 * 			be solved easily using sliding window technique.
 * 			There we start both left and right indices from 0 and increase right as long as sum is
 * 			less than k. When sum is more than k, we increase left and take it out of sum. We keep
 * 			track of maximum. This way we are checking all the maximum interval starting at each point.
 * 			So this works for all positive integers.
 *
 * 			The algorithm to start from both end of array and remove maximum from both end does not
 * 			work. There can be larger number just past the minimum one that every time gets masked
 * 			by the smaller number. And we can reject many medium sized numbers that may be part of
 * 			the result. Example: A = {1, 1000, 2, 2, 2, 2, 2} and k=15
 *
 * 			The first algorithm does not work in general case when we have negative numbers as well.
 * 			Because when sliding window sum exceeds k we cannot directly reject the left, as some
 * 			negative number down the road may bring the sum under k.
 *
 * 			Lets try to visualize the problem to understand it better. As we are talking about
 * 			subarray we are not changing the arrangements. Sum of the subarray can be represented
 * 			with cumulative sum graph where x axis is the index and y axis is the cumulative sum.
 * 			In that graph we want to find a window of size k in y axis that includes maximum
 * 			number of points in x axis.
 *
 * 			For positive only the cumulative graph is always increasing. As per problem statement
 * 			we want to slide the window along y axis. But as value only change at x axis points,
 * 			accumulating points along x-axis to from the window and then move it works for positive
 * 			only numbers.
 *
 * 			But when we have negative numbers the cumulative graph will fluctuate. We want to neglect
 * 			the local fluctuations and see the farthest points in x-axis the k sized window
 * 			cuts/projects.
 * 			So starting at index i we want to know the farthest index j such that sum is within k,
 * 			even if cumulative sum exceeds k in between.
 * 			So while looking at an intermediate j we just do not want to know the sum until that point
 * 			but the minimum we could even if we get past j.
 * 			So we need to propagate the minimum from end of array to each point.
 *
 * 			It is like making the fluctuation curve a flat one. If for a i<j<w Sum[i,w]<Sum[i,j] then
 * 			we want to note the Sum[i,w] at Sum[i,j].
 *
 * 			Now with respect to the new function the curve will be non decreasing as in case of only
 * 			positive integers. So we can solve using sliding window.
 *
 */

struct IndexPair {
	int start_idx, end_idx;
};

IndexPair FindLongestSubarrayLessThanK(const vector<int>& A, int k) {
	vector<int> cum_sum;
	cum_sum.emplace_back(A.front());
	for(size_t i=1 ; i<A.size() ; ++i) {
		cum_sum.emplace_back(A[i]+cum_sum.back());
	}

	vector<int> min_past_this_point(cum_sum.size());
	min_past_this_point[cum_sum.size()-1] = cum_sum[cum_sum.size()-1];
	for(int i=(int)cum_sum.size()-2 ; i>=0 ; --i) {
		min_past_this_point[i] = min(cum_sum[i], min_past_this_point[i+1]);
	}

	//Now sliding window on it
	int left=0, right=0, max_length=0;
	IndexPair result = IndexPair{-1,-1};
	while(right < (int)A.size()) {
		int min_curr_sum = (left>0) ?
								min_past_this_point[right] - cum_sum[left-1]
							  : min_past_this_point[right];

		if(min_curr_sum <= k) {
			if(max_length < right - left + 1) {
				max_length = right - left + 1;
				result = IndexPair{left, right};
			}
			++right;
		} else {
			++left;
		}
	}
	return result;
}

IndexPair FindLongestPositiveSubarrayLessThanK(const vector<int>& A, int k) {
	IndexPair result = IndexPair{-1, -1};
	int start = 0, end = 0;
	int sum = A[start];
	int max_length = 0;

	while(end < (int)A.size()) {
		if(sum <= k) {
			if(end-start+1 > max_length) {
				max_length = end-start+1;
				result = IndexPair{start, end};
			}
			sum += A[end++];
		} else {
			sum -= A[start++];
		}
	}
	return result;
}

int main() {
	vector<int> A = {431, -15, 639, 342, -14, 565, -924, 635, 167, -70};
	IndexPair res = FindLongestSubarrayLessThanK(A, 184);
	cout << res.start_idx << ", " << res.end_idx << endl;

	A = {1, 2, 1, 0, 1, 1, 0};
	res = FindLongestPositiveSubarrayLessThanK(A, 4);
	cout << res.start_idx << ", " << res.end_idx << endl;

	A = { 1, 1000, 2, 2, 5, 4, 3, 2 };
	res = FindLongestPositiveSubarrayLessThanK(A, 100);
	cout << res.start_idx << ", " << res.end_idx << endl;

}
