/*
 * 06.NearestRepetition.cpp
 *
 * Problem: Write a program which takes an array and find the distance between closest pair of duplicate entries.
 *
 *  Created on: Feb 23, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Maintain hash table of entries with latest position

typedef vector<int> VI;

int FindNearestRepetition(VI input)
{
	unordered_map<int, int> last_index;
	size_t min_dist = numeric_limits<size_t>::max();

	for(size_t i=0; i< input.size() ; ++i)
	{
		auto it = last_index.find(input[i]);
		if(it != last_index.end()) {
			min_dist = min(min_dist, i - last_index[input[i]]);
		}
		last_index[input[i]] = i;
	}

	return min_dist;
}


int main()
{
	cout << FindNearestRepetition({0,1,2,3,4,5,6,7,3,2,1,7}) << endl;
}
