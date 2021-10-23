/*
 * HC.16.SearchTwoSortedArrays1.cpp
 *
 * Problem: You are given two sorted arrays and a positive integer k. Design an algorithm for
 * 			computing kth smallest element in an array consisting elements of the two arrays.
 *
 * 			This is simpler of the general version where you can assume that k is smaller
 * 			than the length of two arrays.
 *
 *  Created on: Dec 15, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			This is simpler as it can be mapped to a known problem of finding median of two
//			sorted arrays of same size. If we take the first k elements from both the arrays
//			then k th smallest element in the combined array is the median.
//
//			The way to find median among two sorted arrays is comparing their individual medians
//			and then discarding halves of both the arrays.
//			Discarding equal amount of elements from both sides of the median keeps the median intact.
//
//			This idea can be used to reject lower half of array whose median is smaller and
//			higher part of the array whose median is is larger. The reason is the lower half has
//			n elements greater than them (n/2 from own array and n/2 from other array) and higher
//			n elements smaller than them. So removing both will keep the median intact.
//
//			Note than if individual medians are equal then that is the overall median.
//
//			We can keep recursively doing that until there is only two elements in an array. Then
//			compute manually.
//
//			Note that total number of elements is even, in which case the median is the average of
//			the two middle most elements.

int Median(const vector<int>& A, int start, int end) {
	int diff = end-start;
	if(diff%2 == 0) { 			// odd: middle one
		return A[start + diff/2];
	} else { 					// even: average of mid twos
		//return (A[start + diff/2] + A[start + diff/2 + 1]) / 2;

		//** Logic changed to smallest element rather than average to support kth element
		return A[start + diff/2];
	}
}

// Assume: A and B
int MedianOfTwo(const vector<int>& A, const vector<int>& B, int a_s, int a_e, int b_s, int b_e) {
	if(a_s > a_e || b_s > b_e) {
		throw "Error: Bug!!";
	}
	if(a_e == a_s && b_s == b_e) {	// Single element
		//return (A[a_s] + B[b_s])/2;

		//** Logic changed to smallest element rather than average to support kth element
		return (A[a_s] < B[b_s]) ? A[a_s] : B[b_s];
	}
	if(a_e - a_s == 1 && b_e - b_s == 1) { // Two elements in both array
		//return (max(A[a_s], B[b_s]) + min(A[a_e], B[b_e]))/2;

		//** Logic changed to smallest element rather than average to support kth element
		return min(max(A[a_s], B[b_s]), min(A[a_e], B[b_e]));
	}

	int a_med = Median(A, a_s, a_e);
	int b_med = Median(B, b_s, b_e);

	if(a_med == b_med) {
		return a_med;
	} else if(a_med < b_med) {
		int diff = a_e - a_s;
		return MedianOfTwo(A, B, a_s + diff/2, a_e, b_s, b_e - diff/2);
	} else { // a_med > b_med
		int diff = a_e - a_s;
		return MedianOfTwo(A, B, a_s, a_e - diff/2, b_s + diff/2, b_e);
	}
}

// Assume k less than size of both the array
int SearchInTwoSortedArrays(const vector<int>& A, const vector<int>& B, int k) {
	if(k > (int)A.size() || k > (int)B.size()) {
		throw "Error: Need better algorithm!";
	}
	return MedianOfTwo(A, B, 0, k-1, 0, k-1);
}

int main() {

	cout << "Testing median: start" << endl;

	vector<int> A = {1, 2, 3, 6};
	vector<int> B = {4, 6, 8, 10};
	cout << MedianOfTwo(A, B, 0, A.size()-1, 0, B.size()-1) << endl;  // 5

	A = {1, 12, 15, 26, 38};
	B = {2, 13, 17, 30, 45};
	cout << MedianOfTwo(A, B, 0, A.size()-1, 0, B.size()-1) << endl;  // 16

	cout << "Testing median: end" << endl;

	cout << "Testing kth element: start" << endl;

	cout << "1st: " << SearchInTwoSortedArrays(A, B, 1) << endl;
	cout << "2nd: " << SearchInTwoSortedArrays(A, B, 2) << endl;
	cout << "3rd: " << SearchInTwoSortedArrays(A, B, 3) << endl;
	cout << "4th: " << SearchInTwoSortedArrays(A, B, 4) << endl;
	cout << "5th: " << SearchInTwoSortedArrays(A, B, 5) << endl;

	cout << "Testing kth element: end" << endl;
}


