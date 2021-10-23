/*
 * predict-the-winner.cpp
 *
 *  Created on: Jan 26, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        // F(lo,hi) = Sum_lo_hi - min(F(lo+1,hi), F(lo, hi-1))
        // S(lo,sz) = Sum_lo_sz - min(S(lo+1,sz-1), S(lo, sz-1))
        // For sum between each index in O(n) we need a prefix sum

        vector<int> prefix_sum(nums.size(),0);
        prefix_sum[0] = nums[0];
        for(size_t i = 1 ; i < nums.size() ; ++i) {
            prefix_sum[i] = nums[i] + prefix_sum[i-1];
        }

        // table[i][j] = sum obtained by first player when numbers start at i and
        //               end at i+j
        vector<vector<int>> table(nums.size(), vector<int>(nums.size()+1, 0));
        for(size_t i = 0 ; i < nums.size() ; ++i) {
            table[i][0] = 0;
            table[i][1] = nums[i];
        }

        for(size_t sz = 2 ; sz <= nums.size() ; ++sz) {
            for(size_t i = 0 ; i+sz-1 < nums.size() ; ++i) {
                int j = i + sz - 1;
                int sum = prefix_sum[j] - ((i>0) ? prefix_sum[i-1] : 0);
                table[i][sz] = sum - min(table[i][sz-1], table[i+1][sz-1]);
            }
        }
        int first_player = table[0][nums.size()];
        int second_player = prefix_sum[nums.size() - 1] - first_player;
        return first_player >= second_player;
    }
};

int main() {
	Solution obj;
	vector<int> A = {1,5,2};
	cout << obj.PredictTheWinner(A) << endl;
}

