/*
 * HC.17.FindKthLargestUnknownLength.cpp
 *
 * Problem: Find kth largest element in a sequence of elements that is presented one element at a time.
 * 			Length of the sequence in not known in advance, and could be very large.
 *
 *  Created on: Dec 17, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			The natural approach is to use a mean heap containing the k largest elements seen thus far,
//			same as done in Heaps/00.OnlineTopK.cpp
//			But that has a time complexity of O(n log k)
//
//			We have seen another way of finding kth largest element by doing partitioning similar to
//			quick sort that takes average case O(n) time. But it can be performed on array of known
//			length.
//			We cannot apply that algorithm directly here without allocating O(n) space. However,
//			we can break our input into fixed size arrays and run that algorithm on those arrays.
//
//			We can store 2k elements, then apply the algorithm and keep the first k elements. Do it
//			over and over again until input finishes.
//
// Time complexity:
//			Finding kth largest in 2k sized array is O(k). It runs every k elements, implying O(n)
//			overall time complexity.

template<typename Compare>
int FindKthLargest(int k, vector<int>& arr, Compare comp);


int FindKthLargestUnknownLength(istringstream* stream, int k) {
	vector<int> candidate;
	int x;

	while(*stream >> x) {
		candidate.emplace_back(x);
		if((int)candidate.size() == 2*k) {
			//Apply the algorithm to reorder elements about kth largest element
			FindKthLargest<less<int>>(k-1, candidate, less<int>());

			//discard the elements beyond size k
			candidate.resize(k);
		}
	}

	if((int)candidate.size() < k) {
		 std::ostringstream stringStream;
		  stringStream << "k " << k << " larger than input size: " << candidate.size();
		  std::string copyOfStr = stringStream.str();
		throw invalid_argument(copyOfStr);
	}

	FindKthLargest<less<int>>(k-1, candidate, less<int>());
	return candidate[k-1];
}


typedef vector<int> VI;
void swap(int& a, int& b) {
	int t = a; a = b; b = t;
}

// Less than is defined by the compare object
// Returns the final index of the pivot element
template<typename Compare>
int Partiton(VI& arr, int left, int right, int pivot_index, Compare comp)
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

int main() {
	string ss = "1 0 3 5 2 0 1";


	int x;
	try {
		istringstream iss1(ss);
		x = FindKthLargestUnknownLength(&iss1, 4);
		cout << "4th largest: " << x << endl;

		istringstream iss2(ss);
		x = FindKthLargestUnknownLength(&iss2, 6);
		cout << "6th largest: " << x << endl;

		istringstream iss3(ss);
		x = FindKthLargestUnknownLength(&iss3, 8);
		cout << "8th largest: " << x << endl;

	} catch (const exception& e) {
		cout << e.what() << endl;
	}
}
