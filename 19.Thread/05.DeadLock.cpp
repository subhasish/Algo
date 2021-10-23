/*
 * 05.DeadLock.cpp
 *
 * Problem: Deadlock occurs when a thread needs to acquire multiple locks and two or more threads
 * 			end up waiting for each other.
 *
 * 			The following program tries to transfer money from one account to another.
 * 			In the process it tries to lock both the accounts. It first tries to lock the
 * 			from account and then to account. So if a pair of accounts tries to transfer money
 * 			from one to another simultaneously then they can potentially get into deadlock.
 *
 *  Created on: Aug 6, 2018
 *      Author: subha
 */

// Solution:
//			Solution is to lock the resources in some universal order in every thread.
//			Some kind of id can be used.

#include <bits/stdc++.h>

using namespace std;

class Account
{
	int balance;
	int id;

	mutex mtx;
	static int global_id;

public:
	Account(int b) : balance(b), id(++global_id) {}

	int get_balance() {
		return balance;
	}

	static void Transfer(Account& from, Account& to, int amount) {
		thread(&Account::Move, &from, ref(to), amount).detach();
	}

private:
	bool Move(Account& to, int amount)
	{
		mutex& mtx1 = (id < to.id) ? mtx : to.mtx;
		mutex& mtx2 = (id < to.id) ? to.mtx : mtx;



//		lock_guard<mutex> lg(mtx);
		lock_guard<mutex> lg(mtx1);
		{
//			lock_guard<mutex> lg(to.mtx);
			lock_guard<mutex> lg(mtx2);

//			cout << id << ", " << to.id << " = " << amount << endl;

			if(amount > balance) {
				return false;
			}

			balance -= amount;
			to.balance += amount;
			return true;
		}
	}
};

int Account::global_id = 0;

int main()
{
	Account a(100), b(50);
	Account::Transfer(a,b,20);
	Account::Transfer(a,b,20);
	Account::Transfer(b,a,10);
	Account::Transfer(a,b,20);

	this_thread::sleep_for(chrono::seconds(3));		// Wait for transactions to finish

	cout << "Balance of A => " << a.get_balance() << endl;
	cout << "Balance of B => " << b.get_balance() << endl;


}
