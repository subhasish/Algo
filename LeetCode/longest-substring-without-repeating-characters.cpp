/*
 * longest-substring-without-repeating-characters.cpp
 *
 *  Created on: Feb 3, 2019
 *      Author: subha
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> table;
        int start = 0, end = 0, max_l = 0;
        while(end < (int) s.length()) {
            if(table.find(s[end]) != table.end()) {
                start = max(start, table[s[end]] + 1);
            }
            table[s[end]] = end;
            max_l = max(max_l, end - start + 1);
            ++end;
        }
        return max_l;
    }
};

int main() {
	Solution obj;
	cout << obj.lengthOfLongestSubstring("weerjrtdbwherjtnbwrhtjn") << endl;
}


