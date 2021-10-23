/*
 * zigzag-conversion.cpp
 *
 *  Created on: Feb 3, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string convert(string s, int n) {
        if(n < 1 || n >= s.length()) {
            return s;
        }
    	int dmax = (n == 1) ? 1 : ((n-1) * 2);
    	int dcurr = dmax;
    	string res = "";
    	res.reserve(s.size());

    	for(int i = 0 ; i < n ; ++i) { //ith row
    		int j = i;
    		while(j < (int)s.length()) {
    			res += s[j];
    			if(dcurr > 0) {
        			j += dcurr;
        			if(j < (int)s.length()) {
        				res += s[j];
        				if(dmax != dcurr) {
        					j += (dmax - dcurr);
        				} else {
        					j += dcurr;
        				}
        			}
    			} else {
    				j += dmax;
    			}
    		}
    		dcurr -= 2;
    	}

    	return res;
    }
};

int main() {
	Solution obj;

	cout << obj.convert("PAYPALISHIRING", 3) << endl; //PAHNAPLSIIGYIR
	cout << obj.convert("PAYPALISHIRING", 4) << endl; //PINALSIGYAHRPI
}
