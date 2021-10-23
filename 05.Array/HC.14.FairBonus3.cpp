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
//			The approach to do total order seems wasteful when the specific constraint is very local.
//
//			One simple but tricky approach solves the problem in linear time. The key observation is
//			that the constraints for left to right and right to left can be satisfied independently.
//
//			So we start by giving each developer one ticket. Then we make a left to right pass in which
//			we give developers one more ticket if they are more productive than previous one, or equal
//			ticket if they are equally productive. Similarly we will do one right to left pass.
//
// Time complexity: worst case id O(n)


typedef vector<int> VI;

VI ComputeFairBonus(const VI& productivity) {
	//Initially assign one tickets to everyone
	VI tickets(productivity.size(), 1);

	//Left to right pass
	for(size_t i=1 ; i<productivity.size() ; ++i) {
		if(productivity[i] > productivity[i-1] && tickets[i]<=tickets[i-1]) {
			tickets[i] = tickets[i-1]+1;
		}
		else if(productivity[i] == productivity[i-1]) {
			tickets[i] = tickets[i-1];
		}
	}

	//Right to left pass
	for(int i=(int)(productivity.size()-2) ; i>=0 ; --i) {
		if(productivity[i] > productivity[i+1] && tickets[i]<=tickets[i+1]) {
			tickets[i] = tickets[i+1]+1;
		}
		else if(productivity[i] == productivity[i+1]) {
			tickets[i] = tickets[i+1];
		}
	}

	return tickets;
}

void PrintVector(VI& list) {
	for(int i: list) {
		cout << i << ",";
	}
	cout << endl;
}

int main() {
	VI productivity = {100,300,500,400,600,900,700,700,200,100,1000,1000,800,800,600};
	VI bonuses = ComputeFairBonus(productivity);
	PrintVector(bonuses);
	// Output will be: 1,2,3,1,2,4,3,3,2,1,3,3,2,2,1
}
