/*
 * 00.CondVar.cpp
 *
 * Problem: Implement signaling between threads.
 *
 *  Created on: Jul 24, 2018
 *      Author: subha
 */


#include <bits/stdc++.h>
//#include <thread>
//#include <mutex>
//#include <condition_variable>

using namespace std;

// Solution:
//			condition_variable is used as a mechanism to signal among threads.
//			It can only be used along with mutex.
//
//			Without signal if a thread waits on while loop then CPU usage will be high.
//			But condition_variable.wait(unique_lock) can wait for the condition to be true,
//			with negligible CPU usage.
//
//			Condition_variable takes a uniqueue_lock.
//			It releases the mutex of the lock while waiting and acquires the lock back while
//			coming out of the wait.
//
//			The notifying thread does not need to hold the lock on the same mutex as the one held
//			by the waiting thread(s); in fact doing so is a pessimization, since the notified thread
//			would immediately block again, waiting for the notifying thread to release the lock.
//
//			Generally waiting should be done inside a loop. If thread is waiting for some condition
//			to happen and notification arrives without that condition being true then the
//			thread should again go back to waiting.
//
//			Two separate concepts waiting for some resource and waiting for some condition to
//			become true. For first one we use mutex, for second one we use the condition variable.
//
//			But there can also be the case when one thread coming out of the lock making the
//			condition false. In that case waiting loop should be inside lock so that each thread
//			can mutual exclusively access and alter the condition. See semaphore example.

void ThreadFn(mutex& mtx, condition_variable& convar, bool& clean)
{
	cout << "T" << this_thread::get_id() << ": Inside the thread function." << endl;

	{
		unique_lock<mutex> u_lock(mtx);

		cout << "T" << this_thread::get_id() << ": Thread acquired the lock." << endl;
		cout << "T" << this_thread::get_id() << ": Thread will now wait for the condition variable." << endl;

		while(!clean) {
			convar.wait(u_lock);
		}
	}

	cout << "T" << this_thread::get_id() << ": Thread came out of wait. Terminating.." << endl;
}

int main()
{
	mutex mtx;
	condition_variable convar;
	bool clean = false;

	cout << "Main: Inside main thread => " << this_thread::get_id() << endl;

	thread t1 {ThreadFn, ref(mtx), ref(convar), ref(clean)};
	thread t2 {ThreadFn, ref(mtx), ref(convar), ref(clean)};

	cout << "Main: main thread is sleeping to avoid race condition.." << endl;

	this_thread::sleep_for(chrono::seconds(1));

	cout << "Main: main thread came out of sleep.." << endl;

	{
		cout << "Main: main thread waiting to lock" << endl;

		lock_guard<mutex> lock_g(mtx);

		cout << "Main: main thread got the lock" << endl;

	}

	cout << "Main: main thread signaling.." << endl;
	convar.notify_all();	// SOULD notify after releasing lock, as others try to lock immediately

	this_thread::sleep_for(chrono::seconds(1));

	cout << "Main: main thread signaling again.." << endl;
	clean = true;
	convar.notify_all();

	t1.join();
	t2.join();

	return 0;
}
