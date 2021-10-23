/*
 * 00.NameHiding.cpp
 *
 * Problem: Test if name hiding hides overloaded versions as well or not
 *
 *  Created on: Mar 19, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

class Base {
public:
	void func(int a) {}
	void func(int a, int b) {}
};

class Derived : public Base {
public:
	void func(int a) {}
};


int main()
{
	Derived d;

	d.func(1);
	//ERROR: But other overloaded version are hidden
	//d.func(1,2);
}
