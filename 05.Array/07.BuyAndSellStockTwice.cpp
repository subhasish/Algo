/*
 * 6.BuyAndSellStockTwice.cpp
 *
 * Problem: An array of stock price is given. We can buy and sell stock twice,
 *          but second buy needs to happen after first sell.
 *
 *          Little complex version of the BuyAndSellStockOnce problem
 *
 *  Created on: Aug 19, 2017
 *      Author: subha
 */


#include <bits/stdc++.h>

using namespace std;

typedef vector<double> VD;

void PrintVecctor(VD& A)
{
	for(double i:A) {
		cout << i << " ";
	}
	cout << endl;
}


// General solution to this kind of problem is to:
//         partition the array, compute for each partition
//         and then combine results of each partition to get maximum.
// But here solution to subproblems are NOT unrelated.
//         Profit for a part monotonically increases with split size.
//         So, for first part, possible maximum profit will increase with increase in end date
//         And for last part, possible maximum profit will decrease with increase in start date
//
// So here shifting split to the right increases possible profit in the first part but decreases for last part
//
// A good way to find optimum is to create two arrays where ith element represent:
//   For array 1: possible maximum profit if we would have to sell before this date
//   For array 2: possible maximum profit if we would have to buy after this date
// Then we can sum that up for each date and get the maximum.

double BuyAndSellStockTwice(VD A)
{
	VD sellBeforeTodayProfit(A.size());
	VD buyAfterTodayProfit(A.size());

	//Forward phase: for each day store maximum profit if we sell before today
	double minSoFar = numeric_limits<double>::max();
	double maxProfit = 0;
	for(unsigned int i=0 ; i<A.size() ; i++) {
		double profit = A[i] - minSoFar;
		maxProfit = max(maxProfit, profit);
		minSoFar  = min(minSoFar, A[i]);
		sellBeforeTodayProfit[i] = maxProfit;
	}

	cout << "Profit if we sell before day i:  ";
	PrintVecctor(sellBeforeTodayProfit);

	//Backward phase: for each day store maximum profit if we buy after that day
	double maxSoFar = 0;
	maxProfit = 0;
	for(int i=A.size()-1 ; i>=0 ; i--) {
		double profit = maxSoFar - A[i];
		maxProfit = max(maxProfit, profit);
		maxSoFar  = max(maxSoFar, A[i]);
		buyAfterTodayProfit[i] = maxProfit;
	}

	cout << "Profit if we buy before after i: ";
	PrintVecctor(buyAfterTodayProfit);

	double totalMax = 0;
	for(unsigned int i=1; i<A.size(); i++) {
		double totalProfit = sellBeforeTodayProfit[i-1] + buyAfterTodayProfit[i];
		totalMax = max(totalMax, totalProfit);
	}

	return totalMax;
}


int main()
{
	cout << BuyAndSellStockTwice({12,11,13,9,12,8,14,13,15}) << endl;
}
