/*
 * 01.TowerOfHanoi.cpp
 *
 * Problem: A peg contains rings in sorted order with the largest ring at the bottom.
 * 			You are to transfer these rings to another peg using one intermediary.
 *
 * 			Write a program that prints the sequence of the transfer of the rings.
 * 			The only operation you can perform is taking a single ring from one peg and
 * 			place it on top of another peg. You must never place a larger ring above a smaller one.
 *
 *			After you solve the general problem, try solving variants when no ring is allowed to
 *			be moved from peg 1 to peg 2 directly.
 *
 *  Created on: Mar 31, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Insight to solving this can be gained by trying examples.
//			We can see that we are solving same problem multiple times with smaller problem size.
//			This will give us intuition of solving it using recursion.
//
//			For finding a recursion we will have to think as induction.
//			We will have to know how to solve directly for base cases.
//			Then we need to know to solve the problem for a size given the solution for
//			problems of smaller sizes.
//
//			Original problem:
//			If we solve the problem for moving top (n-1) rings to peg 3 using peg 2 as intermediary
//			and then move the nth ring to peg 2 and then solve for moving (n-1) rings from peg 3
//			to peg 2 using peg 1 as intermediary. Then that solves it.
//
//			Time complexity is T(n) = T(n-1) + 1 + T(n-1) = 1 + 2T(n-1) = 2^n
//			One way to see this is to unwrap the recurrence.
//
//			Variant problem:
//			In original problem, in order to do things fast we switch role of the pegs. But here
//			we need to make sure that roles are not messed up to make sure no ring goes from
//			peg 1 to peg 2.
//			Solve for top (n-1) rings from peg 1 to peg 2, that is the same recursive problem of
//			size one less. Then move nth ring from peg 1 to 3.
//			Then solve for (n-1) rings from peg 2 to peg 1. Then move nth ring from peg 3 to peg 2.
//			Then finally solve the problem (n-1) remaining rings.
//			Here notice that only role of from and to are interchanged. The role of intermediary
//			is never changed. And every time we move rings from and to through intermediary.
//			So no chance of moving peg 1 to peg 2.

const int numOfPegs = 3;

void ComputeTowerOfHanoiSteps(int num_rings_to_move, vector<stack<int>>& pegs,
								int from_peg, int to_peg, int use_peg, int* total_steps)
{
	if(num_rings_to_move > 0)
	{
		ComputeTowerOfHanoiSteps(num_rings_to_move-1, pegs, from_peg, use_peg, to_peg, total_steps);

		pegs[to_peg].push(pegs[from_peg].top());
		pegs[from_peg].pop();

		++*total_steps;
		cout << "Moved ring " << pegs[to_peg].top() << " from peg " << from_peg << " to peg " << to_peg << endl;

		ComputeTowerOfHanoiSteps(num_rings_to_move-1, pegs, use_peg, to_peg, from_peg, total_steps);
	}
}

void ComputeTowerOfHanoiStepsNo1To2(int num_rings_to_move, vector<stack<int>>& pegs,
								int from_peg, int to_peg, int use_peg, int *total_steps)
{
	if(num_rings_to_move > 0)
	{
		ComputeTowerOfHanoiStepsNo1To2(num_rings_to_move-1, pegs, from_peg, to_peg, use_peg, total_steps);

		pegs[use_peg].push(pegs[from_peg].top());
		pegs[from_peg].pop();

		++*total_steps;
		cout << "Moved ring " << pegs[use_peg].top() << " from peg " << from_peg << " to peg " << use_peg << endl;

		ComputeTowerOfHanoiStepsNo1To2(num_rings_to_move-1, pegs, to_peg, from_peg, use_peg, total_steps);

		pegs[to_peg].push(pegs[use_peg].top());
		pegs[use_peg].pop();

		++*total_steps;
		cout << "Moved ring " << pegs[to_peg].top() << " from peg " << use_peg << " to peg " << to_peg << endl;

		ComputeTowerOfHanoiStepsNo1To2(num_rings_to_move-1, pegs, from_peg, to_peg, use_peg, total_steps);
	}
}


int ComputeTowerOfHanoi(int num_of_rings)
{
	int total_steps=0;

	vector<stack<int>> pegs(numOfPegs);
	for(int i=num_of_rings ; i>=1 ; --i) {
		pegs[0].push(i);
	}

	//ComputeTowerOfHanoiSteps(num_of_rings, pegs, 0, 1, 2, &total_steps);

	// For variant output should not have string "peg 0 to peg 1"
	ComputeTowerOfHanoiStepsNo1To2(num_of_rings, pegs, 0, 1, 2, &total_steps);

	return total_steps;
}


int main()
{
	int total_steps = ComputeTowerOfHanoi(7);

	cout << endl << "Total steps: " << total_steps << endl;
}
