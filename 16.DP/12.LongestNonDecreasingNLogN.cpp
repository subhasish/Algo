/*
 * 12. LongestNonDecreasingNLogN.cpp
 *
 * Problem: It is a variant of DP/12.LongestNonDecreasing.cpp. Original problem statement was:
 *
 * 			Write a program that takes an input array and finds the length of longest
 * 			nondecreasing subsequence in the array. The numbers in the subsequence need
 * 			not to be consecutive.
 *
 * 			That was solved in O(n^2). In this problem solve it in O(n log n)
 *
 *  Created on: May 12, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
//

// Binary search (note boundaries in the caller)
int CeilIndex(std::vector<int> &v, int l, int r, int key) {
    while (r-l > 1) {
    	int m = l + (r-l)/2;
    	if (v[m] >= key)
    		r = m;
    	else
    		l = m;
    }

    return r;
}

int LongestIncreasingSubsequenceLength(std::vector<int> &v) {
    if (v.size() == 0)
        return 0;

    std::vector<int> tail(v.size(), 0);
    int length = 1; // always points empty slot in tail

    tail[0] = v[0];
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < tail[0])
            // new smallest value
            tail[0] = v[i];
        else if (v[i] > tail[length-1])
            // v[i] extends largest subsequence
            tail[length++] = v[i];
        else
            // v[i] will become end candidate of an existing subsequence or
            // Throw away larger elements in all LIS, to make room for upcoming grater elements than v[i]
            // (and also, v[i] would have already appeared in one of LIS, identify the location and replace it)
            tail[CeilIndex(tail, -1, length-1, v[i])] = v[i];
    }

    return length;
}

int main() {
    std::vector<int> v{ 2, 5, 3, 7, 11, 8, 10, 13, 6 };
    std::cout << "Length of Longest Increasing Subsequence is " << LongestIncreasingSubsequenceLength(v) << endl;
   return 0;
}

