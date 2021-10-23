/*
 * 09.CollatzParallel.cpp
 *
 * Problem: Design an multi-threaded algorithm for checking the Collatz conjecture.
 * 			Make full use of the cores available to you.
 *
 *  Created on: Aug 20, 2018
 *      Author: subha
 */

//Solution:
//
//			One approach could be to send each number to one thread to test. But it would result in
//			spending more time in communicating.
//
//			Another approach would be to divide numbers in equal subrange for each threads and assign
//			each thread with one range. Problem with this approach is that one number takes
//			different amount of time than other. So it is quite possible that one thread takes
//			sufficiently longer time than another thread.
//
//			A good compromise is to divide the range in smaller intervals, which are large enough to
//			offset the thread overhead.
//
//			We can use the thread pool infrastructure and assign the work to pools.
//			Work pool is nothing but a shared queue, to maintain FIFO.
//
//			One way could be that each pool signal the dispatcher that it has finished its current
//			task and ask for more.
//			Instead, pool can just check the shared queue and take one task from top.
//			If queue is empty then they will wait. And the dispatcher will notify_all to let waiting
//			thread know.
//
//			All queue related operation will happen within lock.
//				- Getting an interval from the queue. But actual check over the range will happen outside the lock.
//				- Checking of queue is empty and waiting for refill


#include <bits/stdc++.h>

using namespace std;

// Check an individual number
bool CollatzCheck(int i, unordered_set<int>& visited)
{
	unordered_set<long long> sequence;
	long long test = i;

	// Test current i.
	while(test >= i) {								// All number less than i is already verified.
		if(!sequence.emplace(test).second) {		// Number in the current sequence => Infinite loop!!
			return false;
		}

		if(test % 2) {								// Odd number
			if(visited.find(test) != visited.end())	 {	// Already tested to converge
				break;
			}

			long long next_test = test * 3 + 1;
			if(next_test <= test) {					// Overflow!!
				return false;
			}
			test = next_test;
		} else {
			test /= 2;							// Even; halve it
		}
	}

	for(long long num: sequence) {					// All numbers on the sequence should be marked as verified
		visited.emplace(num);
	}
	return true;
}


int ThreadPoolFunction(mutex& mtx, condition_variable& convar, queue<pair<int,int>>& q)
{
	unordered_set<int> verified_numbers;	// Sharing this set across thread was causing access violations

	while(true) {
		pair<int,int> p;
		bool got = false;

		{
			unique_lock<mutex> ul(mtx);
			if(!q.empty()) {
				p = q.front();
				q.pop();

				got = true;
				// Outputting inside lock so appear good
				cout << "Thread " << this_thread::get_id() << " computing for => (" << p.first << ", " << p.second << ")" << endl;
			}
		}

		if(got) {
			for(int i=p.first ; i<=p.second ; ++i) {
				CollatzCheck(i, verified_numbers);
			}
		}

		{
			unique_lock<mutex> ul(mtx);
			if(q.empty()) {
				convar.wait(ul);
			}
		}

	}

	return 0;
}


int main()
{
	mutex mtx;
	condition_variable convar;

	queue<pair<int,int>> q;


	int num_threads = thread::hardware_concurrency();
	cout << "Number of threads = " << num_threads << endl;
	for(int i=0 ; i<num_threads ; ++i) {
		thread(ThreadPoolFunction, ref(mtx), ref(convar), ref(q)).detach();
	}

	int N = 10000000;
	int RANGE_SIZE = 100000;
	for(int i=0; i< N/RANGE_SIZE ; ++i) {
		unique_lock<mutex> u_lock(mtx);
		pair<int,int> p = make_pair(i * RANGE_SIZE + 1, (i+1) * RANGE_SIZE);
		q.emplace(p);
		convar.notify_all();
	}

	this_thread::sleep_for(chrono::seconds(60));

	return 0;
}



