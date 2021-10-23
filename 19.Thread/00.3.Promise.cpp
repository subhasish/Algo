/*
 * 00.Promise.cpp
 *
 * Problem: Implement asynchronous programming in C++
 *
 *  Created on: Jul 24, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
//#include <thread>
//#include <future>

using namespace std;

// Solution:
//			Future is the way of creating asynchronous programming in C++ without creating
//			explicit threads.
//			Promises are just containers of future.
//
//			Promise can set value of a future. It is used in conjunction with a separate thread that
//			sets the value of the future. Type of the value set is the template type of the promise.
//
//			The usefulness of this is that the thread need not to be completed to get the
//			value of the future. When one thread sets it, other thread gets it immediately.
//			Until then the other thread waits.

void PromiseFn(promise<int>& prom)
{
	cout << "T1: Inside the thread function => " << this_thread::get_id() << endl;

	this_thread::sleep_for(chrono::seconds(5));

	prom.set_value(200);
	cout << "T1: Has set the promise value. Going to sleep" << endl;

	this_thread::sleep_for(chrono::seconds(5));
	cout << "T1: Come out of sleep" << endl;
}

int main()
{
	promise<int> mypromise;
	future<int> fut = mypromise.get_future();

	cout << "Main: main thread starts => " << this_thread::get_id() << endl;
	thread t1 {PromiseFn, ref(mypromise)};

	cout << "Main: will wait for promise value." << endl;
	cout << fut.get() << endl;
	cout << "Main: got promise value. Waiting for thread." << endl;

	t1.join();

	return 0;
}


