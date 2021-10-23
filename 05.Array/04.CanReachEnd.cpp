/*
 * 4.CanReachEnd.cpp
 *
 * Problem: Given an array A, where A[i] = allowed number of steps in forward direction,
 *          Find out whether end of array can be reached from the start.
 *
 *  Created on: Aug 16, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;

// We can traverse the array and track farthest position we can reach
// For a position i, if farthest can be reached is less than i, then we cannot go farther
bool CanReachEnd(VI A)
{
	unsigned int farthestCanReach=0;
	// farthestCanReach >= i so that we can reach i before moving from i
	for(unsigned int i=0; i<A.size() && farthestCanReach >= i && farthestCanReach < A.size(); i++)
	{
		farthestCanReach = max(farthestCanReach, i+A[i]);
	}

	if(farthestCanReach >= A.size()-1)
		return true;
	else
		return false;
}


// Find minimum number of steps to reach the end.
bool MinimumStepForEnd(VI A, unsigned int& result)
{
	VI minStep(A.size(),A.size());

	if(!CanReachEnd(A))
		return false;

	minStep[0]=0;

	// Simple DP: minimum of existing steps or step through node i
	for(unsigned int i=0; i<A.size() ; ++i)	{
		for( int j=1; j<=A[i] ; j++) {
			minStep[i+j] = min(minStep[i]+1,minStep[i+j]);
		}
	}
	result = minStep[A.size()-1];
	return true;
}

void PrintMinStep(VI A)
{
	unsigned int res;
	bool canReach;

	canReach = MinimumStepForEnd(A, res);
	if(canReach)
		cout << "Minimum number of steps: " << res << endl;
	else
		cout << "End cannot be reached." << endl;
}

int main()
{
	cout << CanReachEnd({2,4,1,1,0,2,3}) << endl;
	cout << CanReachEnd({0}) << endl;
	cout << CanReachEnd({3,2,0,0,2,0,1}) << endl;

	PrintMinStep({2,4,1,1,0,2,3});
	PrintMinStep({0});
	PrintMinStep({3,2,0,0,2,0,1});
}


