/*
 * HC.32.CriticalHeight.cpp
 *
 * Problem: We are testing case/egg that can break after being dropped from certain height.
 * 			With other normal assumptions, we want to find the floor number of a building
 * 			from where onwards the case/egg will break.
 *
 * 			But the number of cases and number of drops is limited. Find the maximum number
 * 			of floor that can be measured, in the worst case.
 *
 * 			Example:
 * 			If we have 1 case and 5 drops, then highest we can measure is 5 floors.
 *
 * 			Note: The example in the book for 2 cases and 5 drops measuring 9 floors is wrong!
 *
 *  Created on: Jan 5, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Clarification:
//			How the problem uses term 'worst case' and 'maximum possible' can be confusing.
//			Worst case means, that if at any point a case breaks then we should be able to figure
//			the critical height using rest of the cases and drops.
//			Given that condition, 'maximum possible' means that without losing the chance of
//			finding the critical height, what is the maximum possible floor that can be measured.
//
//			Note that maximum can only be possible to test when the case does not break, that is we
//			can test higher number of floor.
//
//			Worst case, is the case of not considering being lucky; that testing an arbitrary floor and
//			case does not break, and then go on finding all floors above that.

// Solution:
//			Lets see the case for 2 cases and 5 drops. We can directly drop from 5th first.
//			If it breaks then we have 1 case and 4 drops remaining. We can detect the critical
//			floor from starting from 1 and then to 4, like similar we did for the case of 1 case
//			and 5 drops.
//			If it does not break then, the we do not need to test floors below 5 and then go
//			testing all the floors above like what we would have done if we had 2 cases and
//			4 drops, but measuring starts from floor 6.
//
//			So for general case, if there is 1 case and d drops, then the maximum we can measure is
//			d floors.
//
//			Otherwise for n cases and d drops we can directly start at floor number Solution(n-1,d-1)+1.
//			If the case breaks then we can find the solution using n-1 cases and d-1 drops.
//			If it does not break then we have n case and d-1 drops. So we can test Solution(n, d-1) more
//			floor on top of the Solution(n-1, d-1)+1 floors.
//			That is the maximum possible floors we can measure in worst case.
//
//			So, Solution(n, d) = Solution(n-1, d-1) + 1 + Solution(n, d-1)
//
//			We need to use DP/memoization so that we are not solving the same subproblem multiple times.
//
//			Just another observation is that if cases is more than the number of drops then it is not
//			useful.

int GetHeightHelper(int cases, int drops, vector<vector<int>>& F);

int GetHeight(int cases, int drops) {
	vector<vector<int>> F(cases+1, vector<int>(drops+1, -1));
	return GetHeightHelper(cases, drops, F);
}

int GetHeightHelper(int cases, int drops, vector<vector<int>>& F) {
	if(cases == 0 || drops == 0) {
		return 0;
	} else if (cases == 1) {
		return drops;
	}
//	else if(cases > drops) {
//		return GetHeightHelper(drops, drops, F);
//	}

	if(F[cases][drops] == -1) {
		F[cases][drops] = GetHeightHelper(cases, drops - 1, F) +
						  GetHeightHelper(cases - 1, drops - 1, F) + 1;
	}

	return F[cases][drops];
}


int main() {
	cout << "n=2, d=5; solution = " << GetHeight(2, 5) << endl;
	cout << "n=3, d=5; solution = " << GetHeight(3, 5) << endl;
	cout << "n=16, d=16; solution = " << GetHeight(16, 16) << endl;
	cout << "n=32, d=16; solution = " << GetHeight(32, 16) << endl;
	cout << "n=29, d=47; solution = " << GetHeight(29, 47) << endl;
}
