/*
 * 4-keys-keyboard.cpp
 *
 *  Created on: May 15, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxA(int N) {
        //There can be 0 or more Ctrl V at last. Try all possibility.

        vector<int> Screen(max(N + 1, 4),0);

        //Base cases
        Screen[0] = 0; Screen[1] = 1; Screen[2] = 2, Screen[3] = 3;

        for(int i = 4 ; i <= N ; ++i) {
            Screen[i] = Screen[i-1] + 1;    //Key 1: Add just one
            for(int j = 4; j <= i ; ++j) {  //At step j-1 we did last Ctrl C
                Screen[i] = max(Screen[i], ((i-j+1) + 1) * Screen[j-3]);	// (i-j+1) Ctrl Vs plus 1 already existing
            }
        }

        return Screen[N];
    }
};

int main() {
return 0


}

