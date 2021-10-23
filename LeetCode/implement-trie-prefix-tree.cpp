/*
 * implement-trie-prefix-tree.cpp
 *
 *  Created on: May 2, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> next;
    bool isLast;

    TrieNode() {
        isLast = false;
    }
    ~TrieNode() {
        for(auto it: next) {
            delete it.second;
        }
    }
};

class Trie {
    TrieNode *root;

public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    ~Trie() {
        delete root;
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* p = root;
        for(char ch: word) {
            if(p->next.find(ch) == p->next.end()) {
                p->next[ch] = new TrieNode();
            }
            p = p->next[ch];
        }
        p->isLast = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* p = root;
        for(char ch: word) {
            if(p->next.find(ch) == p->next.end()) {
                return false;
            }
            p = p->next[ch];
        }
        return p->isLast;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* p = root;
        for(char ch: prefix) {
            if(p->next.find(ch) == p->next.end()) {
                return false;
            }
            p = p->next[ch];
        }
        return true;
    }
};

int main() {
	 Trie* obj = new Trie();
	 string word = "apple";
	 obj->insert(word);
	 bool param_2 = obj->search(word);
	 cout << param_2 << endl;

	 string prefix = "app";
	 bool param_3 = obj->startsWith(prefix);
	 cout << param_3 << endl;
}
