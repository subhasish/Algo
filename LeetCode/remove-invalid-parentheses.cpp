/*
 * remove-invalid-parentheses.cpp
 *
 *  Created on: Apr 8, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool isValid(const string& s) {
        int count = 0;
        for(int i=0 ; i<(int)s.length() ; ++i) {
            if(s[i] == '(') {
                ++count;
            } else if(s[i] == ')'){
                --count;
            }

            if(count < 0) {
                return false;
            }
        }

        return count == 0;
    }

    void helper(const string& s, int curr_idx, int diff, string& part, unordered_set<string>& result) {
        if(curr_idx == (int)s.length()) {    // reached end; check and add to result
            if(isValid(part)) {
                if(result.empty() || (*result.begin()).length() == part.length()) {
                    result.emplace(part);
                } else {
                    if((*result.begin()).length() < part.length()) {
                        result.clear();
                        result.emplace(part);
                    }
                }
            }
            return;
        }


        // For '(' and ')' try both options adding next char and ignoring next char
        if(s[curr_idx] != '(' || s[curr_idx] != ')') {
            helper(s, curr_idx+1, diff, part, result);
        }

        if(diff < 0 || (diff == 0 && s[curr_idx] == ')')) {     //already invalid
        	return;
        }


        part.push_back(s[curr_idx]);
        if(s[curr_idx] == '(') {
            ++diff;
        } else if (s[curr_idx] == ')') {
            --diff;
        }

        helper(s, curr_idx+1, diff, part, result);
        part.pop_back();
    }

public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> result;
        unordered_set<string> result_set;
        string part;
        part.reserve(s.size());
        helper(s, 0, 0, part, result_set);
        if(result_set.empty()) {
            result_set.emplace("");
        }
        for(auto ss: result_set) {
            result.emplace_back(ss);
        }
        return result;
    }
};

int main() {
	Solution obj;
	string s;

	s = ")(f";
	vector<string> res = obj.removeInvalidParentheses(s);

	for(string ss: res) {
		cout << "\"" << ss << "\"" <<endl;
	}

}
