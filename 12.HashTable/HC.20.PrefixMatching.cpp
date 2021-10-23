/*
 * HC.20.PrefixMatching.cpp
 *
 * Problem: Given a query string and a dictionary of strings find the shortest prefix of the query
 * 			string that is not a prefix of any of any strings in the dictionary.
 *
 *  Created on: Dec 22, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;


// Solution:
//			Typical application of trie.

struct Trie {
	struct TrieNode {
		bool isString = false;								// Flag if end of a string
		unordered_map<char, unique_ptr<TrieNode>> leaves;	// set of pointers to next level strings
	};

	unique_ptr<TrieNode> root = make_unique<TrieNode>(TrieNode());

	bool Insert(const string& s) {
		auto* p = root.get();
		for(char c: s) {
			if(p->leaves.find(c) == p->leaves.end()) {
				p->leaves[c] = make_unique<TrieNode>(TrieNode());
			}
			p = p->leaves[c].get();
		}

		if(p->isString) {	// string already exists
			return false;
		} else {
			p->isString = true;
			return true;
		}
	}

	string GetShortestUniquePrefix(const string& s) {
		auto* p = root.get();
		string prefix;
		for(char c: s) {
			prefix += c;
			if(p->leaves.find(c) == p->leaves.end()) {
				return prefix;
			}
			p = p->leaves[c].get();
		}
		return "";
	}
};


string FindShortestPrefix(const string& s, const vector<string>& D) {
	Trie T;
	for(const string& word: D) {
		T.Insert(word);
	}

	return T.GetShortestUniquePrefix(s);
}

int main() {
	vector<string> D = {"dog", "be", "cut", "car", "category", "catsnip"};

	cout << FindShortestPrefix("cat", D) << endl;
	cout << FindShortestPrefix("cutting", D) << endl;
	cout << FindShortestPrefix("ant", D) << endl;
}
