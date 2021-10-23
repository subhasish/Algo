/*
 * 08.FindKthLargest.cpp
 *
 * Problem: Find kth largest element in an unsorted array.
 *
 *  Created on: Feb 10, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
#include <chrono>
#include <limits>
#include <random>

using namespace std;

// Solution: Variant of partitioning in quicksort.
//			 But here we need to look at one side only based on the final position of pivot element.
//           If pivot's position is greater than k then we will look in left otherwise will look in right.
//
// Time complexity: average case: T(n) = T(n/2) + O(n). Master theorem (a=1, b=2, c=1; c > (log b)/(log a)) => T(n) = O(n)
//					worst case: T(n) = O(n^2)  when each time random pivot is either largest or smallest element

typedef vector<int> VI;
void swap(int& a, int& b) {
	int t = a; a = b; b = t;
}

// Less than is defined by the compare object
// Returns the final index of the pivot element
template<typename Compare>
int Partiton(vector<int>& arr, int left, int right, int pivot_index, Compare comp)
{
	int pivot_val = arr[pivot_index];
	swap(arr[pivot_index], arr[right]);		// Move pivot to right, to each comparing with each other element in the range.
											// And swap to correct position later

	int new_pivot_index = left;				// All element left to this are greater than pivot. At end put pivot in this index.

	for(int i=left ; i<right ; i++) {
		if(comp(arr[i], pivot_val)) {
			swap(arr[i], arr[new_pivot_index++]);	// Put the larger element in left and increment final position of pivot
		}
	}

	swap(arr[right], arr[new_pivot_index]);
	return new_pivot_index;
}


template<typename Compare>
int FindKthLargest(int k, VI& arr, Compare comp)
{
	int left = 0, right = arr.size() - 1;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);

	while(left <= right) {		// Ensure less than equal case for single element

		uniform_int_distribution<int> iDistribution(left,right);
		int pivot_index = iDistribution(generator);

		//cout << "Left = " << left << ", Right = " << right << ", Pivot = " << arr[pivot_index] << ", was at index = " << pivot_index ;
		int new_pivot_index = Partiton(arr, left, right, pivot_index, comp);
		//cout << ", Now at = " << new_pivot_index << endl;

		if(new_pivot_index == k) {
			return arr[new_pivot_index];
		} else if(new_pivot_index < k) {
			left = new_pivot_index + 1;
		} else {   // new_pivot_index > k
			right = new_pivot_index - 1;
		}
	}

	//Dead code
	return 0;
}


int main()
{
	VI arr = {3, 2, 1, 5, 4};
	cout << "Largest element = " << FindKthLargest<greater<int>>(0, arr, greater<int>()) << endl;
	cout << "Smallest element = " << FindKthLargest<greater<int>>(arr.size() - 1, arr, greater<int>()) << endl;
	cout << "Median element = " << FindKthLargest<greater<int>>(arr.size() / 2, arr, greater<int>()) << endl;

}
