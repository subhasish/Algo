/*
 * 02.MinimumWait.cpp
 *
 * Problem: Given service time for a set of queries, compute a schedule for processing the queries
 * 			that minimize the total wait time. Return the minimum wait time.
 *
 *  Created on: May 20, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Service time of each query adds to wait time of all queries remaining.
//			So for any assignment, swapping fast query before a slower query reduce wait time.

int MinimumWaitScheduling(vector<int> service_time)
{
	sort(service_time.begin(), service_time.end());

	int total_wait = 0;
	for(size_t i=0; i<service_time.size() ; ++i) {
		size_t number_remaining = service_time.size() - i - 1;
		total_wait += number_remaining * service_time[i];
	}
	return total_wait;
}

int main()
{
	cout << MinimumWaitScheduling({2, 5, 1, 3}) << endl;
}
