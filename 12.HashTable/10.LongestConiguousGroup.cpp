/*
 * 10.LongestConiguousGroup.cpp
 *
 * Problem: Write a program that takes a set of integers and returns largest subset of integers such that all the numbers in the
 * 			subset are contiguous
 *
 *  Created on: Feb 25, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Trying to grow the set around each element. As each element can be on only one group we can remove them from future consideration.

int FindLongestContiguousGroup(const vector<int>& Array)
{
	unordered_set<int> remaining_elements(Array.begin(), Array.end());

	int max_size = 0;
	while(!remaining_elements.empty())
	{
		int a = *remaining_elements.begin();
		remaining_elements.erase(a);
		int count = 1;

		int low = a-1, hi = a + 1;
		while(remaining_elements.find(low) != remaining_elements.end())
		{
			++count;
			remaining_elements.erase(low);
			--low;
		}
		while(remaining_elements.find(hi) != remaining_elements.end())
		{
			++count;
			remaining_elements.erase(hi);
			++hi;
		}

		if(max_size < count)
		{
			max_size = count;
		}
	}

	return max_size;
}


int main()
{
	cout << FindLongestContiguousGroup({3, -2, 9, 7, 8, 1, 2, 0, -1, 5, 8}) << endl;
}
