/*
 * 03.Interleave.cpp
 *
 * Problem: Create two threads such that one only prints even number and another prints odd number.
 * 			Write code such that the two threads running concurrently prints number from
 * 			1 to 100 in order.
 *
 *  Created on: Aug 1, 2018
 *      Author: subha
 */

// Solution:
//			It is similar to the problem where n threads were executing one critical function
//			in tandem.
//
//			When one is done it must wait for another and also notify another to come out of
//			it waiting.

#include <bits/stdc++.h>

using namespace std;

class OddEvenMonitor
{
	bool turn;
	condition_variable convar;
	mutex mtx;

public:
	static const bool ODD_TURN = true;
	static const bool EVEN_TURN = false;

	OddEvenMonitor(): turn(ODD_TURN) {}

	void WaitTurn(bool old_turn) {
		unique_lock<mutex> ul(mtx);
		while(turn != old_turn) {
			convar.wait(ul);
		}
	}

	void ToggleTurn () {
		lock_guard<mutex> lg(mtx);
		turn = !turn;
		convar.notify_all();
	}

};


void OddThread(OddEvenMonitor& monitor)
{
	for(int i=1 ; i<100 ; i +=2 ) {
		monitor.WaitTurn(OddEvenMonitor::ODD_TURN);
		cout << i << endl;
		monitor.ToggleTurn();
	}
}

void EvenThread(OddEvenMonitor& monitor)
{
	for(int i=2 ; i<=100 ; i +=2 ) {
		monitor.WaitTurn(OddEvenMonitor::EVEN_TURN);
		cout << i << endl;
		monitor.ToggleTurn();
	}
}


int main()
{
	OddEvenMonitor monitor;
	thread t1(OddThread, ref(monitor));
	thread t2(EvenThread, ref(monitor));

	t1.join();
	t2.join();
}
