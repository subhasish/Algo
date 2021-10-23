/*
 * 05.KMostFrequent.cpp
 *
 * Problem: Given a list of strings find K most frequent strings.
 *
 *  Created on: Feb 22, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Store the frequencies in a hash table
//			 Then put them in a min-heap of size K similar to finding top K entries

typedef vector<string> VS;

typedef pair<string, int> PSI;
typedef vector<PSI> VPSI;

VS KMostFrequent(VS input, int K)
{
	unordered_map<string, int> freq;

	for(string s: input) {
		++freq[s];
	}

	priority_queue<PSI, VPSI, function<bool(PSI&, PSI&)>>
			min_heap([] (PSI& p1, PSI& p2) { return p1.second > p2.second; });

	int count = 0;
	for(auto it: freq)
	{
		++count;

		// Did easy implementation. But possible to avoid extra push by first checking with minimum in the min-heap
		min_heap.push(it);

		if(count > K)
		{
			min_heap.pop();
		}
	}

	VS res;
	while(!min_heap.empty())
	{
		res.push_back(min_heap.top().first);
		min_heap.pop();
	}
	return res;
}


int main()
{
	VS res = KMostFrequent({"pui", "tito", "jeet", "papai", "mampu", "banti", "pui", "tito", "jeet", "papai", "pui", "tito", "jeet"}, 4);

	cout << "Most frequents are:" << endl;
	for(string s: res)
	{
		cout << s << endl;
	}
}
