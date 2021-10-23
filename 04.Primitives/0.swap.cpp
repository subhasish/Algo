/*
 * 0.swap.cpp
 *
 *  Created on: Jun 14, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

template<typename T>
void printV(vector<T> a)
{
	for (auto& x: a){
		cout << ' ' << x;
	}
	cout << endl;
}

int main()
{
	vector<int> a = {1,2,3};
	vector<int> b = {4,5,6};

	swap(a,b);

	cout << "a: " ;
	printV(a);

	cout << "b: ";
	printV(b);
}


