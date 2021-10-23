/*
 * 01.PairedTask.cpp
 *
 * Problem: We are given a set of even number of tasks by the time it takes to complete.
 * 			Those tasks are to be assigned to workers and each worker can complete two tasks.
 * 			Assign the tasks so as to minimize total time taken to complete all the tasks.
 *
 *  Created on: May 20, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Task that takes the longest needs most help, so pair it up smallest one

typedef pair<int, int> task_pair;
typedef vector<task_pair> task_assignment;

task_assignment OptimumTaskAssignment(vector<int> task_duration)
{
	sort(task_duration.begin(), task_duration.end());

	task_assignment result;
	for(int i=0, j=task_duration.size()-1 ; i<j ; ++i, --j) {
		result.emplace_back(task_pair{task_duration[i], task_duration[j]});
	}

	return result;
}


int main() {
	task_assignment result = OptimumTaskAssignment({5, 2, 1, 6, 4, 4});

	for(const task_pair& tp: result) {
		cout << tp.first << ", " << tp.second << endl;
	}
}
