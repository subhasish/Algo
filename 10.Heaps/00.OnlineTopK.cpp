/*
 * 00.OnlineTopK.cpp
 *
 * Problem: Given a stream (no backup or reading old values) of strings, compute k longest strings in that sequence
 *
 *  Created on: Jan 29, 2018
 *      Author: subha
 */


#include <bits/stdc++.h>

using namespace std;

// Solution: Finding K maximum elements is common case of min-heap.
//           If next element is larger than the minimum of top K elements then it can replace that one in top K


typedef vector<string> VS;

VS OnlineTopK(size_t k, istringstream* iss) {
	VS result;
	priority_queue<string, VS, function<bool(string&, string&)>>
			min_heap([] (string& s1, string& s2) { return s1.length() > s2.length(); } );

	string next;
	while(*iss >> next) {
		if(min_heap.size() < k) {
			min_heap.push(next);
		} else {
			if(next.length() > min_heap.top().length()) {
				min_heap.pop();
				min_heap.push(next);
			}
		}
	}

	// populate result
	while(!min_heap.empty()) {
		result.push_back(min_heap.top());
		min_heap.pop();
	}
	return result;
}


int main()
{
	string str = "earth neptune sun jupitar moon mercury saturn saturnerer";
	istringstream ss(str);


	VS res = OnlineTopK(5, &ss);

	for(string s: res) {
		cout << s << endl;
	}
}
