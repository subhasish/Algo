/*
 * 11.SalaryCap.cpp
 *
 * Problem: Your office is trying to meet a total salary target of all employees by putting a salary cap.
 * 			Design an algorithm for computing the salary cap, given existing salaries and the target payroll.
 *
 *  Created on: Mar 14, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			The cap amount is to be searched in increasing order. The amount is to be matched for each salary.
//			So salaries are to be sorted.

double FindSalaryCap(vector<double>& salaries, double target)
{
	sort(salaries.begin(), salaries.end());

	double sum = 0;
	size_t remaining = salaries.size();
	for(size_t i=0 ; i<salaries.size() ; ++i) {
		double total_at_here = sum + salaries[i] * remaining;
		if(total_at_here > target) {
			return (target - sum)/remaining;
			break;
		}

		sum += salaries[i];
		--remaining;
	}

	return -1; // No cap needed
}


int main()
{
	vector<double> salaries = {20, 30, 40, 90, 100};
	cout << "Cap = " << FindSalaryCap(salaries, 210);
}
