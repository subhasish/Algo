/*
 * 00.Mutex.cpp
 *
 * Problem: Implement synchronization concept mutual exclusion.
 *
 *  Created on: Jul 24, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
//#include <thread>
//#include <mutex>

using namespace std;

// Solution:
//			Pass the mutex to the thread function so that they can lock it if needed.
//
//			There are two ways to lock a mutex:
//				1. lock_guard<mutex>  lock(mutex_object);
//				2. unique_lock<mutex> lock(mutex_objext);
//			These are RAII type, do not need to explicitly unlock. Mutex gets unlocked when
//			lock object goes out of scope.
//
//			The difference between these two is that unique_lock can be unlocked and locked again.
//
//			recursive_mutex allows same thread to acquire multiple locks. Generally considered
//			bad design.


void ThreadFn(mutex& mtx)
{
	cout << "T1: Inside the thread function => " << this_thread::get_id() << endl;

	lock_guard<mutex>  lock_grd(mtx);

	cout << "T1: Locked the mutex." << endl;

	this_thread::sleep_for(chrono::seconds(5));

}


int main()
{
	mutex mtx;

	cout << "Main: main thread starts => " << this_thread::get_id() << endl;

	thread t1 {ThreadFn, ref(mtx)};

	cout << "Main: main thread will now sleep, so that thread gets lock without race" << endl;
	this_thread::sleep_for(chrono::seconds(1));

	unique_lock<mutex> u_lock(mtx);
	cout << "Main: main thread got the lock.." << endl;

	u_lock.unlock();				// unique_lock can be unlocked and locked again
	u_lock.lock();

	t1.join();

	return 0;
}
