/*
 * palindrome-partitioning.cpp
 *
 *  Created on: Feb 5, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool IsPalindrome(string& s) {
        int i=0, j = (int)s.length()-1;
        while(i<j) {
            if(s[i] != s[j]) {
                return false;
            }
            ++i; --j;
        }
        return true;
    }

    void Helper(int end, const string& s, unordered_map<int, vector<vector<string>>>& table) {

        for(int j=0 ; j<=end ; ++j) {
            string suff = s.substr(j, end - j + 1);
            if(IsPalindrome(suff)) {
                if(j>0) {
                    vector<vector<string>> t = table[j-1];
                    for(vector<string>& vs: t) {
                        vs.emplace_back(suff);
                        table[end].emplace_back(vs);
                    }
                } else {
                    table[end].emplace_back(vector<string>({suff}));
                }
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        unordered_map<int, vector<vector<string>>> table;
        //table[i] represents the result set of decompositions of string[0..i]
        //Now if suffix is palindrome then we can add it to all existing sets of i

        vector<vector<string>> res;
        if(s == "") {
            return res;
        }

        for(int i=0 ; i< (int)s.length(); ++i) {
        	Helper(i, s, table);
        }

        return table[s.length()-1];
    }
};

int main() {
	Solution obj;
	vector<vector<string>> res = obj.partition("aab");

	for(const vector<string>& vs: res) {
		cout << "[";
		for(const string& s: vs) {
			cout << s << ", ";
		}
		cout << "]" << endl;
	}
}

