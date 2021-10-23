/*
 * odd-even-jump.cpp
 *
 *  Created on: Apr 4, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
        //We need to keep numbers from end in a sorted list and then
        //efficiently find the place to jump from each i.
        //This should be achievable by doing binary search.
        //
        //To do this efficiently we can keep them in a set or map and then
        //use binary search
        //
        //We also need to know the index of the element. So we can use map
        //instead of set and store index

        if(A.empty()) {
            return 0;
        }
        if(A.size() == 1) {
            return 1;
        }

        map<int,int> val_to_index;  //sorted plus value to index map
        val_to_index[A[A.size()-1]] = A.size()-1;

        vector<int> odd_jump(A.size(),-1);  //ith element stores where the odd jump from i will go
        vector<int> even_jump(A.size(),-1); //ith element stores where the even jump from i will go

        vector<bool> good_odd(A.size(),false);  //flag if ith position is good when odd jump is taken from here => end is reachable
        vector<bool> good_even(A.size(),false);  //flag if ith position is good when even jump is taken from here => end is reachable

        good_odd[A.size()-1] = true;
        good_even[A.size()-1] = true;
        int res = 1;

        for(int i = A.size() - 2 ; i >= 0 ; --i) {
            auto lo = val_to_index.lower_bound(A[i]);
            auto hi = val_to_index.upper_bound(A[i]);


            if(lo != val_to_index.end()) {
                if(lo->first > A[i]) {
                	if(lo == val_to_index.begin()) {
                		lo = val_to_index.end();
                	} else {
                		--lo;
                	}
                }
                else if(lo->first == A[i]) {
                	hi = lo;
                }
            } else {
                --lo;
            }

            //Debug: start
//            if(lo != val_to_index.end()) {
//            	cout << "For " << A[i] << ", next smaller element = " << lo->first << ", at index " << lo->second << endl;
//            } else {
//            	cout << "For " << A[i] << ", No next smaller element" << endl;
//            }
//            if(hi != val_to_index.end()) {
//            	cout << "For " << A[i] << ", next greater element = " << hi->first << ", at index " << hi->second << endl;
//            } else {
//            	cout << "For " << A[i] << ", No next greater element" << endl;
//            }


            if(lo != val_to_index.end()) {
                even_jump[i] = lo->second;
                if(good_odd[even_jump[i]]) {  //even jump from here we go to good cell with odd jump
                	good_even[i] = true;
                }
            }
            if(hi != val_to_index.end()) {
                odd_jump[i] = hi->second;
                if(good_even[odd_jump[i]]) {  //starting from here we jump to good cell with even jump
                    good_odd[i] = true;
                    ++res;
                }
            }

            val_to_index[A[i]] = i;
        }

        return res;
    }
};

int main() {
	Solution obj;
	vector<int> A;


	A = {2,3,1,1,4};
	cout << obj.oddEvenJumps(A) << ", expected = 3" << endl;

	A = {5,1,3,4,2};
	cout << obj.oddEvenJumps(A) << ", expected = 3" << endl;

	A = {10,13,12,14,15};
	cout << obj.oddEvenJumps(A) << ", expected = 2" << endl;

}

