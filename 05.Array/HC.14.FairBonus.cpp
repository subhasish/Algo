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
//			One thing to note that exact numbers does not matter as long as the relative order
//			between neighbors are maintained.
//			Careful observation between few examples will show that the input can be broken into
//			set of contiguous hills, where foots of the hills will get one concert ticket and
//			as we go up the hill number of ticket increases. The two sides may not have same
//			number of elements but top will contain maximum.
//
//			One thing is to consider that for equal neighbors we want to give same number of
//			tickets. That is not possible to count if we only store the number of elements
//			on each side; we do not know how many were equal and where. We need to store the
//			indices where the hills starts and ends and re-process them to compute final
//			number of tickets.
//
//			Also there can be multiple tops

struct Hill {
	int start=-1,end=-1;
	int top=-1;
};

typedef vector<int> VI;

VI ComputeFairBonus(const VI& productivity) {
	vector<Hill> hills;

	Hill curr;

	// 1st hill initialization
	curr.start = 0;
	bool is_uphill = true;
	int prev = -1;
	for(size_t i=0 ; i<productivity.size() ; ++i) {
		if(productivity[i] > prev) {
			if(is_uphill) {
				// nothing to do; keep continuing
			} else {
				curr.end = i-1;
				hills.emplace_back(curr);

				//new hill
				curr.start = i-1;
				is_uphill = true;
			}
		} else if(productivity[i] < prev) {
			if(is_uphill) {
				curr.top = i-1;
				is_uphill = false;
			} else {
				//nothing to do; keep continuing
			}
		} else { // equal
			// nothing to do; keep continuing
		}

		prev = productivity[i];

		if(i == productivity.size()-1) { //last hill
			curr.end = i;
			if(is_uphill) {
				curr.top = i;
			}
			hills.emplace_back(curr);
		}
	}

	for(size_t i=0 ; i<hills.size() ; ++i) {
		cout << "Hill " << i << ": start = " << hills[i].start << ", top = " << hills[i].top << ", end = " << hills[i].end << endl;
	}

	VI bonuses(productivity.size(),1); // Initialize with 1
	for(size_t i=0 ; i<hills.size() ; ++i) {
		// compute uphill
		for(int j=hills[i].start+1 ; j<hills[i].top ; ++j) {
			if(productivity[j] > productivity[j-1]) {
				bonuses[j] = bonuses[j-1]+1;
			} else if(productivity[j] == productivity[j-1]) {
				bonuses[j] = bonuses[j-1];
			}
		}

		//compute down-hill
		for(int j=hills[i].end-1 ; j > hills[i].top ; --j ) {
			if(productivity[j] > productivity[j+1]) {
				bonuses[j] = bonuses[j+1] + 1;
			} else if (productivity[j] == productivity[j+1]) {
				bonuses[j] = bonuses[j+1];
			}
		}

		//compute top
		if(hills[i].top > hills[i].start) {
			if(productivity[hills[i].top] > productivity[hills[i].top-1] && bonuses[hills[i].top] <= bonuses[hills[i].top-1]) {
				bonuses[hills[i].top] = bonuses[hills[i].top-1]+1;
			}
			//multiple top
			for(size_t j=1 ; hills[i].top+j < productivity.size() && productivity[hills[i].top] == productivity[hills[i].top+j] ; ++j) {
				bonuses[hills[i].top+j] = bonuses[hills[i].top];
			}
		}
		if(hills[i].top < hills[i].end) {
			if(productivity[hills[i].top] > productivity[hills[i].top+1] && bonuses[hills[i].top] <= bonuses[hills[i].top+1]) {
				bonuses[hills[i].top] = bonuses[hills[i].top+1]+1;
			}
			//multiple top
			for(int j=1 ; hills[i].top-j >=0 && productivity[hills[i].top] == productivity[hills[i].top-j] ; --j) {
				bonuses[hills[i].top-j] = bonuses[hills[i].top];
			}
		}
	}
	return bonuses;
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
