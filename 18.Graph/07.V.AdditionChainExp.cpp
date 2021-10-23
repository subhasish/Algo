/*
 * 07.V.AdditionChainExponentiation.cpp
 *
 * Problem: An Addition chain is a finite sequence <1,2,...,n> where each element after first is
 * 			sum of two previous elements where a number can be added to itself as well.
 * 			For example 15 can be computed by following 2 addition chains:
 * 			1) 1,2,4,8,12,14,15
 * 			2) 1,2,3,5,10,15
 * 			3) 1,2,3,6,12,15
 * 			It is not obvious but the second and third ones are the shortest chain to compute 15.
 *
 * 			Given a positive integer n, compute the shortest addition chain that results n?
 *
 *  Created on: Jul 5, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
// 			Shortest path, seems like BFS. All numbers from previous levels should be considered
//			before considering numbers from current level. Seems like level-by-level processing.
//
//			But actually it is lot harder than that. Here two numbers are generating a number
//			And the resultant sequence is the union of the sequence corresponding to the two numbers.
//
//			Also the minimum resultant may not be from the minimum of the two. Some longer two
//			may had more overlapping and result minimum for the union. So we need to consider
//			all the sequence generating a number for future use.
//
//			Also all generating sequence of smaller number should be generated first. So that
//			for larger numbers we consider all possible sequences and we do not need to revisit.
//
//			This boils down to a recursive/dynamic programming algorithm.
//
// Time complexity:
//			Each number from 1 to n has to be considered. Each number i will have 2 sets to combine.
//			Size of each set for a number i can potentially be 2^(i-1); each number from 1 to (i-1)
//			can either be in the set or not.
//			So exponential time.


namespace std {
	template<>
	struct hash<set<int>> {
		size_t operator()(const set<int> s) const {
			size_t res = 0;
			for(const int i: s) {
				res ^= hash<int>()(i);
			}
			return res;
		}
	};
}

typedef vector<int> VI;
typedef set<int> SI;				//NOTE: Using set as it has its equality operator built in
//typedef set<SI> SSI;
typedef unordered_set<SI> SSI;		//NOTE: Need the hash function to make set<int> as key of unordered_set

unordered_map<int, SSI> res_map;

// Do not need distance, as once a number is visited it is its minimum distance
// Maintain a map with a number and the previous

void PrintSI(const SI& si)
{
	for(const int i: si) {
		cout << i << ", ";
	}
	cout << endl;
}

void PrintSSI(SSI& ssi)
{
	for(const auto& si: ssi) {
		cout << "New Set: ";
		PrintSI(si);
	}
}

SSI ShortestAdditionChainHelper(int n)
{
	SSI result;

	if(n<=1) {
		SI one;
		one.emplace(1);
		result.emplace(one);

		return result;
	}

	if(res_map.find(n) != res_map.end()) {
		return res_map[n];
	}

	for(int i=1; i<=n/2 ; ++i) {
		int j=n-i;
		SSI res1 = ShortestAdditionChainHelper(i);
		SSI res2 = ShortestAdditionChainHelper(j);

		for(const auto& s1: res2) {
			for(const auto& s2: res1) {
				SI s = s1;
				for(int x: s2) {
					s.emplace(x);
				}
				s.emplace(i);
				s.emplace(j);
				s.emplace(n);
				result.emplace(s);
			}
		}
	}

	res_map[n] = result;
	return result;
}


SI ShortestAdditionChain(int n) {
	SSI res_set;
	SI res;

	res_set = ShortestAdditionChainHelper(n);

	for(const auto& s: res_set) {
		if(res.empty()) {
			res = s;
		} else {
			if(res.size() > s.size()) {
				res = s;
			}
		}
	}

	return res;
}


int main()
{
	int n = 15;
	SI res = ShortestAdditionChain(n);

	cout << "Shortest chain for " << n << ":" << endl;
	for(int i: res) {
		cout << i << ", ";
	}
	cout << endl;
}
