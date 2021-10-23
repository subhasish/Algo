/*
 * 00.Future.cpp
 *
 * Problem: Implement asynchronous programming in C++
 *
 *  Created on: Jul 22, 2018
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
//			future<return type> is the type of future object.
//			It can be launched asynchronously or can be deferred to be run by same thread
//			when get is called.
//			future_object.get() function return the value returned by asynchronous function.
//			Calling get() multiple times will cause crash.
//			Validity of get() can be checked by valid() method.

int asyncFunc(int val)
{
	cout << "T1: Inside the asynchronous function." << endl;
	cout << "T1: Id => " << this_thread::get_id() << endl;
	return ++val;
}

int main()
{
	int val = 100;

	cout << "Main: Id => " << this_thread::get_id() << endl;

	future<int> fn = async(launch::async, asyncFunc, val); // @suppress("Invalid arguments")

	if(fn.valid())
		cout << fn.get() << endl;

	if(fn.valid())					// Without valid() check second get() will crash
		cout << fn.get() << endl;
	else
		cout << "Second call invalid" << endl;

	return 0;
}
