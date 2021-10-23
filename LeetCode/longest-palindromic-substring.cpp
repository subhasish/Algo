/*
 * longest-palindromic-substring.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Interestingly DP solution takes O(n^2) time and O(n^2) space but the non DP solution takes O(n^2) time
// but takes O(1) space

class SolutionNonDP {

	pair<int,int> maxGrownFromCenter(const string& s, int i) {
		int l=i, r=i, r_even = -1;
		int max_start=i,max_len = 1;
		if(r< (int)s.length() && s[r] == s[r+1]) {
			r_even = r+1;
			max_len = 2;
		}

		while(l>=0 && r< (int)s.length()) {
			if(s[l] == s[r]) {
				if(r-l+1 > max_len) {
					max_len = r-l+1;
					max_start = l;
				}
			} else {
				break;
			}
			--l; ++r;
		}
		if(r_even >0 ) {
			l = i;
			while(l>=0 && r_even< (int)s.length()) {
				if(s[l] == s[r_even]) {
					if(r_even-l+1 > max_len) {
						max_len = r_even-l+1;
						max_start = l;
					}
				} else {
					break;
				}
				--l; ++r_even;
			}
		}
		return make_pair(max_start,max_len);
	}
public:
    string longestPalindrome(string s) {
        // From each center point try to grow the palindrome
        int max_len = 1, max_start = 0;
        for(size_t i=0 ; i<s.length() ; ++i) {
            pair<int, int> start_len = maxGrownFromCenter(s, i);
            if(start_len.second > max_len) {
            	max_len = start_len.second;
            	max_start = start_len.first;
            }
        }

        return s.substr(max_start, max_len);
    }
};

class SolutionDP {
public:
    string longestPalindrome(string s) {
        // dp[i][sz] = is the length of the longest palindrome starting at i and of size sz
        int dp[s.length()][s.length()+1];

        int max_len = 1, max_start = 0;
        for(size_t i=0 ; i<s.length() ; ++i) {
            dp[i][0] = 0;
            dp[i][1] = 1;
            if(i<s.length()-1 && s[i] == s[i+1]) {
            	dp[i][2] = 2;
            	max_len = 2;
            	max_start = i;
            } else {
            	dp[i][2] = 0;
            }
        }


        for(size_t sz=3 ; sz<=s.length() ; ++sz) {
            for(size_t i=0 ; i+sz-1<s.length() ; ++i) {
                dp[i][sz] = (dp[i+1][sz-2] > 0 && s[i] == s[i+sz-1]) ?
                                    sz : 0;
                if(dp[i][sz] > max_len) {
                    max_len = dp[i][sz];
                    max_start = i;
                }
            }
        }

        return s.substr(max_start, max_len);
    }
};

int main() {
	SolutionNonDP obj;

	cout << obj.longestPalindrome("babad") << endl;
	cout << obj.longestPalindrome("cbbd") << endl;
	cout << obj.longestPalindrome("wsegwgehrrherhere") << endl;
}

