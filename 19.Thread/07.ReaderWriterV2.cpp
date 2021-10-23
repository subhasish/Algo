/*
 * 06.ReaderWriterV1.cpp
 *
 * Problem: Need to synchronize the read and write to an shared object. No thread should access
 * 			the object for read or write while another thread opened it for writing.
 * 			Two or more readers may access it the same time.
 *
 * 			Version 2:
 * 			In version 1 solution we have such that if a writer is waiting for a reader to finish
 * 			and another reader comes then the second reader gets preference over the writer
 * 			that was waiting. This may cause the writer to starve.
 *
 * 			So we want no writer to wait more than necessary, once added to the queue.
 *
 *  Created on: Aug 12, 2018
 *      Author: subha
 */

// Solution:
//			Previous solution was to maintain two locks and one counter for number of
//			reader process. Writer was waiting until number of reader becomes 0.
//			But it was causing a reader preference; a reader that comes later than writer
//			would get preference if writer waiting for another reader.
//
//			Easiest way to avoid that is to make every reader wait on writer lock. Readers
//			will immediately release it but in mean time they will not cause writes to starve.

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
			lock_guard<mutex> lgw(RW::w_mutex);
			lock_guard<mutex> lgr(RW::r_mutex);
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
	thread(Writer).detach();
	thread(Reader).detach();
	thread(Writer).detach();

	this_thread::sleep_for(chrono::seconds(30));
}
