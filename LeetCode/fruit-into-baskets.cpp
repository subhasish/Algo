/*
 * fruit-into-baskets.cpp
 *
 *  Created on: Feb 2, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& tree) {
        unordered_map<int,int> basket; //type to count mapping for current stretch
        int start=0, end=0, max_count=0;
        while(end != (int)tree.size()) {
            if(basket.find(tree[end]) != basket.end()) {
                ++basket[tree[end]];
                ++end;
            } else {
                if(basket.size() < 2) {
                    basket.emplace(tree[end], 1);
                    ++end;
                } else {
                    while(basket.size() >= 2) {
                        --basket[tree[start]];
                        if(basket[tree[start]] == 0) {
                            basket.erase(tree[start]);
                        }
                        ++start;
                    }
                }
            }

            //start to end-1 is the range
            if(max_count < end-start) {
                max_count = end-start;
            }
        }
        return max_count;
    }
};


int main() {
	Solution obj;

	vector<int> A = {1,2,1};
	cout << obj.totalFruit(A) << endl;

	A = {0,1,2,2};
	cout << obj.totalFruit(A) << endl;

	A = {1,2,3,2,2,1,0};
	cout << obj.totalFruit(A) << endl;

	A = {3,3,3,1,2,1,1,2,3,3,4};
	cout << obj.totalFruit(A) << endl;
}

