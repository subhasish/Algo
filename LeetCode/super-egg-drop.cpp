/*
 * super-egg-drop.cpp
 *
 *  Created on: Jan 25, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;


class EggDrop {
    int eggDropRecr(int K, int N, vector<vector<int>>* arr_ptr) {
        vector<vector<int>>& arr = *arr_ptr;
        if(arr[N][K] != -1) {
            return arr[N][K];
        }
        if(K>N) {
            return eggDropRecr(N, N, arr_ptr);
        }

        //Linear Search: Too slow

//        int min_drop = numeric_limits<int>::max();
//        for(int x=1 ; x <= N ; ++x) {
//            min_drop = min(min_drop, max(eggDropRecr(K-1,x-1,arr_ptr),
//                                         eggDropRecr(K, N-x, arr_ptr)) + 1);
//        }
//        arr[N][K] = min_drop;
//        return min_drop;

        //Binary Search
        int lo = 1, hi = N;
        while(lo+1 < hi) {	//Will end with 2 adjacent numbers
        	int mid = lo + (hi - lo)/2;
        	int t1 = eggDropRecr(K-1, mid-1, arr_ptr);
        	int t2 = eggDropRecr(K, N-mid, arr_ptr);
        	if(t1 == t2) {
        		hi = lo = mid;
        		arr[N][K] = t1 + 1;
        		return arr[N][K];
        	} else if(t1 > t2) {
        		hi = mid;
        	} else {
        		lo = mid;
        	}
        }
        int t1 = max(eggDropRecr(K-1, lo-1, arr_ptr), eggDropRecr(K, N-lo, arr_ptr));
        int t2 = max(eggDropRecr(K-1, hi-1, arr_ptr), eggDropRecr(K, N-hi, arr_ptr));
        arr[N][K] = min(t1, t2) + 1;
        return arr[N][K];
    }
public:
    int superEggDrop(int K, int N) {
        vector<vector<int>> arr(N+1, vector<int>(K+1, -1));
        //K==0 no egg => not possible => infinite
        for(int i = 0 ; i <= N ; ++i) {
            arr[i][0] = numeric_limits<int>::max();
            arr[i][1] = i;
        }

        for(int j = 0 ; j <= K ; ++j) {
            arr[0][j] = 0;
            arr[1][j] = 1;
        }

        for(int i = 2 ; i <= N ; ++i) {
            for(int j = 2 ; j <= K ; ++j) {
                arr[i][j] = -1;
            }
        }

        return eggDropRecr(K, N, &arr);
    }
};

int main() {
	EggDrop obj;

	int ret = obj.superEggDrop(100, 10000);

	cout << ret << endl;
    return 0;
}

