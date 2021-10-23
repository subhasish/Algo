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
 * 			Version 3:
 * 			In version 2 when writer 1 has write lock, then writer 2 arrives and then reader 3,
 * 			there is no guarantee that writer 2 will write before reader 3. Both are waiting
 * 			for write lock anyone can get it.
 * 			All readers and writers should wait at least as possible based on their arrival.
 *
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
//			Then to remove reader preference we made every reader wait on writer lock. Readers
//			will immediately release it but in mean time they will not cause writes to starve.
//			But this does not enforce order. Any thread may starve.
//
//			We can have one dispatcher thread that maintains a queue of entries. Similar to
//			thread pool but here one thread looking up the queue and and then forking reading
//			and writing in separate threads.
//
//			If only readers are reading and next one is a reader then it will let that read.
//			In any case one writer is involved it will give it mutual exclusive access.
//
//			We still need to maintain reader count and whether any writer is writing.
//			We will need two condition variables to let dispatcher know:
//				1. When one reader/writer finishes, so that next waiting task may proceed.
//				2. When new tasks are added, so that dispatcher may resume working.
//
//			When needed dispatcher loop will wait based on states of previous of readers/writer.


#include <bits/stdc++.h>

using namespace std;

namespace RW {
	mutex rw_mutex;							// read write lock
	mutex q_mutex;							// queue lock
	condition_variable convar_rw;			// condition variable for no reader-writer conflict
	condition_variable convar_empty_queue;	// condition variable for empty queue

	int reader_count = 0;
	bool writing = false;

	int data = 7;
}

void RandomWait()
{
	//Random wait
	unsigned seed = chrono::system_clock().now().time_since_epoch().count();
	default_random_engine rgen(seed);

	unsigned sleep_ms = rgen() % 1000;
	this_thread::sleep_for(chrono::milliseconds(sleep_ms));
}

void Reader()
{
	cout << "Reader " << this_thread::get_id() << ": " << RW::data << endl;
	RandomWait();

	{
		lock_guard<mutex> lg(RW::rw_mutex);
		--RW::reader_count;
	}
	RW::convar_rw.notify_all();
}

void Writer()
{
	cout << "Writer " << this_thread::get_id() << ": " << ++RW::data << endl;
	RandomWait();

	{
		lock_guard<mutex> lg(RW::rw_mutex);
		RW::writing = false;
	}
	RW::convar_rw.notify_all();
}

enum class RWEnum{
	READ, WRITE
};

void Dispatcher(queue<RWEnum>& q)
{
	while(true) {
		RWEnum task;
		bool got = false;
		{
			unique_lock<mutex> u_lock(RW::q_mutex);
			if(!q.empty()) {
				task = q.front();
				//q.pop();  //DO NOT POP unless task is done or it is waiting!!
				got = true;
			}
		}

		if (got) {

			if(task == RWEnum::READ) {
				{
					unique_lock<mutex> u_lock(RW::rw_mutex);
					if(!RW::writing) {
						++RW::reader_count;
						thread(Reader).detach();
						{
							lock_guard<mutex> lg(RW::q_mutex);
							q.pop();	// POP only when the task is done
						}
					} else {
						while(RW::writing) {
							RW::convar_rw.wait(u_lock);
						}
					}
				}
			}
			else if(task == RWEnum::WRITE) {
				{
					unique_lock<mutex> u_lock(RW::rw_mutex);
					if(!RW::writing && RW::reader_count == 0) {
						RW::writing = true;
						thread(Writer).detach();
						{
							lock_guard<mutex> lg(RW::q_mutex);
							q.pop();	// POP only when the task is done
						}
					} else {
						while(RW::writing || RW::reader_count != 0) {
							RW::convar_rw.wait(u_lock);
						}
					}
				}
			}
		}

		{
			unique_lock<mutex> q_lock(RW::q_mutex);
			if(q.empty()) {
				RW::convar_empty_queue.wait(q_lock);
			}
		}
	}
}

int main()
{
	queue<RWEnum> q;
	thread(Dispatcher,ref(q)).detach();

	{
		lock_guard<mutex> lg(RW::q_mutex);
		q.emplace(RWEnum::READ);
		RW::convar_empty_queue.notify_all();
	}
	{
		lock_guard<mutex> lg(RW::q_mutex);
		q.emplace(RWEnum::READ);
		RW::convar_empty_queue.notify_all();
	}
	{
		lock_guard<mutex> lg(RW::q_mutex);
		q.emplace(RWEnum::READ);
		RW::convar_empty_queue.notify_all();
	}
	{
		lock_guard<mutex> lg(RW::q_mutex);
		q.emplace(RWEnum::READ);
		RW::convar_empty_queue.notify_all();
	}
	{
		lock_guard<mutex> lg(RW::q_mutex);
		q.emplace(RWEnum::WRITE);
		RW::convar_empty_queue.notify_all();
	}
	{
		lock_guard<mutex> lg(RW::q_mutex);
		q.emplace(RWEnum::WRITE);
		RW::convar_empty_queue.notify_all();
	}
	{
		lock_guard<mutex> lg(RW::q_mutex);
		q.emplace(RWEnum::READ);
		RW::convar_empty_queue.notify_all();
	}
	{
		lock_guard<mutex> lg(RW::q_mutex);
		q.emplace(RWEnum::READ);
		RW::convar_empty_queue.notify_all();
	}
	{
		lock_guard<mutex> lg(RW::q_mutex);
		q.emplace(RWEnum::WRITE);
		RW::convar_empty_queue.notify_all();
	}
	{
		lock_guard<mutex> lg(RW::q_mutex);
		q.emplace(RWEnum::READ);
		RW::convar_empty_queue.notify_all();
	}
	{
		lock_guard<mutex> lg(RW::q_mutex);
		q.emplace(RWEnum::READ);
		RW::convar_empty_queue.notify_all();
	}

	this_thread::sleep_for(chrono::seconds(30));
}
