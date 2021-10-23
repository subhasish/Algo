/*
 * SparseTable.cpp
 *
 *	Here are trying to use Sparse table do range minimum query.
 *
 *  Created on: Feb 20, 2021
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4;
const int K = 25;

//st[i][j] will store the answer for the range [i,i+2^j−1] of length 2^j
int st[MAXN][K+1];

void PrecomputeMin(vector<int>& arr) {
	for(size_t i = 0; i < arr.size() ; ++i) {
		st[i][0] = arr[i];
	}

	int k = floor(log2(arr.size())) + 1;
	for(int j = 1 ; j <= k ; ++j) {
		for(int i = 0 ; (i + (1 << j)) <= (int)arr.size() ; ++i) {
			st[i][j] = min(st[i][j-1], st[i + (1 << (j-1))][j-1]);
		}
	}
}


int GetMin(int L, int R) {
	int j = floor(log2(R-L+1));
	return min(st[L][j], st[R - (1 << j) + 1][j]);
}

int sumPreComp[MAXN][K+1];
void PrecomputeSum(vector<int>& arr) {
	for(size_t i = 0; i < arr.size() ; ++i) {
		sumPreComp[i][0] = arr[i];
	}

	int k = floor(log2(arr.size())) + 1;
	for(int j = 1 ; j <= k ; ++j) {
		for(int i = 0 ; (i + (1 << j)) < (int)arr.size() ; ++i) {
			sumPreComp[i][j] = sumPreComp[i][j-1] + sumPreComp[i + (1 << (j-1))][j-1];
		}
	}
}

long long GetSum(int L, int R) {
	long long sum = 0;
	for( int j = K ; j >= 0 ; --j) {
		if((1 << j) <= (R - L + 1)) {
			sum += sumPreComp[L][j];
			L += (1 << j);
		}
	}
	return sum;
}


int main() {
	vector<int> arr = {5, 6, 8, 23, 45, 4, 7, 232, 345, -34, 46, -2, 35, 6, 4, 3345, 4, 33};

	PrecomputeSum(arr);
	cout << GetSum(3, 8) << endl;

//	PrecomputeMin(arr);
//	cout << GetMin(3,8) << endl;
//	cout << GetMin(3,9) << endl;

	vector<int> nums = {1,4,3,7,4,5};
	PrecomputeMin(nums);
	cout << GetMin(0,5) << endl;

//	int k = 3;
//
//	cout << "start" << endl;
//	        long long res = nums[k];
//
//	        for(int i = 0 ; i <= k ; ++i) {
//	            for(int j = k ; j < nums.size() ; ++j) {
//
//	                int mn = GetMin(i,j);
//	                long long c = (mn) * (j - i + 1);
//	                res = max(res, c);
//
//	                cout << i << "," << j << " - " << mn << ", " << c << " = " << res << endl;
//	            }
//	        }
//	        return res;
}


