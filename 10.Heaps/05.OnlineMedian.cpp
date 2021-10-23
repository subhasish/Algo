/*
 * 05.OnlineMedian.cpp
 *
 * Problem: Compute median of online data. You need to output median after reading each input.
 *
 *  Created on: Feb 1, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: As we need to output median each time and we do not know end of input, we need to store all data to compute median accurately.
//           Sorting each time like insertion sort will cause O(n^2) time
//           Also if we use partition approach to find n/2th element each time then, each iteration will take O(n) time and in total O(n^2)
//
//           Note that median divides array in two halves and when a new element is added only one half can increase by 1.
//           Also the element to be moved is largest among the smaller half or smallest among the larger half.
//           So, we can use two heaps, a max-heap for smaller half and min-heap for the larger half.

void OnlineMedian(istringstream* iss) {
	priority_queue<int, vector<int>, less<int>> max_heap;
	priority_queue<int, vector<int>, greater<int>> min_heap;

	int x;
	while(*iss >> x) {
		size_t min_sz = min_heap.size();
		size_t max_sz = max_heap.size();

		// Insert to make only lower half at most 1 larger than size of larger half. So max_heap can only be larger
		if(min_sz == max_sz) {

			// Cannot directly push to max_heap. As the item may actually belong to min_heap.
			// So first push in min_heap and then take minimum of them and then put it in max heap

			min_heap.push(x);
			max_heap.push(min_heap.top());
			min_heap.pop();

		} else if(min_sz < max_sz) { // Size has to be cached before the if statement, otherwise condition may not evaluate correctly

			// Now push in max_heap so they become equal size again
			// Similar as above push in max_heap first and then take max of it and put in min_heap

			max_heap.push(x);
			min_heap.push(max_heap.top());
			max_heap.pop();

		} else {
			// min_heap.size() > max_heap.size() not possible
		}

		// Now take median.
		cout << "Median: " << ((min_heap.size() == max_heap.size()) ? (0.5 * (min_heap.top() + max_heap.top())) : max_heap.top()) << endl;
	}
}


int main()
{
	istringstream iss("1 0 3 5 2 0 1");
	OnlineMedian(&iss);
}
