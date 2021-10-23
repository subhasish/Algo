/*
 * HC.31.CircularMaxSubarray.cpp
 *
 * Problem: We have seen how maximum subarray sum can be computed in DP/00.MaximumSubarray.cpp, but
 * 			it cannot solve for circular array. In circular array first and last elements are
 * 			considered adjacent.
 *
 * 			Given a circular array A, compute its maximum subarray sum in O(n) time.
 * 			Also try to do it in O(n) time and O(1) space.
 *
 *  Created on: Jan 4, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Alternative solution to the circular subarray can be computed by computing minimum
//			subarray - the remaining elements yield a subarray that cycles around.
//
//			This approach uses O(1) space and O(n) time.
//
// C++:
//			Pass max or min comparator


// Calculates the non-circular solution
// NOTE: how the max or min is passed
int OptimumCompSubarray(const vector<int>& A, const int& (*comp) (const int&, const int&)) {
	int overall=0;
	int till=0;

	for(int a: A) {
		till = comp(a, a + till);
		overall = comp(till, overall);
	}

	return overall;
}

int MaxSumarraySumInCircular(const vector<int>& A) {
	return max(OptimumCompSubarray(A, max),						// Non-circular case
			accumulate(A.cbegin(), A.cend(), 0) - OptimumCompSubarray(A, min));		// circular case
}


int main() {
	vector<int> A = {10, -4, 5, -4, 10};
	cout << "Max in circular = " << MaxSumarraySumInCircular(A) << endl;

	vector<int> B = {10, 4, 5, -4, 10};
	cout << "Max in circular = " << MaxSumarraySumInCircular(B) << endl;

	vector<int> C = {-10, -4, 5, -4, 10};
	cout << "Max in circular = " << MaxSumarraySumInCircular(C) << endl;
}
