/*
 * 00.BasicHashTable.cpp
 *
 * Problem: Implement a basic hash table
 *
 *  Created on: Feb 18, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: This is a hash table with chaining to resolve conflict

// Node for storing key value pair with next pointer for chaining
template<typename K, typename V>
struct HashNode
{
	K key;				// key
	V value;			// value
	HashNode* next;		// next node with same key

	HashNode(K& k, V& v, HashNode* n=nullptr) : key(k), value(v), next(n) {}
};

// Generic hash function
template<typename K>
struct HashFunction {
	size_t operator ()(const K& key, size_t modulus) const
	{
		return (*(reinterpret_cast<const size_t*>(&key))) % modulus;
	}
};

// Specialized for string
template<>
struct HashFunction<string> {
	size_t operator()(const string& key, size_t modulus) const
	{
		const int Prime = 997;
		size_t val = 0;
		for(char c: key) {
			val = (val * Prime + c) % modulus;
		}
		return val;
	}
};

// Hash table
template<typename K, typename V, typename Func>
struct MyHashTable
{
	HashNode<K,V> **table;
	Func hashFunc;
	int capacity;

	MyHashTable(int C=32) : capacity(C) {
		//table = new HashNode<K,V> *[capacity]();
		table = new HashNode<K,V> *[capacity];
	}

	// Returns iterator and bool as unordered_map::insert
	// For us pointer will work as iterator
	pair<HashNode<K,V>* ,bool> put(K key, V val) {

		size_t index = hashFunc(key, capacity);
		HashNode<K,V>* start = table[index];
		bool found = false;

		HashNode<K,V>* p;
		for(p = start; p != nullptr ; p = p->next) {
			if(p->key == key) {
				found = true;
				break;
			}
		}

		if(found) {
			p->value = val;
			return make_pair(p, false);
		} else {
			HashNode<K,V>* n = new HashNode<K,V>(key, val, start);
			table[index] = n;
			return make_pair(n,true);
		}
	}

	// STL find returns iterator, we will return pointer to hash node
	V* get(K key)
	{
		size_t index = hashFunc(key, capacity);
		HashNode<K,V>* start = table[index];

		for(HashNode<K,V>* p = start ; p != nullptr ; p = p->next)
		{
			if(p->key == key)
				return new V(p->value);
		}

		return nullptr;
	}
};


int main()
{
	MyHashTable<string, int, HashFunction<string>> stringMap;  // Use specialized hash function

	stringMap.put("abc",3);
	stringMap.put("pui",70);
	stringMap.put("tito",44);

	int* ret = stringMap.get("pui");
	cout << ((ret != nullptr) ? *ret : -1) << endl;

	ret = stringMap.get("jeet");
	cout << ((ret != nullptr) ? *ret : -1) << endl;

	ret = stringMap.get("tito");
	cout << ((ret != nullptr) ? *ret : -1) << endl;


	MyHashTable<int, int, HashFunction<int>> intMap;  // Use generic hash function

	intMap.put(2,3);
	intMap.put(4,5);
	intMap.put(6,7);

	ret = intMap.get(4);
	cout << ((ret != nullptr) ? *ret : -1) << endl;

	ret = intMap.get(44);
	cout << ((ret != nullptr) ? *ret : -1) << endl;

	ret = intMap.get(6);
	cout << ((ret != nullptr) ? *ret : -1) << endl;
}
