/*
 * word-abbreviation.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

string abbr(string word, int prefix_len) {
    if(word.length() < 4) {
        return word;
    } else {
    	prefix_len = max(prefix_len, 1);
    	int num = word.length()-1-prefix_len;
        return word.substr(0, prefix_len) + ((num>0) ? to_string(num) : "") + word.back();
    }
}

struct TrieNode {
    unordered_map<char, TrieNode*> next;
    bool shared;
    int word_idxs;  //indices of all the words

    ~TrieNode() {
    	for(auto ch: next) {
    		delete ch.second;
    	}
    }
};

TrieNode* getNewTrieNode() {
    TrieNode* t = new TrieNode();
    t->shared = false;
    return t;
}

void TrieGetAllAbbr(TrieNode* root, string prefix, const vector<string> input, vector<string>& result) {
	if(root != nullptr) {
        for(auto it: root->next) {
        	if(!it.second->shared) {
        		int idx = it.second->word_idxs;
        		result[idx] = abbr(input[idx], prefix.length()+1);
        	}
        	else {
                TrieGetAllAbbr(it.second, prefix+it.first, input, result);
        	}
        }
    }
}

void TrieInsert(TrieNode* root, string s, int index) {
    TrieNode* p = root;
    if(p == nullptr) {
        p = getNewTrieNode();
    }

    for(char ch: s) {
        if(p->next.find(ch) == p->next.end()) {
            p->next[ch] = getNewTrieNode();
        } else {
        	p->next[ch]->shared = true;
        }
        p->word_idxs = index;
        p = p->next[ch];
    }
    p->word_idxs = index;
}

class Solution {
public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        vector<string> res(dict.size());

        // Form group of words that has same abbreviations
        unordered_map<string, unordered_set<int>> groups;
        for(int i=0; i< (int)dict.size() ; ++i) {
            groups[abbr(dict[i], 1)].emplace(i);
        }

        //Now form trie of each groups
        for(auto group: groups) {
            TrieNode* root = getNewTrieNode();
            for(int idx: group.second) {
                TrieInsert(root, dict[idx], idx);
            }

            TrieGetAllAbbr(root, "", dict, res);
        }

        for(int i=0; i< (int)res.size() ; ++i) {
        	if(res[i].length() == dict[i].length()) {
        		res[i] = dict[i];
        	}
        }

        return res;
    }
};


int main() {
	Solution obj;
	vector<string> dict = {"like","god","internal","me","internet","interval","intension","face","intrusion"};

	vector<string> abr = obj.wordsAbbreviation(dict);
	for(auto s: abr) {
		cout << s << ", ";
	}
	cout << endl;
}

