/*
 * HC.04.BiggestNMinusOneProduct.cpp
 *
 * Problem: Given an array of length n whose entries are integers, compute the largest product
 * 			that can be made by using (n-1) entries in A.
 * 			You cannot use one entry more than once. Array entries may be positive, negative,
 * 			or 0. You cannot use division operation implicitly or explicitly.
 *
 *  Created on: Oct 30, 2018
 *      Author: subha
 */


#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Can be solved by case analysis.
//			If there are more than one zeros, then result is 0.
//			Otherwise if odd number of negatives and a zero then result is 0.
//			Otherwise if all negative and even number of them then product of all but minimum
//			that is absolute value max.
//			Otherwise we try to avoid element with minimum absolute value.
//
//			Do few iterations one to collect all information about data, then figure which element
//			to skip and then one final iteration to compute the product.
//			Note that there can be multiple occurrences of element that we want to skip.
//
// Time complexity: O(n)
// Space complexity: O(n)

int BiggestNMinusOneProduct(const vector<int>& A)
{
	int count_neg=0,count_zero=0,count_pos=0,min_pos,max_neg,min_neg=0;
	min_pos = numeric_limits<int>::max();
	max_neg = numeric_limits<int>::min();
	int number_to_skip;
	bool has_already_skipped;

	if(A.size() < 2) {
		throw length_error("Input size must be more than 1.");
	}

	for(size_t i=0 ; i<A.size() ; ++i) {
		if(A[i] == 0) {
			++count_zero;
		} else if(A[i] < 0) {
			++count_neg;
			if(A[i] > max_neg) {
				max_neg = A[i];
			}
			if(A[i] < min_neg) {
				min_neg = A[i];
			}
		} else { // A[i] > 0
			++count_pos;
			if(A[i] < min_pos) {
				min_pos = A[i];
			}
		}
	}

	if(count_zero > 1) {
		return 0;
	} else if(count_zero == 1 && count_neg%2 == 1) {
		return 0;
	} else if(count_zero == 1) {
		number_to_skip = 0;
	} else { // No zero
		if(count_pos == 0) { // No positive
			if(count_neg%2 == 0) { // No zero, No positive, even negative => result must be negative
				number_to_skip = min_neg;
			} else {
				number_to_skip = max_neg;
			}
		} else { // Some positive
			if(count_neg%2 == 1) {
				number_to_skip = max_neg;
			} else {
				number_to_skip = min_pos;
			}
		}
	}

	int product = 1;
	// Now compute the product skipping the first occurrence of number_to_skip
	for(size_t i=0 ; i<A.size() ; ++i) {
		if(A[i] == number_to_skip && !has_already_skipped) {
			has_already_skipped = true;
			continue;
		} else {
			product *= A[i];
		}
	}
	return product;
}


// Solution:
//			Another solution without case analysis is to compute all suffix products and
//			prefix product and finally compute Prefix[0,i-1] * Suffix[i+1,n-1] for all i
//			and note the maximum.
//
// Time complexity: O(n)
// Space complexity: O(n)
//
//			Some space can be improved by not saving one product in array and use running
//			product.

int BiggestNMinusOneProduct1(const vector<int>& A)
{
	if(A.size() < 2) {
		throw length_error("Array should have minimum two element.");
	}

	vector<int> suffix_prouct(A.size());
	int running_product = 1;

	for(int i = A.size()-1 ; i>=0 ; --i) {
		running_product *= A[i];
		suffix_prouct[i] = running_product;
	}

	running_product = 1;
	int max_prouct = numeric_limits<int>::min();
	for(int i=0 ; i<(int)A.size() ; ++i) {
		int product_without_current = running_product * ((i+1 < (int)A.size()) ? suffix_prouct[i+1] : 1);
		if(max_prouct < product_without_current) {
			max_prouct = product_without_current;
		}
		running_product *= A[i];
	}

	return max_prouct;
}


int main()
{
	vector<int> A = {2, 3, 4, 5};
	cout << BiggestNMinusOneProduct(A) << ", " << BiggestNMinusOneProduct1(A) << endl;

	A = {2, 3, 4, 0};
	cout << BiggestNMinusOneProduct(A) << ", " << BiggestNMinusOneProduct1(A) << endl;

	A = { 2, 3, 0, 0};
	cout << BiggestNMinusOneProduct(A) << ", " << BiggestNMinusOneProduct1(A) << endl;

	A = {2, 3, -4, 0};
	cout << BiggestNMinusOneProduct(A) << ", " << BiggestNMinusOneProduct1(A) << endl;

	A = {2, -3, -4, 0};
	cout << BiggestNMinusOneProduct(A) << ", " << BiggestNMinusOneProduct1(A) << endl;

	A = {2, -3, -4, 0, 0};
	cout << BiggestNMinusOneProduct(A) << ", " << BiggestNMinusOneProduct1(A) << endl;

	A = {-2, -3, -4, -5};
	cout << BiggestNMinusOneProduct(A) << ", " << BiggestNMinusOneProduct1(A) << endl;

	A = {-2, -3, -4, -5, -6};
	cout << BiggestNMinusOneProduct(A) << ", " << BiggestNMinusOneProduct1(A) << endl;

	A = {0};
	cout << BiggestNMinusOneProduct(A) << ", " << BiggestNMinusOneProduct1(A) << endl;
}
