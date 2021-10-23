/*
 * split-array-largest-sum.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;


class Solution {
    int helper(const vector<int>& nums, const vector<int>& max_from_start, vector<vector<int>>& table,
    			const vector<int>& sum_from_first, int upto, int parts) {
        if(upto <= 0) {
        	return nums[0];
        }
    	if(parts <= 1) {
            return sum_from_first[upto];
        }
        if(table[upto][parts] != -1) {
            return table[upto][parts];
        }
        if(upto+1 <= parts) {
            return max_from_start[upto];
        }

//        cout << "Finding for range [0, " << upto << "]" << endl;

        int min_sum = numeric_limits<int>::max();
        int running_sum = nums[upto];
        for(int j=upto-1 ; j >= 0 ; --j) {
        	int part1 = helper(nums, max_from_start, table, sum_from_first, j, parts-1);
        	int max_among = max(part1, running_sum);
//        	cout << "Int Max from [0, " << j << "] is = " << part1 <<", and sum for last part = " << running_sum << ", result max = " << max_among <<endl;
            min_sum = min(min_sum, max_among);

            running_sum += nums[j]; // for next loop
        }
        table[upto][parts] = min_sum;
//        cout << "Result for range [0, " << upto << " ] is = " << min_sum << endl;
        return min_sum;
    }

public:
    int splitArray(vector<int>& nums, int m) {
        vector<int> max_from_start(nums.size());
        max_from_start[0] = nums[0];
        for(int i=1 ; i< (int)nums.size() ; ++i) {
            max_from_start[i] = max(nums[i], max_from_start[i-1]);
        }

		vector<int> sum_from_first(nums.size(), nums[0]);
		for(int i=1; i< (int) nums.size() ; ++i) {
			sum_from_first[i] = sum_from_first[i-1] + nums[i];
		}

        vector<vector<int>> table(nums.size(), vector<int>(m+1, -1)); //table[i][j] stores max from nums[0..i] with j partitions

        int res = helper(nums, max_from_start, table, sum_from_first, nums.size()-1, m);
        return res;
    }
};



int main() {
	vector<int> A;
	Solution obj;

	A = {7,2,5,10,8};
	cout << obj.splitArray(A, 2) << endl;
}
