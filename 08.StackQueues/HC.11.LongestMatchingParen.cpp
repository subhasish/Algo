/*
 * HC.11.LongestMatchingParen.cpp
 *
 * Problem: Write a program that takes a input string made up of character '(' and ')' and
 * 			return the size of maximum length substring in which parentheses are matched.
 *
 * 			**Alert: Understood wrong problem first time. For input "((())()(()" the output
 * 			should be "(())()"
 *
 *  Created on: Nov 4, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			It is similar to doing parentheses matching that we do using stack. When an
//			opening parenthesis comes we push it in the stack and when a closing one comes
//			we pop one up from the stack.
//
//			One observation is that when we get a closing parenthesis that matches, the current
//			matching is from stack top to the current element. But there can be adjacent previous
//			matching which should also be counted. How to know about them.
//			One key observation is that those previous matching must have started after the current
//			top element of the stack that still not matched.
//
//			So if we store the position of the opening parenthesis in the stack then we can
//			compute the length of the current match based on its position.
//
//			So we can push the index of opening parenthesis and compute the length while popping.


int LongestMatchingParentheses(const string& s) {
	int max_length = 0, end = -1;

	stack<int> open_parent;
	for(size_t i=0; i<s.length() ; ++i) {
		if(s[i] == '(') {
			open_parent.push(i);
		} else if(s[i] == ')') {
			if(open_parent.empty()) {		// Not matching; next matching should start after it
				end = i;
			} else {
				open_parent.pop();
				int start = open_parent.empty() ? end : open_parent.top();
				int curr_length = i - start;
				if(max_length < curr_length) {
					max_length = curr_length;
				}
			}
		}
	}
	return max_length;
}

int main() {
	string s = "((())()(()";
	cout << LongestMatchingParentheses(s) << endl;
}

