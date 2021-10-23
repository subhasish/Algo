/*
 * 08.TimerWithdelete.cpp
 *
 * Problem: Design a timer that manages the execution of deferred threads.
 *          The timer will take tasks to be executed in future and execute them accordingly.
 *          A task can also be deleted.
 *
 *          This can be used to perform tasks for calendar events.
 *
 *
 *  Created on: Aug 13, 2018
 *      Author: subha
 */

// Solution:
//          The timer should store all the events but no need to be wake until next task to execute.
//          So we can maintain all tasks in a priority queue. Priority will be time to execute the
//          task. Then timer can sleep until the task at the top the priority queue needs to execute.
//
//          If we need to remove the a future event then we need to maintain a hash table.
//          To remove an random event we cannot use the priority queue directly. We could have created
//          our own priority queue. But using BST also gets us minimum and iterator and erase method.
//
//			Similar to other programs hash table will map the key to the iterator on to the BST and
//			can be used to delete entries easily.
//
//          If add and removal happens on another thread then queue should be locked to avoid race
//          condition.

#include <bits/stdc++.h>
#include <future>

using namespace std;

struct Event {
    string name;	// Assuming no event can have same name. Otherwise, use id.
    time_t time;

    Event(string s, time_t t): name(s), time(t) {}
};

struct EventComparator
{
	bool operator() (const Event& a, const Event& b) const
	{
		if(a.time != b.time) {		// Otherwise there will be only one entry for a time
			return a.time < b.time;
		} else {					// Assuming no event can have same name. Otherwise, use id.
			return a.name < b.name;
		}

	}
};

// Sends some notification when calendar event occurs
void TimerHandler(string name)
{
    time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout << "Event: "<< name << ". Occurred at: " << ctime(&t) << endl;
    cout << "Thread Id: " << this_thread::get_id() << endl;
}

typedef set<Event, EventComparator> EventSet;
typedef EventSet::iterator EventSetIter;
typedef map<string, EventSetIter> MapToEventSet;


void DispatcherThread(EventSet& bst, MapToEventSet& key_to_set, mutex& mtx)
{
    while(!bst.empty()) {
        Event e = *bst.begin();
        time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());

        if(now >= e.time) {
        	lock_guard<mutex> lg(mtx);

            bst.erase(bst.begin());
            key_to_set.erase(e.name);

            thread(TimerHandler, e.name).detach();

        } else {
            cout << "Going to sleep for: " << (e.time - now) << " seconds." << endl;
            this_thread::sleep_for(chrono::seconds(e.time-now));
        }
    }
}

void DeleteEventThread(EventSet& bst, MapToEventSet& key_to_set, mutex& mtx)
{
	auto it = key_to_set.find("third");
	if(it != key_to_set.end()) {
		lock_guard<mutex> lg(mtx);

		bst.erase(it->second);
		key_to_set.erase(it);
	}
}

int main()
{
    time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());

    // Populate data

    EventSet bst;
    MapToEventSet key_to_set;

    auto p = bst.emplace(Event("first", t + 5));
    key_to_set.emplace("first",p.first);
    p = bst.emplace(Event("second", t + 10));
    key_to_set.emplace("second",p.first);
    p = bst.emplace(Event("sixth", t + 30));
    key_to_set.emplace("sixth",p.first);
    p = bst.emplace(Event("fifth", t + 25));
    key_to_set.emplace("fifth",p.first);
    p = bst.emplace(Event("fourth", t + 20));
    key_to_set.emplace("fourth",p.first);
    p = bst.emplace(Event("third", t + 15));
    key_to_set.emplace("third",p.first);

    mutex mtx;

    thread t1(DispatcherThread, ref(bst), ref(key_to_set), ref(mtx));
    thread t2(DeleteEventThread, ref(bst), ref(key_to_set), ref(mtx));

    if(t1.joinable())
    	t1.join();
    if(t2.joinable())
    	t2.join();

    this_thread::sleep_for(chrono::seconds(5));
}
