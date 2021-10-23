/*
 * palindrome-partitioning-ii.cpp
 *
 *  Created on: Feb 5, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class SolutionMemLimit {
    bool IsPalindrome(const string& S)
    {
        for(int i=0, j=S.length()-1 ; i<j ; ++i, --j) {
            if(S[i] != S[j]) {
                return false;
            }
        }
        return true;
    }
public:
    int minCut(const string& s) {
        if(s == "") {
            return -1;
        }
        // DP[i] stores the result vector for prefix s[0..i]
	    vector<int> DP(s.size());
        string suff = "";
        suff.reserve(s.size());

        //For base case no cut
        DP[0] = 0;

        for(size_t i=1 ; i < s.size() ; ++i) {  // for all prefix s[0..i]
            DP[i] = numeric_limits<int>::max();
            for(size_t j=0 ; j <= i ; ++j) {    // for all suffix s[j..i]
                suff = s.substr(j, i-j+1);
                if(IsPalindrome(suff)) {
                    if(j==0) {
                        DP[i] = 0;
                    } else {
                        DP[i] = min(DP[i], DP[j-1] + 1);
                    }
                }
            }
        }

        return DP[s.size()-1];
    }
};

class Solution {
public:
    int minCut(const string& s) {
        if(s == "") {
            return -1;
        }
        // DP[i] stores the result vector for prefix s[0..i]
	    vector<int> DP(s.size());

	    //start with maximum number of cuts possible in string s[0..i] and then we would try to minimize
	    for(size_t i = 0 ; i < s.size() ; ++i) {
	    	DP[i] = i;
	    }

        for(int i=0 ; i < (int)s.size() ; ++i) {  // considering all palindromes centering at i

        	//considering odd length palindrome. j is the size of the palindrome from the center
        	for(int j=1 ; i-j >= 0 && i+j < (int)s.size() ; ++j) {
        		if(s[i-j] == s[i+j]) {
        			DP[i+j] = min(DP[i+j], (i-j > 0 ? DP[i-j-1] + 1: 0));
        		} else {
        			DP[i+j] = min(DP[i+j], DP[i+j-1]+1);
        			break;
        		}
        	}

        	//considering even length palindrome. j is the size of the palindrome from the center
        	//i is the left of the center two
        	for(int j=0 ; i-j >= 0 && i+1+j < (int)s.size() ; ++j) {
        		if(s[i-j] == s[i+1+j]) {
        			DP[i+1+j] = min(DP[i+1+j], (i-j > 0 ? DP[i-j-1] + 1 : 0));
        		} else {
        			DP[i+1+j] = min(DP[i+1+j], DP[i+j]+1);
        			break;
        		}
        	}
        }

        return DP[s.size()-1];
    }
};

int main() {
	SolutionMemLimit obj;
	string s;
	s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	int res = obj.minCut(s);
	cout << res << endl;

	Solution ob;
	res = ob.minCut(s);
	cout << res << endl;

	s = "aab";
	res = ob.minCut(s);
	cout << res << endl;

}

