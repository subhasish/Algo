/*
 * regular-expression-matching.cpp
 *
 *  Created on: May 3, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool isMatchFromHere(string& s, string& p, size_t si, size_t pi) {
        if(pi == p.length()) {
            if(si == s.length()) {
                return true;
            } else {
                return false;
            }
        } else if(si == s.length()){
            if(pi+1 < p.length() && p[pi+1] == '*') {
                return isMatchFromHere(s, p, si, pi+2);
            } else {
                return false;
            }
        } else {
            if(pi+1 < p.length() && p[pi+1] == '*') {
                if(p[pi] == '.' || s[si] == p[pi]) {
                    return isMatchFromHere(s, p, si, pi+2) || isMatchFromHere(s, p, si+1, pi);
                } else {
                    return isMatchFromHere(s, p, si, pi+2);
                }
            } else if(p[pi] == '.' || s[si] == p[pi]) {
                return isMatchFromHere(s, p, si+1, pi+1);
            } else {
                return false;
            }
        }
    }
public:
    bool isMatch(string s, string p) {
        return isMatchFromHere(s, p, 0, 0);
    }
};

int main() {
	string s, p;
	s = "";
	p = "a*c*";
	Solution obj;

	cout << obj.isMatch(s,p) << endl;
}

