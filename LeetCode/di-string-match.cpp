/*
 * di-string-match.cpp
 *
 *  Created on: May 12, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> diStringMatch(string S) {
        int ni = 0, nd = S.length();

        vector<int> res(S.length() + 1);
        for(int i = 0 ; i < (int)S.length() ; ++i) {
            if(S[i] == 'I') {
                res[i] = ni++;
            } else if(S[i] == 'D') {
                res[i] = nd--;
            }
        }

        res[S.length()] = ni;
        return res;
    }
};

int main() {
	Solution obj;

	vector<int> res = obj.diStringMatch("IDID");
	for(auto i: res)
		cout << i << ", " << endl;
}


