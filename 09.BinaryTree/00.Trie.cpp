/*
 * Trie.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> next;
    bool isEnd;

    ~TrieNode() {
		for(auto ch: next) {
			delete ch.second;
		}
	}
};

TrieNode* getNewTrieNode() {
    TrieNode* t = new TrieNode();
    t->isEnd = false;
    return t;
}

void TrieInsert(TrieNode* root, string s) {
    TrieNode* p = root;
    if(p == nullptr) {
        p = getNewTrieNode();
    }

    for(char ch: s) {
        if(p->next.find(ch) == p->next.end()) {
            p->next[ch] = getNewTrieNode();
        }
        p = p->next[ch];
    }
    p->isEnd = true;
}

void TrieGetAllAbbr(TrieNode* root, string prefix, vector<string>& result) {
	if(root != nullptr) {

		if(root->isEnd) {
            result.emplace_back(prefix);
            return;
        }

        for(auto it: root->next) {
            TrieGetAllAbbr(it.second, prefix + (it.first), result);
        }
    }
}

vector<string> GetAllTrieStrings(vector<string>& dict) {

	//Insert all
	TrieNode* root = getNewTrieNode();
	for(int idx = 0 ; idx < (int)dict.size() ; ++idx) {
		TrieInsert(root, dict[idx]);
	}

	//Retrieve all
	vector<string> res;
	TrieGetAllAbbr(root, "", res);
	return res;
}


int main() {
	vector<string> dict = {"like","god","internal","me","internet","interval","intension","face","intrusion"};

	vector<string> abr = GetAllTrieStrings(dict);
	for(auto s: abr) {
		cout << s << ", ";
	}
	cout << endl;
}

