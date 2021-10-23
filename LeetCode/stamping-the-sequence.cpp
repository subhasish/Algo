/*
 * stamping-the-sequence.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
	bool match(const string& str, int index, const string& pat) {
		int i = index;
		for( ; (i-index) < (int)pat.size() && i < (int)str.size() ; ++i) {
			if(str[i] != '?' && str[i] != pat[i-index]) {
				return false;
			}
		}
		if(i-index == (int)pat.size()) {
			return true;
		} else {
			return false;
		}
	}
public:
    vector<int> movesToStamp(string stamp, string target) {
        vector<int> res;
        int sz = (int) stamp.size();
        string mask (sz, '?');
        string end(target.size(), '?');

        size_t pos = 0;
        while((pos = target.find(stamp, pos)) != string::npos) {
        	target.replace(pos, sz, mask);
        	res.emplace_back(pos);
        	++pos;
        }

//        cout << target << endl;

        while(target != end) {
        	bool matchFound = false;
        	for(int i=0 ; i+sz-1 < (int)target.size() ; ++i) {
        		if(target.substr(i, sz) == mask) {
        			continue;
        		}
        		if(match(target, i, stamp)) {
        			res.emplace_back(i);
        			target.replace(i, sz, mask);
        			matchFound = true;
        			break;
        		}
        	}
        	if(!matchFound) {
        		return {};
        	}
        }

        reverse(res.begin(), res.end());
        return res;
    }
};


void printV(const vector<int>& A) {
	for(const int& a: A) {
		cout << a <<", ";
	}
	cout << endl;
}
int main () {
	Solution obj;
	vector<int> a = obj.movesToStamp("abc", "ababccabcccabcbc");

	printV(a);
}
