/*
 * next-permutation.cpp
 *
 *  Created on: Jan 26, 2019
 *      Author: subha
 */
#include <bits/stdc++.h>
using namespace std;

void swap(int& a, int& b) {
	int t=a; a=b; b=t;
}

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i=nums.size()-1;
        while(i > 0 && nums[i-1] >= nums[i]) {
            --i;
        }
        sort(nums.begin()+i, nums.end());
        if(i == 0) {
            return;
        }

        //Doing linear search here, but binary search is also possible
        for(int j=i ; j < nums.size() ; ++j) {
            if(nums[j] <= nums[i-1]) {
                continue;
            } else {
                swap(nums[j], nums[i-1]);
                break;
            }
        }
        return;
    }
};



