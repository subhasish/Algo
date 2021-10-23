/*
 * 00.STLHashTable.cpp
 *
 * Problem: Use available STL hash function library like unordered_set and unordered_map
 * 			Important things are insert, find and iterator.
 *
 *  Created on: Feb 19, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// C++:
//		Insert/Emplace:	Inserts a new element and returns a pair of iterator and bool, where iterator point to the
//				newly inserted or existing element, and bool is true if element was newly added or false if already present.
//				Insertion only takes place if key is not equivalent to any other key in the container.
//
//				Emplace is better as it takes key/value. Insert takes iterator for the position to insert. But
//				insert also takes initializer list {key, value}
//
//		Erase: Delete an element. Can use both key and iterator
//
//		Operator[] : To update existing value use operator[] which basically return reference of the mapped value
//
//		Find: 	Returns pointer to iterator to the element if present, otherwise special iterator end()
//
//		Iterator: Iterator points to pair<key, value> while iterating over map
//				  Order is not fixed but guaranteed to cover all items between begin() and end()
//
//		hash<T>(): Hash method provides functions for hashing for the basic classes in C++, e.g., int, bool, string, unique_ptr, shared_ptr etc.

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

int main()
{
	unordered_map<int, int> table;

	auto ret = table.emplace(2,3);
	cout << "Success: " << ret.second << endl;

	// This insert should be unsuccessful
	ret = table.emplace(2,5);
	cout << "Success: " << ret.second << ", Val: " << ret.first->first << endl;

	// To update use operator[]
	table[2]=7;
	cout << "Val: " << table[2] << endl;

	table[3]=9;
	table[5]=25;

	// Iterating all items
	cout << "Iterating all items in map: " << endl;
	for(auto val: table) {
		cout << "Key: " << val.first  << ", Val: " << val.second << endl;
	}

	table.erase(3);
	table.erase(100);

	// Iterating all items after erase
	cout << "Iterating all items in map after erase: " << endl;
	for(auto val: table) {
		cout << "Key: " << val.first  << ", Val: " << val.second << endl;
	}

	unordered_set<int> myset;

	myset.emplace(3);
	myset.emplace(6);
	myset.emplace(9);

	cout << "Iterating all items in set: " << endl;
	for(int i: myset) {
		cout << "Item: " << i << endl;
	}

	size_t hash_val = hash<string>()("pui");
	cout << "Hash value of pui: " << hash_val << endl;


	//Complex: map of int to unordered_set of set
	unordered_map<int, unordered_set< set<int> > > map_set;

	unordered_set<set<int>> ussi;

	set<int> s1,s2,s3;
	unordered_set<set<int>> ss1,ss2,ss3;
	s1.emplace(1); s1.emplace(2); s1.emplace(3);
	s2.emplace(4); s2.emplace(5); s2.emplace(6);
	s3.emplace(7); s3.emplace(8); s3.emplace(9);

	ss1.emplace(s1); ss2.emplace(s2); ss3.emplace(s3);

	map_set[1] = ss1;
	map_set[2] = ss2;
	map_set[3] = ss3;
}
