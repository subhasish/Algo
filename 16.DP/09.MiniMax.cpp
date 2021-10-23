/*
 * 09.MiniMax.cpp
 *
 * Problem: It is a pick up coin game, where an even number of coins are placed in a line.
 * 			Two players take turns at choosing one coin each, but only from either end.
 *
 * 			Design an efficient algorithm for computing the maximum total value for the
 * 			starting player assuming both player play optimally.
 *
 *  Created on: May 9, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			It is clear that greedy will not work. And we need to consider all possibilities
//			while deciding on which one to pick.
//
//			In a range [a,b] let say M(a,b) the maximum one can obtain if other also play optimally.
//			That maximizing the minimum possible. If first player picks a then he can get maximum
//			C[a]+S(a,b)-M(a+1,b) where S(a,b) is sum of C[a..b]. Similar for b. So we can say:
//			M(a,b) = max(C[a]+S(a,b)-M(a+1,b), C[b]+S(a,b)-M(a,b-1)).
//
//			Another way of looking this is that second player seek to maximize his revenue by trying
//			to minimize the revenue of first player, as total is constant. Then we can write:
//			M(a,b) = max({C[a] + min(M(a+1,b-2), M(a+2,b-1))}, {C[b] + min(M(a+1,b-1), M(a,b-2))})
//			ALERT: I got it wrong first time. All size in recurrence is (a+b-2). If second parameter
//			is size instead of position then size would be (b-2) for all subproblems.
//
//			Benefit of this min-max recurrence is that it does not require computing S(a,b)
//
//			Top-down is trivial as just writing the recurrence relation.
//			Bottom up can be done by growing the length of the sub-array. Outer loop will be on the
//			length of substring, so that we find smaller solution first. Inner loop will be on
//			starting index.

int MiniMaxPickUpCoin(const vector<int>& C)
{
	// DP[i][j] will store the result for subarray that starts at i and have length j
	int DP[C.size()][C.size()+1];

	//memset(DP, 0, sizeof(DP));  // Optional

	// Base case: For length 1 and 2 its trivial
	for(size_t i=0; i < C.size() ; ++i) {
		DP[i][0] = 0; 						// No element
		DP[i][1] = C[i];					// 1 element
		if(i< C.size()-1) {
			DP[i][2] = max(C[i],C[i+1]);  	// 2 elements
		} else {
			DP[i][2] = 0;
		}
	}

	// Recurrence
	for(size_t j=3 ; j <= C.size() ; ++j) {			// All smaller length has to be computed first. Note = sign!
		for(size_t i=0; i+j-1 < C.size() ; ++i) {	// Until last index is not beyond the array
			DP[i][j] = max(C[i]+min(DP[i+2][j-2],DP[i+1][j-2]), C[i+j-1]+min(DP[i][j-2], DP[i+1][j-2]));
		}
	}

	return DP[0][C.size()];
}


int main()
{
	vector<int> C= {10, 25, 5, 1, 10, 5};
	cout << MiniMaxPickUpCoin(C) << endl;
}
