/*
 * capacity-to-ship-packages-within-d-days.cpp
 *
 *  Created on: May 1, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;
    }
};

class Solution {
    unordered_map<pair<int,int>, int, pair_hash> table;

    int helperDP(const vector<int>& w, int n, int d) {
        // Base cases
        if(n <= 0) {    //one item
            return w[0];
        }
        if(d <= 1) { 	//one day
        	int sum_item = w[0];
        	for(int i=1 ; i<=n ; ++i) {
        		sum_item += w[i];
        	}
        	return sum_item;
        }
        if(n <= d-1) {    //Each one day
            int max_item = w[0];
            for(int i=0 ; i <= n ; ++i) {
                max_item = max(max_item, w[i]);
            }
            return max_item;
        }

        //Recursive case
        pair<int,int> p = make_pair(n, d);
        if(table.find(p) != table.end()) {
            return table[p];
        } else {
            int running_sum = w[n];
            int current_sol = numeric_limits<int>::max();
            for(int j = n-1 ; j >= 0 ; --j) {
            	int sub_sol = helperDP(w, j, d-1);
                current_sol = min(current_sol, max(running_sum, sub_sol));
                running_sum += w[j];
            }

            table[p] = current_sol;
            return table[p];
        }
    }
public:
    int shipWithinDays(vector<int>& weights, int D) {
        return helperDP(weights, weights.size()-1, D);
    }
};


int main() {
	Solution obj;
	vector<int> items = {1,2,3,4,5,6,7,8,9,10};
	int days = 5;
	cout << obj.shipWithinDays(items, days) << endl;
}
