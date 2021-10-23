/*
 * 00.STLMapIterate.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;


void DFS(const char curr, const unordered_map<char, unordered_set<char>>& G) {
	cout << "Traversing: " << curr << endl;
	if(G.find(curr) == G.end()) {
		return;
	}

	for(auto ch: G.at(curr)) {
		DFS(ch, G);
	}
}

int main() {
	unordered_map<char, unordered_set<char>> G;

	G['c'].emplace('b');
	G['b'].emplace('a');

	for(auto it : G) {
		cout << "Starting with: " << it.first << endl;
		DFS(it.first, G);
	}
}


