/*
 * guess-number-high-or-low.cpp
 *
 *  Created on: Jan 27, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;



class Solution {
	int N;
	int guess(int num) {
		if(num == N) return 0;
		if(num > N) return 1;
		return -1;
	}

public:
	Solution(int num) : N(num) {	}
    int guessNumber(int n) {
        int lo = 1, hi=n;
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            int res = guess(mid);
            if(res == 0) {
                return mid;
            } else if(res < 0) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }
};


int main() {
	Solution obj(6);

	cout << obj.guessNumber(10) << endl;
}
