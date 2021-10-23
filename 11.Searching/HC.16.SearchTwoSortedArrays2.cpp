/*
 * HC.16.SearchTwoSortedArrays1.cpp
 *
 * Problem: You are given two sorted arrays and a positive integer k. Design an algorithm for
 * 			computing kth smallest element in an array consisting elements of the two arrays.
 *
 * 			This is general version where k can be is larger than the size of individual arrays
 * 			but less than the total size.
 *
 *  Created on: Dec 15, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Now as k can be larger than size of individual arrays, the median finding algorithm will
//			not work.
//
//			One O(k) solution could be to keep on merging the arrays until we hit the kth element.
//			This uses the sortedness of the arrays while merging but checks all the elements.
//			As elements are sorted, we can potentially use binary search kind of algorithm to
//			skip checking all the elements.
//
//			To find kth element in A union B, we need to find x such that x elements in A and (k-x)
//			elements in B compose the first k elements in the combined array.
//
//			Now at the solution (A[x-1] <= B[k-x]) {xth element in A is not greater than (k-x+1)th
//			element in B} and (B[k-x-1] <= A[x]) must hold. This has to hold so that those k elements
//			compose the first k elements.
//
//			If (A[x-1] <= B[k-x]) is true but (B[k-x-1] <= A[x]) is false then that means x is small and
//			we need to increase x.
//			Similarly, if (A[x-1] <= B[k-x]) is false and (B[k-x-1] < A[x]) is true then that means
//			x is large and need to decrease x.
//			Both conditions cannot be false at the same time.
//
//			So this x can be found using some kind of hybrid binary search on A and B. We can maintain
//			a limit [lo, hi] for x and depending on the result of the comparisons we will reduce the
//			size of the range by half.

int findKth(vector<int>& A, vector<int>& B, int k) {
        if(A.empty()) { return B[k-1]; }
        if(B.empty()) { return A[k-1]; }

        //At solution x elements in A and (k - x) elements in B will constitute k smallest element

        //Try to find the x using binary search
        int lo = 0;
        int hi = min((int)A.size(), k); //one element beyond

        while(lo < hi) {
            int x = lo + (hi - lo) / 2;

            //Have appropriate default during checking. Think min amd max beyond two ends.
            int A_x_1 = (x > 0) ? A[x-1] : numeric_limits<int>::min();
            int A_x = (x < A.size()) ? A[x] : numeric_limits<int>::max();

            //B[k - x - 1] can be at either end
            int B_k_x_1 = numeric_limits<int>::min();
            if(k - x > 0 && k - x <= B.size()) {
                B_k_x_1 = B[k-x-1];
            } else if(k - x > B.size()) {
                B_k_x_1 = numeric_limits<int>::max();
            }

            int B_k_x = (k - x < B.size()) ? B[k-x] : numeric_limits<int>::max();

            if(A_x_1 <= B_k_x && B_k_x_1 <= A_x) {
                return max(A_x_1, B_k_x_1);
            } else if(A_x_1 <= B_k_x && B_k_x_1 >= A_x) {
                lo = x + 1;
            } else {
                hi = x - 1;
            }
        }

        //Haven't returned means loop broke with lo == hi. x == lo
        int A_x_1 = (lo > 0 && lo <= A.size()) ? A[lo - 1] : numeric_limits<int>::min();
        int B_k_x_1 = (k - lo > 0 && k - lo <= B.size()) ? B[k - lo - 1] : numeric_limits<int>::min();
        return max(A_x_1, B_k_x_1);
    }

int SearchInTwoSortedArrays(const vector<int>& A, const vector<int>& B, int k) {
	int lo = max(0, static_cast<int>(k - B.size()) - 1);	//lower bound
	int hi = min(k, static_cast<int>(A.size())) - 1;		//upper bound

	// Range of x is [lo, hi]. x is index in A. So there are x+1 elements.
	// So corresponding number of elements in B is (k-x-1) and its index is (k-x-2)

	while(lo < hi) {
		int x = lo + (hi-lo)/2;

		// Lets populate the four numbers we need to compare. For numbers beyond the array set default
		// value such that comparisons makes sense.
		int A_x_plus_1 = (x+1 >= (int)A.size()) ? numeric_limits<int>::max() : A[x+1];
		int A_x = (x<0) ? numeric_limits<int>::min() : A[x];
		int B_k_x_1 = (k-x-1 >= (int)B.size()) ? numeric_limits<int>::max() : B[k-x-1];
		int B_k_x_2 = (k-x-2 < 0) ? numeric_limits<int>::min() : B[k-x-2];

		if(A_x_plus_1 < B_k_x_2) {		// A[x] need to be greater than B[k-x-1]. So increase x. Increase lower bound.
			lo = x + 1;			// old value of x didn't work. So lo has to be at least x+1
		} else if(B_k_x_1 < A_x) {	// B[k-x] need to be greater than A[x-1]. So decrease x. Decrement upper bound.
			hi = x - 1;			// old value of x didn't work. So hi has to be at lease x-1.
		} else {				// Both conditions satisfied. That means we found x.
			//kth element will be max of A[x-1] and B[k-x-1]
			return max(A_x, B_k_x_2);
		}

	}

	//If haven't returned but broke the loop that means lo == hi
	int a = (lo < 0 || lo >= (int)A.size()) ? numeric_limits<int>::min() : A[lo];
	int b = (k-lo-2 < 0 || k-lo-2 >= (int)B.size()) ? numeric_limits<int>::min() : B[k-lo-2];
	return max(a, b);

}

int main() {
	vector<int> A = {1, 12, 15, 26, 38};
	vector<int> B = {2, 13, 17, 30, 45};

	cout << "1st: " << SearchInTwoSortedArrays(A, B, 1) << endl;
	cout << "2nd: " << SearchInTwoSortedArrays(A, B, 2) << endl;
	cout << "3rd: " << SearchInTwoSortedArrays(A, B, 3) << endl;
	cout << "4th: " << SearchInTwoSortedArrays(A, B, 4) << endl;
	cout << "5th: " << SearchInTwoSortedArrays(A, B, 5) << endl;

	A = {1, 12, 15};
	B = {2, 13, 17, 30};

	cout << "5th: " << SearchInTwoSortedArrays(A, B, 5) << endl;
	cout << "6th: " << SearchInTwoSortedArrays(A, B, 6) << endl;
	cout << "7th: " << SearchInTwoSortedArrays(A, B, 7) << endl;
}


