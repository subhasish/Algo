/*
 * 01.CacheService.cpp
 *
 * Problem: Context of the problem is online spell correction service. Client send a input
 * 			string and the service returns an array of strings in its dictionary that are closest
 * 			to the input string.
 * 			The service caches results to improve performance. It saves the last queried input and
 * 			the result array for that string.
 *
 * 			Now implement proper synchronization so that cache is used properly.
 *
 *  Created on: Jul 28, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			The last query and last result are stored in two different variables.
//			While one threads checks with last query and determine that matches with that one,
//			another thread can update the result array. So the first thread will return
//			wrong result.
//
//			Solution is to synchronize each call using mutex.
//			But if mutex enforces only one thread to execute the service call at a time then
//			that would result in poor performance.
//
//			Solution is to lock just the part of the code that operate on the cached values
//
//			For creating multiple threads do thread.detach() and then make main thread wait
//			so that all the child thread can finish within that time.

typedef vector<string> VS;

VS DummyService(string w) {
	this_thread::sleep_for(chrono::milliseconds(50));	// mimic delay in service
	return {w+" hello", w + " world"};
}

class SpellCheckService
{
	static string w_last;
	static vector<string> closest_to_last_w;
	static mutex mtx;

  public:
	static vector<string> Service(string w)
	{
		vector<string> result;
		bool found = false;

		{
			lock_guard<mutex> lg(mtx);
			if(w == w_last) {
				result = closest_to_last_w;
				found = true;
				cout << "****** Found in cache for input => " << w << endl;
			} else {
				cout << "------ Not Found in cache for input => " << w << ", Cache = "<< w_last<< endl;
			}
		}

		if(!found) {
			result = DummyService(w);

			{
				lock_guard<mutex> lg(mtx);
				w_last = w;
				closest_to_last_w = result;
			}
		} else {

		}

		return result;
	}
};

string SpellCheckService::w_last;
vector<string> SpellCheckService::closest_to_last_w;
mutex SpellCheckService::mtx;


void ThreadFn(string w)
{
	VS res = SpellCheckService::Service(w);

	for (string s: res) {
		cout << "Query: " << w << ", one result: " << s << endl;
	}
}

int main()
{
	VS qs = { "ab", "cd", "ef", "ef", "cd", "cd", "cd", "cd", "ab"};

	for(string q: qs) {
		thread(ThreadFn, q).detach();
		this_thread::sleep_for(chrono::milliseconds(20));	// mimic delay between requests
	}

	this_thread::sleep_for(chrono::seconds(5));		// wait for all threads to finish
}
