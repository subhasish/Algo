/*
 * HC.32.MinimumDrops.cpp
 *
 * Problem: We are testing case/egg that can break after being dropped from certain height.
 * 			With other normal assumptions, we want to find the floor number of a building
 * 			from where onwards the case/egg will break.
 *
 * 			But the number of cases and number of drops is limited. Find the minimum number
 * 			of drops required to find the critical floor from 1 to F floors using c cases.
 *
 * 			Note: This is a variant of the the problem HC.32.CriticalHeight.cpp
 *
 *  Created on: Jan 5, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;


// Solution:
// 			When we drop an case/egg from floor x there are two cases (1) it breaks, (2) it does not
//			break.
//			(1) If it breaks then we have to find the critical floor between 1 to (x-1) floors using
//				(c-1) cases.
//			(2) If it does not break then we need to find critical floor between (x+1) to F floors
//				using c cases.
//
//			So if we start at floor x then the number of drops needed at the worst case is the maximum
//			of the two.
//			To find the minimum overall, we need to consider all floors as x and then take the minimum.
//
//			Base case to the recursive solution is that when we have one floor we need one drop and if
//			have 0 floors then we need 0 drop.
//
//			Another base case for c is, if there is only 1 case then we need F drops in worst case.


int GetMinimumDropHelper(int cases, int floors, vector<vector<int>>& F);

int GetMinimumDrop(int cases, int floors) {
	vector<vector<int>> F(cases+1, vector<int>(floors+1, -1));
	return GetMinimumDropHelper(cases, floors, F);
}

int GetMinimumDropHelper(int cases, int floors, vector<vector<int>>& F) {
	// 0 or 1 floor need 0/1 drops
	if(floors == 0) {
		return 0;
	} else if (floors == 1) {
		return 1;
	}

	// for 1 case we need floors number of drops in worst case
	if(cases == 1) {
		return floors;
	}

	if(F[cases][floors] == -1) {
		int min_drop = numeric_limits<int>::max();
		for(int i=1 ; i<=floors ; ++i) {
			min_drop = min(min_drop,
						   max(GetMinimumDropHelper(cases-1, i - 1, F),
							   GetMinimumDropHelper(cases, floors-i, F)) + 1);
		}
		F[cases][floors] = min_drop;
	}

	return F[cases][floors];
}


int main() {
	cout << "cases=2, floor=36; minimum drop = " << GetMinimumDrop(2, 36) << endl;
}
