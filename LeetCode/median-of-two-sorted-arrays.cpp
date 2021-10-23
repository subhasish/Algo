/*
 * median-of-two-sorted-arrays.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    double median(const vector<int>& A, int s, int e) {
        if(s == e) {
            return A[s];
        }
        int mid = s + (e-s)/2 ;
        if((e-s+1)%2 == 1) {
            return A[mid];
        } else {
            return (A[mid] + A[mid+1]) / 2.0;
        }
    }

    double findMedianInConstTime(const vector<int>& A, const vector<int>& B, int s1, int e1, int s2, int e2) {
        if(e1-s1 > 3 || e2-s2 > 3) {
            throw length_error("Arrays larger for constant time coputation.");
        }
        vector<int> merged(e1-s1+1 + e2-s2+1);
        int k = 0;
        while(s1 <= e1 && s2 <= e2) {
            if(A[s1] <= B[s2]) {
                merged[k++] = A[s1++];
            } else {
                merged[k++] = B[s2++];
            }
        }

        while(s1 <= e1) {
            merged[k++] = A[s1++];
        }
        while(s2 <= e2) {
            merged[k++] = B[s2++];
        }

        return median(merged, 0, merged.size()-1);
    }

    double helper(const vector<int>& A, const vector<int>& B, int s1, int e1, int s2, int e2) {
        if(e1-s1 <= 1 || e2-s2 <=1) { //If necessary trim and do constant time computation
            if(e1-s1 <= 1 && e2-s2 > 3) {
                int mid = s2 + (e2-s2)/2 ;
                if((e2-s2)%2 == 0) {  //odd length
                    s2 = mid - 1;
                    e2 = mid + 1;
                } else {
                    s2 = mid - 1;
                    e2 = mid + 2;
                }
            } else if(e1-s1 > 3 && e2-s2 <= 1) {
                int mid = s1 + (e1-s1)/2;
                if((e1-s1)%2 == 0) {  //odd length
                    s1 = mid - 1;
                    e1 = mid + 1;
                } else {
                    s1 = mid - 1;
                    e1 = mid + 2;
                }
            }
            return findMedianInConstTime(A, B, s1, e1, s2, e2);
        }

        int len1 = e1-s1+1;
        int len2 = e2-s2+1;
        int cutlen = 1;
        if(len1 < len2) {
            cutlen = (len1-1)/2;
        } else {
            cutlen = (len2-1)/2;

        }

        double med1 = median(A, s1, e1);
        double med2 = median(B, s2, e2);
        if(med1 < med2) {
            s1 += cutlen;
            e2 -= cutlen;
        } else {
            e1 -= cutlen;
            s2 += cutlen;
        }
        return helper(A, B, s1, e1, s2, e2);
    }

public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    	if(nums1.empty()) {
    		return median(nums2, 0, nums2.size()-1);
    	} else if (nums2.empty()) {
    		return median(nums1, 0, nums1.size()-1);
    	}

        return helper(nums1, nums2, 0, nums1.size()-1, 0, nums2.size()-1);
    }
};

int main() {
	vector <int> A, B;
	Solution obj;

//	A = {1, 12, 15, 26, 38};
//	B = {2, 13, 17, 30, 45};
//	cout << obj.findMedianSortedArrays(A,B) << endl;
//
//	A = {};
//	B = {2, 13, 17, 30, 45};
//	cout << obj.findMedianSortedArrays(A,B) << endl;

	A = {1};
	B = {2, 13, 17, 30, 45};
	cout << obj.findMedianSortedArrays(A,B) << endl;
}


