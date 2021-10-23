/*
 * 00.Semaphore.cpp
 *
 * Problem: Implement Semaphore acquire and release.
 *
 *  Created on: Jul 25, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Using mutex, lock and condition variable should be able to able to achieve this by
//			maintaining two variables maximum number of locks allowed and number of locks currently
//			taken.
//
//			If current lock taken is maximum then thread will wait. When some thread releases one
//			lock it notifies all other threads.
//			Reading and updating the taken variable should be done inside mutex.


struct Semaphore{
	int max_available;
	int taken;
	mutex mtx;
	condition_variable convar;

	Semaphore(int max) : max_available(max), taken(0) {}

	void Acquire() {
		unique_lock<mutex> u_lock(mtx);

		while(taken == max_available) {
			// We do not have mutex lock but no available resource
			convar.wait(u_lock);
		}

		++taken;
	}

	void Release() {
		lock_guard<mutex> lock_g(mtx);
		--taken;
		convar.notify_all();
	}
};


void ThreadFn(Semaphore& sema)
{
	cout << "T" << this_thread::get_id() << ": Inside thread function. Will wait on semaphore. "<< endl;
	sema.Acquire();

	// Do some stuff that a function could do.
	// Here we would wait randomly.

//	random_device rd;
//	default_random_engine generator(rd());

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);

	uniform_int_distribution<int> i_dist(1,1000);
	int randomNumber = i_dist(generator);

	cout << "T" << this_thread::get_id() << ": Got the semaphore." << endl;
	cout << "T" << this_thread::get_id() << ": Sleeping for " << randomNumber << " milliseconds." << endl;

	this_thread::sleep_for(chrono::milliseconds(randomNumber));

	cout << "T" << this_thread::get_id() << ": Coming out of sleep and releasing semaphore" << endl;

	sema.Release();
}

int main()
{
	Semaphore sema(3);

	thread t1(ThreadFn, ref(sema));
	thread t2(ThreadFn, ref(sema));
	thread t3(ThreadFn, ref(sema));
	thread t4(ThreadFn, ref(sema));
	thread t5(ThreadFn, ref(sema));
	thread t6(ThreadFn, ref(sema));
	thread t7(ThreadFn, ref(sema));

	cout << "Main: Created seven threads." << endl;

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();

	return 0;
}
