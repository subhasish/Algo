/*
 * 6.BuyAndSellStockOnce.cpp
 *
 * Problem: Given an array of stock prices of different days,
 *          find maximum profit that can be made by buying and selling stock.
 * Hint:
 *          It is not as simple as finding maximum and minimum and taking their difference,
 *          as minimum can appear after maximum.
 *
 *  Created on: Aug 19, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;
typedef vector<double> VD;

double BuyAndSellStockOnce(VD A)
{
	// It is clear that we will have to maintain minimum so far and maximum profit so far
	double minSoFar  = numeric_limits<double>::max();
	double maxProfit = 0;
	for(double d: A) {
		double profit = d - minSoFar;
		if(maxProfit < profit) {
			maxProfit = profit;
		}
		if(minSoFar > d) {
			minSoFar = d;
		}
	}
	return maxProfit;
}

int main()
{
	cout << BuyAndSellStockOnce({310,315,275,295,260,270,290,230,255,250}) << endl;
}
