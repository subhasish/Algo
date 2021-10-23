/*
 * 08.Timer.cpp
 *
 * Problem:	Design a timer that manages the execution of deferred threads.
 * 			The timer will take tasks to be executed in future and execute them accordingly.
 * 			A task can also be deleted.
 *
 * 			This can be used to perform tasks for calendar events.
 *
 *
 *  Created on: Aug 13, 2018
 *      Author: subha
 */

// Solution:
//			The timer should store all the events but no need to be wake until next task to execute.
//			So we can maintain all tasks in a priority queue. Priority will be time to execute the
//			task. Then timer can sleep until the task at the top the priority queue needs to execute.
//
//			If we need to remove the a future event then we need to maintain a hash table.
//			To remove an random event we cannot use the priority queue. See the BST implementation.
//
//			If add and removal happens on another thread then queue should be locked to avoid race
//			condition.

#include <bits/stdc++.h>
#include <future>

using namespace std;

struct Event {
	string name;
	time_t time;

	Event(string s, time_t t): name(s), time(t) {}
};

// Sends some notification when calendar event occurs
void TimerHandler(string name)
{
	time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());
	cout << "Event: "<< name << ". Occurred at: " << ctime(&t) << endl;
	cout << "Thread Id: " << this_thread::get_id() << endl;
}


int main()
{
	time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());
	time_t t5 = t + 5;
	time_t t10 = t + 10;

	priority_queue<Event, vector<Event>, function<bool(Event&,Event&)>>
		min_heap([](Event& a, Event& b) { return a.time > b.time; });

	min_heap.emplace(Event("first", t5));
	min_heap.emplace(Event("second", t10));

	while(!min_heap.empty()) {
		Event e = min_heap.top();
		time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());

		if(now >= e.time) {
			min_heap.pop();
			thread(TimerHandler, e.name).detach();

		} else {
			cout << "Going to sleep for: " << (e.time - now) << " seconds." << endl;
			this_thread::sleep_for(chrono::seconds(e.time-now));
		}
	}

	this_thread::sleep_for(chrono::seconds(5));
}
