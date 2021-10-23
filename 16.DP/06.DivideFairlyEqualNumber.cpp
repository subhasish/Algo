/*
 * 06.DivideFairlyEqualNumber.cpp
 *
 * Problem: Given a set of elements with corresponding values, divide them in two sets such that
 * 			the the difference of values of the two sets is minimum and the two sets has
 * 			equal number of elements.
 *
 *  Created on: May 6, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			It is a variant of the knapsack problem. If we did not have the constraint of equal
//			number of elements in each sets then it is same as knapsack problem where the weight
//			constraint is the half of total weights.
//
//			But now we have the number constraint as well. Just think it as another constraint.
//			For each element we have two choices; to include them in solution and not to include.
//			And now we will have to do it for each weight up to limit, for each possible set size.
//
//			So we can see that any constraint can be transformed into another parameter and can
//			be solved in this general way

int DivideFairlyInEqualNumbers(vector<int> items)
{
	int N = (int) items.size();
	if(N%2 != 0) {
		cout << "Not possible, odd number of elements." << endl;
		return 0;
	}

	int total=0;
	for(int i: items) {
		total += i;
	}
	int limit = total/2;

	// DP[i][j][k] stores the optimal solution involving elements from items[0..i] with total less
	// than j that involves k elements in the solution
	int DP[N][limit+1][N/2+1];

	// Base case: When limit is 0 or number of elements is 0 optimal solution is also 0
	for(int i=0; i<N ; ++i) {
		for(int j=0 ; j<=limit ; ++j) {
			DP[i][j][0] = 0;
		}
		for(int k=0; k<=N/2 ; ++k) {
			DP[i][0][k] = 0;
		}
	}

	for(int i=0; i<N ; ++i) {
		for(int j=1 ; j<=limit ; ++j) {
			for(int k=1; k<=N/2 ; ++k) {
				int without = (i>0) ? DP[i-1][j][k] : 0;
				int with = (j-items[i] >= 0) ?
						(((i>0) ? DP[i-1][j-items[i]][k-1] : 0) + items[i]) : 0;
				DP[i][j][k] = max(with, without);
			}
		}
	}

	return DP[N-1][limit][N/2];
}

int main()
{
	cout << DivideFairlyInEqualNumbers({60,50,70,30}) << endl;
	cout << DivideFairlyInEqualNumbers({60,1,2,3,4,5}) << endl;
}
