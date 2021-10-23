/*
 * burst-balloons.cpp
 *
 *  Created on: Feb 1, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    int Helper(int left, int right, const vector<int>& nums, vector<vector<int>>* table_ptr) {
        vector<vector<int>>& table = *table_ptr;
        if(left+1>=right) {
            return 0;
        }
        if(table[left][right] >= 0) {
            return table[left][right];
        }

        int result = 0;
        for(int i=left+1; i<right ; ++i) {
            result = max(result,
                            nums[left] * nums[i] * nums[right] +
                            Helper(left, i, nums, table_ptr) +
                            Helper(i, right, nums, table_ptr));
        }
        table[left][right] = result;
        return result;
    }
public:
    int maxCoins(vector<int>& nums) {
        vector<int> A(nums.size()+2,1);
        for(size_t i=0 ; i<nums.size() ; ++i) {
            A[i+1] = nums[i];
        }

        vector<vector<int>> dp_table(A.size(), vector<int>(A.size(), -1));
        return Helper(0,A.size()-1, A, &dp_table);
    }
};

int main() {
	Solution obj;

	vector<int> nums = {3, 1, 5, 8};
	cout << obj.maxCoins(nums) << endl;
}

