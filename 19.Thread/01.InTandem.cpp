/*
 * 01.InTandem.cpp
 *
 * Problem: There are n threads that calls a critical function in mutually exclusive way.
 * 			Implement a synchronization mechanism so that one thread cannot call the
 * 			critical function for (k+1)th time until all other threads have completed
 * 			their kth call to the critical function.
 *
 *  Created on: Jul 29, 2018
 *      Author: subha
 */


// Solution:
//			This kind of synchronization is better to be controlled by a master thread.
//			Here we used main thread to control this.
//			We also need one global counter to count how many threads have executed the
//			critical function in current iteration.
//
//			Each thread should wait after executing critical function for others to complete.
//			When everyone completes, main thread notify them to proceed. This can be done
//			using one condition_variable.
//
//			Main thread should also wait until everyone completes to unblock all threads.
//			This has to be separate condition_variable so that these don't mix up.
//			The last thread in an iteration should notify main thread to notify others.

#include <bits/stdc++.h>

using namespace std;


static int counter = 0;

void Critical(int i)
{
	cout << "ID: " << this_thread::get_id() <<  " / Critical: "  << i << ", Counter: " << counter<< endl;
}

void ThreadFn(int n, int k, mutex& mtx, condition_variable& convar, condition_variable& control_convar)
{

	for(int i=0 ; i<k ; ++i) {
		unique_lock<mutex> u_lock(mtx);

		++counter;

		Critical(i);

		if(counter == n) {					// If last in iteration
			control_convar.notify_all();	// Notify main thread, so that others gets unblocked
		}

		cout << "Thread " << this_thread::get_id() << " waiting!!" << endl;

		convar.wait(u_lock);				// Be in waiting until main unblocks all

		cout << "Thread " << this_thread::get_id() << " came out of wait!!" << endl;
	}

	cout << "Thread " << this_thread::get_id() << " exiting!! " << endl;
}

int main()
{
	int n = 4;
	int k = 5;

	mutex mtx;
	condition_variable convar;

	mutex control_mtx;
	condition_variable control_convar;

	vector<thread> pool;

	for(int i=0; i<n ; ++i) {
		pool.emplace_back(thread(ThreadFn, n, k, ref(mtx), ref(convar), ref(control_convar)));
	}

	for(int i=0; i<k ; ++i) {
		unique_lock<mutex> u_lock(control_mtx);

		while(counter != n) {				// Wait until all threads completes one iteration
			control_convar.wait(u_lock);	// Wait for to be notified by the final thread
		}

		cout << "Main came out" << endl;
		{
			lock_guard<mutex> lg(mtx);		// Wait for the final thread to go in wait mode
			counter=0;						// Reset the counter
		}

		convar.notify_all();				// Notify all threads that they may proceed
	}

	for(thread& t: pool) {
		if(t.joinable()) {
			t.join();
		}
	}

	cout << "Main exiting!!" << endl;

	return 0;
}
