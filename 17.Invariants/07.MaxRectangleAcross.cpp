/*
 * 07.MaxRectangleAcross.cpp
 *
 * Problem: Write a program that takes an input array and returns the pair of entries that would
 * 			create maximum rectangle using minimum of the two and distance between them.
 *
 * 			You can also think it as amount of water trapped between the two lines of that height.
 *
 *  Created on: Jun 3, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			It can be solved in a similar fashion as in two-sum problem.
//
//			We can start by considering first and last line. Then we can ignore the minimum
//			of the two and consider next line.
//
//			Logic is that the distance of the line is anyway decreasing, now we cannot increase
//			the area by keeping the smaller of the two. So leave the smaller and explore all
//			possibilities for maximum.

int GetMaxRectangleAcross(const vector<int>& A)
{
	int curr_max = 0;
	for(int i=0, j=A.size()-1 ; i<j ;) {
		int width = j-i;
		curr_max = max(curr_max, width * min(A[i], A[j]));

		if(A[i] < A[j]) {
			++i;
		} else {
			--j;
		}
	}

	return curr_max;
}

int main()
{
	vector<int> A = {1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1};

	cout << GetMaxRectangleAcross(A) << endl;
}

