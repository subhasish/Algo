/*
 * minimum-incompatibility.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: subha
 */


#include <bits/stdc++.h>
using namespace std;

class Solution {

public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        int sz = nums.size();
        if(k == sz) {return 0;}

        int maxMask = (1 << sz) - 1;
        int n = sz / k;

        vector<int> tab(maxMask + 1, -1);

        //Compute all valid sets of size n
        for(int i = 1 ; i <= maxMask ; ++i) {
            int ones = __builtin_popcount(i);
            if(ones != n) { continue; }

            int mn = numeric_limits<int>::max();
            int mx = numeric_limits<int>::min();

            unordered_set<int> dup_check;

            for(int j = 0 ; j < sz ; ++j) {
                int m = (1 << j);
                if((i & m) == 0) { continue; }

                if(!dup_check.empty() && dup_check.find(nums[j]) != dup_check.end()) {
                    break;
                }

                dup_check.emplace(nums[j]);
                mn = min(mn, nums[j]);
                mx = max(mx, nums[j]);
            }

            if((int)dup_check.size() == n) {
                tab[i] = (mx - mn);
            }
        }


        //Go over all bit masks
        for(int m = 1 ; m <= maxMask ; ++m) {
            int ones = __builtin_popcount(m);
            if(ones % n != 0) { continue; }

            //Compute all sub-bitmasks of a bit mask: https://cp-algorithms.com/algebra/all-submasks.html
            for(int s=m ; s ; s = (s-1)&m) {
                int sones = __builtin_popcount(m);
                if(sones % n != 0 ) {continue;}

                int as = m - s;
                if(tab[s] != -1 && tab[as] != -1) {
                    int nv = tab[s] + tab[as];
                    tab[m] = (tab[m] == -1) ? nv : min(nv, tab[m]);
                }
            }
        }

        return tab[maxMask];

    }

};

int main() {
	Solution obj;
	vector<int> nums;

	nums = {12,8,6,6,12,1,7,9,8,9,1,9};
	cout << "Expected: 22, Actual: " << obj.minimumIncompatibility(nums, 4) << endl;

}


