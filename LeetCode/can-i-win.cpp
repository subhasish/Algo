/*
 * can-i-win.cpp
 *
 *  Created on: Jan 27, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// The state of the game is what numbers are left. Total need not to be tracked as total is the
// sum of the numbers used. But total can be passed for ease.
// Top down DP seems to solve the problem easily. Other ways to map problem of F(n,t) to F(n-1,*)
// did not work.
// What numbers left can be tracked by using bits as there as less than 20 of them.
// If i th number is left we can use ith bit as 1 from LSB.
//
// Base case is if total remaining is less than maximum then current player win.
// Also be careful about the case when sum of all numbers cannot make to total.

class Solution {
	const int max_possible = 20;
	int totalLeft(const int& state) {
		int res = 0;
		for(int i=1 ; i<=max_possible ; ++i) {
			if(isPresent(state,i)) {
				res += i;
			}
		}
		return res;
	}
	bool isPresent(const int& state, int pos) {
		return (state & (1 << (pos-1))) > 0;
	}
	void markUsed(int& state, int pos) {
		state &= ~(1 << (pos-1));
	}
	void markUnused(int& state, int pos) {
		state |= (1 << (pos-1));
	}
	int maxAvailable(const int& state) {
		int res = 0;
		for(int i=1 ; i<=max_possible ; ++i) {
			if(isPresent(state,i)) {
				res = i;
			}
		}
		return res;
	}
	bool Helper(int max_num, int total, int state, unordered_map<int, bool>* table_ptr) {
		if(maxAvailable(state) >= total) {	// Base case
			return true;
		}
		if(totalLeft(state) < total) {
			return false;
		}
		unordered_map<int, bool>& table = *table_ptr;

		if(table.find(state) != table.end()) {
			return table[state];
		}

		for(int i=1 ; i<=max_num ; ++i) {
			if(isPresent(state,i)) {
				markUsed(state, i);

				bool res = Helper(max_num, total-i, state, table_ptr);

				markUnused(state, i);
				if(!res) {
					table[state] = true;
					return true;
				}
			}
		}
		table[state] = false;
		return false;
	}
public:
    bool canIWin(int max_num, int total) {
        //table[i] = Is it possible first player can win if state of the game is
    	//			 depicted by i

        unordered_map<int, bool> table;

        int state = 0;
        for(int i=1 ; i<=max_num ; ++i) {
        	markUnused(state, i);
        }
        bool win = Helper(max_num, total, state, &table);
        return win;
    }
};

int main() {
	Solution obj;
	bool res;

	res = obj.canIWin(4,6);
	cout << res << endl;

	res = obj.canIWin(10,11);
	cout << res << endl;

	res = obj.canIWin(5,50);
	cout << res << endl;
}
