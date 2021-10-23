/*
 * HC.03.BuySellKTimes.cpp
 *
 * Problem: We are given the stock price of n days for some company. We want to find the
 * 			maximum profit that can be made by buying and selling a single share k times
 * 			over the n days.
 *
 * 			Program takes an array of daily stock prices and k.
 *
 *  Created on: Oct 28, 2018
 *      Author: subha
 */

// Solution:
//			Maximum profit at ith day could be due to selling the stock on that day or not doing anything.
//			If we make kth sell on ith day then we need to buy on some day j (j<i) and make (k-1) buy and
//			sell before j.
//
//			Let Profit[t][i] stores maximum profit using at most t transactions up to day i (including i).
//			There are two options: either make kth sell on ith day or do nothing.
//
//			So, Profit(k,i) = Max {  Max over j<i { Price(i) - Price(j) + Profit(k-1,j-1)}
//								   , Profit(k,i-1) }
// Time complexity: O(k * n^2)
// Space complexity: O(kn)

#include <bits/stdc++.h>
using namespace std;

int MaxProfitAtMostKBuySell(const vector<int>& prices, int k)
{
	int n=prices.size();
	// profit[t][i] stores maximum profit using at most t transactions up to day i (including i)
	int profit[k+1][n];

	// For day 0, you can't earn money irrespective of how many times you trade
	for (int i = 0; i <= k; i++) {
		profit[i][0] = 0;
	}

	// profit is 0 if we don't do any transaction (i.e. k =0)
	for (int i = 0; i < n; i++) {
	    profit[0][i] = 0;
	}

	// Fill up the table in bottom up manner
	for(int x=1 ; x<=k ; ++x) {
		for(int i=1; i<n ; ++i) {
			int max_so_far = numeric_limits<int>::min();
			for(int j=0 ; j<i ; ++j) {
				// Max over all days j<i
				max_so_far = max(max_so_far, (j>0 ? profit[x-1][j-1]: 0) - prices[j]);
			}
			profit[x][i] = max(max_so_far + prices[i], profit[x][i-1]);
		}
	}
	return profit[k][n-1];
}

// One observation is that we are looping over j=0 to i-1 over and over again to find max.
// But as we increase i, only one new item is getting added to the previously compared items.
// So if we store what we found max last time then new max can be computed in O(1).
// So, we can do the computation while looping over the outer loop. So the inner two loop can be
// combined as one loop.
//
// Time complexity: O(kn)
// Space complexity: O(kn)

int MaxProfitAtMostKBuySellOpt1(const vector<int>& prices, int k)
{
	int n=prices.size();
	// profit[t][i] stores maximum profit using at most t transactions up to day i (including i)
	int profit[k+1][n];

	// For day 0, you can't earn money irrespective of how many times you trade
	for (int i = 0; i <= k; i++) {
		profit[i][0] = 0;
	}

	// profit is 0 if we don't do any transaction (i.e. k =0)
	for (int i = 0; i < n; i++) {
	    profit[0][i] = 0;
	}

	// Fill up the table in bottom up manner
	for(int x=1 ; x<=k ; ++x) {
		int previous_max = numeric_limits<int>::min();
		for(int i=1; i<n ; ++i) {
			previous_max = max(previous_max, profit[x-1][i-1] - prices[i-1]);
			profit[x][i] = max(previous_max + prices[i], profit[x][i-1]);
		}
	}
	return profit[k][n-1];
}

// Space complexity can be further reduced, as we only look at profit from the last day
// profit[x][i-1] and profit[x-1][i-1].
// So we don't need to look at days beyond i-1. So actually we do not need those rows.
//
// But while computing for ith day and xth transaction (i-1)th day's xth transaction should
// be available.
// So all computation for (i-1)th day has to finish before ith day. So the loop has to done
// in the other order. Day first then by transaction.
//
// Again for ith day xth transaction, (i-1)th day (x-1)th profit should also be available.
// But if we do iteration of transaction from 1 to k then when we compute profit[x], the
// profit[x-1] will store result of ith day. So the iteration of the transaction will have
// to be done in decreasing order, so that profit[x-1] stores result of (i-1)th day.
//
// Time complexity: O(kn)
// Space complexity: O(k)

int MaxProfitAtMostKBuySellOpt2(const vector<int>& prices, int k)
{
	int n=prices.size();
	// profit[t] stores maximum profit using at most t transactions up to day (i-1)
	// while making ith iteration on day. We are reusing the row.
	int profit[k+1];

	// For day 0, you can't earn money irrespective of how many times you trade
	for (int i = 0; i <= k; i++) {
		profit[i] = 0;
	}

	// Now previous max for each transaction has to be maintained separately, as we are
	// not finishing one transaction first.
	// Previous max for 1st day is the profit by buying on day 1.
	vector<int> previous_max (k+1, -prices[0]);

	for(int i=1; i<n ; ++i) {
		for(int x=k ; x>=1 ; --x) {
			profit[x] = max(previous_max[x] + prices[i], profit[x]);
			previous_max[x] = max(previous_max[x],  profit[x-1] - prices[i-1]);
		}
	}

	return profit[k];
}


int main()
{
	int k = 2;
	vector<int> prices = { 10, 22, 5, 75, 65, 80 };

	cout << "Maximum profit is: " << MaxProfitAtMostKBuySell(prices, k) << endl;

	cout << "Maximum profit is: " << MaxProfitAtMostKBuySellOpt1(prices, k) << endl;

	cout << "Maximum profit is: " << MaxProfitAtMostKBuySellOpt2(prices, k) << endl;

	return 0;
}
