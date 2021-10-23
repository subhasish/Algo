/*
 * HC.32.JosephusProblem.cpp
 *
 * Problem: Men numbered from 1 to n are arranged in a circle in clockwise order. Every kth man is
 * 			removed, until only one man remains. What is the number of the last man?
 *
 * Note:	*****Very tricky
 *
 *  Created on: Jan 9, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			One way is to simulate the game. But how to answer without simulating?
//			Seems daunting at first sight. So lets play with examples and try to make some observations.
//
//			The simple case when k=2 constant that is comprehensible using examples. But the
//			general case is not comprehensible using examples. But still might trigger some thoughts.
//
//			Observation 1:  Lets say we start with n men. When one person is removed the game is
//							equivalent to playing with (n-1) men. Only thing is that some numbering
//							needs to change between game for n and (n-1).
//			Observation 2:  When only one person remains, i.e., n=1 result is 1.
//
//			From these two observations it seems that recursion can be used to solve the problem. But
//			we need to find a mapping between the winner of the (n-1) and n games.
//
//			The recursion will give the result of the winner in the indexing of (n-1) game. And there
//			is k. We need to use these two to come up with the index of the winner in the n game.
//
//			Suppose the winner of the (n-1) game is x. The index is computed from 1 for the game of (n-1).
//			But for game of n the index 1 of game (n-1) is placed at (k+1). This is because after killing
//			kth person the count for second round started with (k+1) or (k mod n)+1 th position.
//
//			So index 1 in (n-1) game is (1 + (k-1) mod n)+1 in n game
//			So index x in (n-1) game is (x + (k-1) mod n)+1 in n game
//
//			If we started counting with 0 then mapping would have been (x + k mod n)



int JosephusProblem(int n, int k) {
	if(n == 1) {
		return 1;
	} else {
		return ((JosephusProblem(n-1, k) + (k-1)) % n) + 1;
	}
}

int main() {
	cout << "The solution for n=3  and k=7  is: " << JosephusProblem(3,7) << endl;	//3
	cout << "The solution for n=4  and k=4  is: " << JosephusProblem(4,4) << endl;	//2
	cout << "The solution for n=5  and k=3  is: " << JosephusProblem(5,3) << endl;	//4
	cout << "The solution for n=5  and k=8  is: " << JosephusProblem(5,8) << endl;	//1
	cout << "The solution for n=5  and k=9  is: " << JosephusProblem(5,9) << endl;	//2
	cout << "The solution for n=14  and k=2  is: " << JosephusProblem(14,2) << endl;//13
}
