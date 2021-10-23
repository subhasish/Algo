/*
 * 06.KnapSack.cpp
 *
 * Problem: We are given a set of items with different value and weights.
 * 			Also we are given a knapsack that can contain up to certain weight.
 *
 * 			We need to find the subset that satisfies the weight constraint of the
 * 			knapsack but also has the maximum value possible.
 *
 * Variant 1:
 * 			Given a set of items with values, divide them in two sets such that difference
 * 			between the values of the two sets is minimum.
 *
 * Variant 2:
 * 			Given a set of items with values, tell whether it is possible to divide them
 * 			in two sets such that both set have same value.
 *
 *  Created on: May 5, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Most important to realize that greedy approach will not give the best solution.
//
//			It is clear that we need to consider all possible subsets, means all possible
//			combinations. As order does not matter, similar to coin change problem
//			we can grow solution for full array by first considering solutions for set of items
//			{0,..,i-1} then build solution for set that has the element i.
//
//			Recurrence relation is also similar to the coin change problem. For each i th element
//			we may choose to include that of exclude that. If we include that and current
//			knapsack limit is K, then we need to take solution for (K-Wi) from {0,..,i-1}.
//			Otherwise, consider solution for K from {0,...,i-1}. The maximum will be the solution.
//
//			When thinking this kind of problem I was always blocked by the thought that I need to
//			consider all possible of combinations and there is no ordered way to that. But
//			seeing these problems it is clear that there is ordered way to do this.
//
// Variants:
//			If we take sum of the total values and think of knapsack that has limit as half
//			of the total then we would find the optimal solution. If optimal is same as limit then
//			we find a tie otherwise we find the best we could.

struct Item {
	int value, weight;
};

int OptimalSubjectToCapacity(const vector<Item>& items, int capacity)
{
	// DP[i][j] stores the optimal value when we choose items [0,..,i] and have constraint j.
	int DP[items.size()][capacity+1];

	// Base case: No solution possible when capacity is 0
	for(int i=0; i < (int)items.size() ; ++i) {
		DP[i][0] = 0;
	}

	// Be careful about negative index and their meanings
	for(int i=0; i < (int)items.size() ; ++i) {
		for(int j=1 ; j<=capacity ; ++j) {
			int without_this = (i>0) ? DP[i-1][j] : 0;
			int with_this = ((j-items[i].weight) >=0) ?
								(((i>0) ? DP[i-1][(j-items[i].weight)] : 0) + items[i].value) : 0;
			DP[i][j] = max(with_this, without_this);
		}
	}

	return DP[items.size()-1][capacity];
}


int main()
{
	vector<Item> items = {Item{60,5}, Item{50, 3}, Item{70, 4}, Item{30, 2}};

	cout << OptimalSubjectToCapacity(items, 5) << endl;
	cout << OptimalSubjectToCapacity(items, 1) << endl;
	cout << OptimalSubjectToCapacity(items, 6) << endl;
}
