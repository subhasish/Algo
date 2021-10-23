/*
 * 04.ThreadPool.cpp
 *
 * Problem: Implement thread pool, where work gets assigned to running threads instead of:
 * 				- Creating unlimited number of threads each time new work comes up. System
 * 				  can be overwhelmed.
 * 				- Avoiding unnecessary overhead of creating and deleting threads
 *
 *  Created on: Aug 1, 2018
 *      Author: subha
 */

// Solution:
//			Create some number of threads that will run infinite loop. They will wait for
//			work to be arrived using condition_variable.
//			Work will be added to some common data structure (say queue) and all threads
//			will be notified.
//
//			Due to locking one of the threads will pick up the work, do it, and put the
//			result in some shared data structure and again wait.

#include <bits/stdc++.h>

using namespace std;


int ThreadPoolFunction(mutex& mtx, condition_variable& convar, queue<int>& q)
{
	while(true) {
		unique_lock<mutex> u_lock(mtx);
		if(!q.empty()) {
			cout << "Thread " << this_thread::get_id() << " => " << q.front() << endl;
			this_thread::sleep_for(chrono::seconds(1));
			q.pop();
		}
		convar.wait(u_lock);
	}
	return 0;
}

int main()
{
	mutex mtx;
	condition_variable convar;

	queue<int> q;

	int num_threads = thread::hardware_concurrency();
	cout << "Number of threads = " << num_threads << endl;
	for(int i=0 ; i<num_threads ; ++i) {
		thread(ThreadPoolFunction, ref(mtx), ref(convar), ref(q)).detach();
	}

	unsigned int counter = 0;
	while(true) {
		this_thread::sleep_for(chrono::seconds(1));
		unique_lock<mutex> u_lock(mtx);
		q.emplace(++counter);
		convar.notify_all();
	}

	return 0;
}
