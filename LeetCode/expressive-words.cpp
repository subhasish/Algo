/*
 * expressive-words.cpp
 *
 *  Created on: May 9, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int expressiveWords(string S, vector<string>& words) {
        vector<pair<char,int>> S_count;
        for(int i = 0; i < (int)S.length() ; ++i) {
            int count = 1;
            while(i < (int)S.length() - 1 && S[i] == S[i+1]) {
                ++count;
                ++i;
            }
            S_count.emplace_back(make_pair(S[i], count));
        }

        int result = 0;
        for(string& q: words) {
            bool failed = false;
            int j = 0;
            for(int i = 0 ; i < (int)q.length() ; ++i, ++j) {
                int count = 1;
                while(i < (int)q.length() - 1 && q[i] == q[i+1]) {
                    ++count;
                    ++i;
                }
                if(j < (int)S_count.size() && S_count[j].first == q[i] &&
                   (S_count[j].second == count ||
                        (S_count[j].second > count && S_count[j].second >= 3)))
                {
                    continue;
                } else {
                    failed = true;
                    break;
                }
            }

            if(!failed && j == (int)S_count.size()) {
                ++result;
            }
        }
        return result;
    }
};


int main() {
	string s;
	vector<string> qs;

	Solution obj;

	s = "heeellooo";
	qs = {"hello", "hi", "helo"};
	cout << obj.expressiveWords(s, qs) << endl;

	s = "helloo";
	qs = {"hello", "hi", "helo"};
	cout << obj.expressiveWords(s, qs) << endl;

	s = "helloo";
	qs = {"helloo", "hi", "helo"};
	cout << obj.expressiveWords(s, qs) << endl;

	s = "abcd";
	qs = {"abc"};
	cout << obj.expressiveWords(s, qs) << endl;

}

