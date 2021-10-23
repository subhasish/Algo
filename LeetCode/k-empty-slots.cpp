/*
 * k-empty-slots.cpp
 *
 *  Created on: Feb 9, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

void pv (const vector<int>& A) {
	for(const int& a: A) {
		cout << a << ", " ;
	}
	cout << endl;
}

class Solution {
public:
    int kEmptySlots(vector<int>& flowers, int k) {

        vector<int> bloom; // sorted array of flowers bloomed
        bloom.emplace_back(flowers[0]);
        for(size_t i = 1 ; i < flowers.size() ; ++i) {

//        	pv(bloom);

            //insert at first
            if(flowers[i] < bloom[0]) {
                if(bloom[0] - flowers[i] == k+1) {
                    return i+1;
                } else {
                    bloom.insert(bloom.begin(), flowers[i]);
                }
                continue;
            }

            //insert at end
            if(flowers[i] > bloom[bloom.size()-1]) {
                if(flowers[i] - bloom[bloom.size()-1] == k+1) {
                    return i+1;
                } else {
                    bloom.emplace_back(flowers[i]);
                }
                continue;
            }

            // insert in the middle
            // Can do binary search to find largest smaller than flower[i]
            int lo = 0, hi = bloom.size()-1;
            while(lo < hi) {
                int mid = lo + (hi-lo+1)/2;
                if(bloom[mid] > flowers[i]) {
                    hi = mid - 1;
                } else {
                    lo = mid;
                }
            }

            //lo is the answer
            if(flowers[i] - bloom[lo] == k+1) {
                return i+1;
            }
            if(bloom[lo+1] - flowers[i]  == k+1) {
                return i+1;
            }
            bloom.insert(bloom.begin()+lo+1, flowers[i]);
        }

        return -1;
    }
};


int main() {
	Solution obj;

	vector<int> A = {1,2,3};

	cout << obj.kEmptySlots(A, 1) << endl;

	A = {6,5,8,9,7,1,10,2,3,4};
	cout << obj.kEmptySlots(A, 2) << endl;
}

