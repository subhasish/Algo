/*
 * Trie.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    unordered_map<char, unique_ptr<TrieNode>> next;
    bool isEnd;
};

unique_ptr<TrieNode> getNewTrieNode() {
    unique_ptr<TrieNode> t(new TrieNode());
    t->isEnd = false;
    return t;
}

void TrieInsert(unique_ptr<TrieNode>& root, string s) {
    TrieNode* p = root.get();

    for(char ch: s) {
        if(p->next.find(ch) == p->next.end()) {
            p->next[ch] = move(getNewTrieNode());
        }
        p = p->next[ch].get();
    }
    p->isEnd = true;
}

void TrieGetAllAbbr(unique_ptr<TrieNode>& root, string prefix, vector<string>& result) {
	if(root != nullptr) {

		if(root->isEnd) {
            result.emplace_back(prefix);
            return;
        }

        for(auto it = root->next.begin() ; it != root->next.end() ; ++it) {
            TrieGetAllAbbr(it->second, prefix + (it->first), result);
        }
    }
}

vector<string> GetAllTrieStrings(vector<string>& dict) {

	//Insert all
	unique_ptr<TrieNode> root = move(getNewTrieNode());
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

