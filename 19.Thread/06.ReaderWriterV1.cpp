/*
 * 06.ReaderWriterV1.cpp
 *
 * Problem: Need to synchronize the read and write to an shared object. No thread should access
 * 			the object for read or write while another thread opened it for writing.
 * 			Two or more readers may access it the same time.
 *
 * 			Version 1:
 * 			No readers cannot be kept waiting if resource is only opened for reading.
 *
 *  Created on: Aug 12, 2018
 *      Author: subha
 */

// Solution:
//			One solution is to let every thread lock the resource. But it is sub-optimal, two
//			readers cannot access it simultaneously.
//
//			Otherwise we need to track whether any process is reading it. It can be done by
//			maintaining a count of processes reading it. Each reader will increment it upon
//			entry and decrement it upon exit.
//
//			Writer on the other hand first will grab the write lock and then get the read lock.
//			Once it gets the read lock it will check the counter and see if it is 0. If 0 then
//			it will perform the write and then release all the locks.

#include <bits/stdc++.h>

using namespace std;

namespace RW {
	mutex r_mutex;							// read lock
	mutex w_mutex;							// write lock
	condition_variable convar_no_reader;	// condition variable for no reader
	int reader_count = 0;					// reader count

	int data = 7;
}

void DoSomething()
{
	//Random wait
	unsigned seed = chrono::system_clock().now().time_since_epoch().count();
	default_random_engine rgen(seed);

	unsigned sleep_ms = rgen() % 1000;
	this_thread::sleep_for(chrono::milliseconds(sleep_ms));

	return;
}

void Reader()
{
	while(true) {
		{
			lock_guard<mutex> lg(RW::r_mutex);
			++RW::reader_count;
		}

		cout << "Read: " << RW::data << endl;

		{
			lock_guard<mutex> lg(RW::r_mutex);
			--RW::reader_count;
			RW::convar_no_reader.notify_all();
		}

		DoSomething();
	}
}

void Writer()
{
	while(true) {
		{
			lock_guard<mutex> lg(RW::w_mutex);
			bool done = false;
			while(!done) {
				unique_lock<mutex> ul(RW::r_mutex);
				if(RW::reader_count == 0) {			// No reader
					cout << "Writer: " << ++RW::data << endl;
					done = true;
				} else {
					RW::convar_no_reader.wait(ul);
				}
			}
		}
		DoSomething();
	}
}

int main()
{
	thread(Reader).detach();
	thread(Reader).detach();
	thread(Writer).detach();
	thread(Reader).detach();
	thread(Writer).detach();

	this_thread::sleep_for(chrono::seconds(30));
}
