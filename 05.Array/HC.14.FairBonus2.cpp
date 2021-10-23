/*
 * HC.14.FairBonus.cpp
 *
 * Problem: An array is given with the number of line of codes written by developers sitting side
 * 			by side. We are to assign bonus concert tickets to them such that among neighbors
 * 			one who wrote more line of code will get more concert ticket than that neighbor.
 *
 * 			Find the minimum number of concert tickets needed to be distributed.
 *
 *			Example: Input: <300,400,500,200>, Output: 7 = <1,2,3,1>
 *
 *  Created on: Nov 11, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			One key observation is that the least productive developer will never need more than
//			one ticket. We can propagate the idea by processing the developers in the increasing
//			order of productivity.
//
//			Fill tickets from lowest rating to highest. So when we get an entry all the smallest entry
//			have their final number of tickets. So when considering neighbors we can ignore the neighbors
//			with higher productivity. If current productivity is higher than neighbors then we know that
// 			those neighbors already have their final number of tickets.
//
//			Also we need to handle equal cases. Otherwise result with two equal neighbors may have
//			different tickets. So this does not look as good solution w.r.t. The worst case then many
//			elements are equal. Worst case O(n^2) as it tries to update all equal neighbors.
//			Can improve by stopping updating equal if already equal. Also can consider equal elements
//			from one side so that number of updates are maximum twice.
//
// Time complexity: worst case id O(n^2) but average case should be O(n log n)

struct EmployeeData {
	int productivity;
	size_t index;
};

typedef vector<int> VI;

VI ComputeFairBonus(const VI& productivity) {
	priority_queue<EmployeeData, vector<EmployeeData>, function<bool(EmployeeData&,EmployeeData&)>>
			min_heap([] (const EmployeeData& lhs, EmployeeData& rhs) {
				return lhs.productivity > rhs.productivity;
			});

	for(size_t i=0 ; i<productivity.size() ; ++i) {
		min_heap.emplace(EmployeeData{productivity[i], i});
	}

	//Initially assign one tickets to everyone
	VI tickets(productivity.size(), 1);

	// Fill tickets from lowest rating to highest. So when we get an entry all the smallest entry
	// have their final number of tickets. So when considering neighbors we can ignore the neighbors
	// with higher productivity. If current productivity is higher than neighbors then we know that
	// those neighbors already have their final number of tickets.
	while(!min_heap.empty()) {
		EmployeeData top = min_heap.top();

		// If left neighbor is smaller than current one
		if(top.index > 0 && productivity[top.index-1] < top.productivity && tickets[top.index-1] >= tickets[top.index]) {
			tickets[top.index] = tickets[top.index-1]+1;
		}

		// If mismatch with right neighbor
		if(top.index < (productivity.size()-1) && productivity[top.index+1] < top.productivity && tickets[top.index+1] >= tickets[top.index]) {
			tickets[top.index] = tickets[top.index+1]+1;
		}

		//Now handle equal cases. Otherwise result with two equal neighbors will have different tickets
		for(size_t j=top.index+1 ; j<productivity.size() && productivity[j] == productivity[top.index] ; ++j) {
			tickets[j] = tickets[top.index];
		}
		for(size_t j=top.index-1 ; j >= 0 && productivity[j] == productivity[top.index] ; --j) {
			tickets[j] = tickets[top.index];
		}

		min_heap.pop();
	}
	return tickets;
}

void PrintVector(VI& list) {
	for(int i: list) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	VI productivity = {100,300,500,400,600,900,700,700,200,100,1000,1000,800,800,600};
	VI bonuses = ComputeFairBonus(productivity);
	PrintVector(bonuses);
	// Output will be: 1,2,3,1,2,4,3,3,2,1,3,3,2,2,1
}
