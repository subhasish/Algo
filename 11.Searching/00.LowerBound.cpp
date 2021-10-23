/*
 * 00.LowerBound.cpp
 *
 * Problem: Search lower bound in a collection in reverse sense.
 * 			That is the elements will in decreasing order and we need to find next smallest element.
 *
 * 			We can form a BST like map/set with custom comparator and use their in-built functions.
 *
 *  Created on: May 19, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

struct Key {
	int val;
};

struct CompKey {
	bool operator()(const Key& a, const Key& b) const {
		return a.val > b.val;
	}
};

int main() {
	vector<int> A = {9, 6, 5, 5, 4, 2, 1};

	cout << "Integer array lower bound: " << *lower_bound(A.begin(), A.end(), 5, greater<int>()) << endl;

	map<Key, string, CompKey> M = { {{9}, "h"}, {{6}, "f"}, {{4}, "e"}, {{2}, "d"}, {{5}, "a"}, {{5}, "b"}};

	auto lb = M.lower_bound(Key{5});
	cout <<  "Map lower bound: " << lb->first.val << endl;

	auto ub = M.upper_bound(Key{5});
	cout <<  "Map upper bound: " << ub->first.val << endl;
}

