/*
 * 00.STLSort.cpp
 *
 * Problem: Use STL sorts for custom types
 * 			Use both sort from algorithm and list.sort()
 *
 *  Created on: Mar 5, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// C++:
//		See use of lambda as comparator. Notice that lambda is not made a constant function.

int main()
{
	vector<int> numberArray = {6346,346,243,7,-365,-362,7};

	// Sort ascending
	sort(numberArray.begin(),numberArray.end());
	for(int i: numberArray) {
		cout << i << ", ";
	}
	cout << endl;

	// Sort descending
	sort(numberArray.begin(),numberArray.end(),greater<int>());
	for(int i: numberArray) {
		cout << i << ", ";
	}
	cout << endl;


	vector<string> strArray = {"amrita","pui","jeet","tito","subhasish","papai","rimpi"};

	// Sort as in dictionary
	sort(strArray.begin(),strArray.end());
	for(string str: strArray) {
		cout << str << ", ";
	}
	cout << endl;

	// Sort reverse dictionary
	sort(strArray.begin(),strArray.end(),greater<string>());
	for(string str: strArray) {
		cout << str << ", ";
	}
	cout << endl;

	// Sort based on length: Use lambda function as comparator
	sort(strArray.begin(), strArray.end(), [](const string& a, const string& b) { return a.length() < b.length(); });
	for(string str: strArray) {
		cout << str << ", ";
	}
	cout << endl;

	// list sort
	list<int> l(numberArray.begin(), numberArray.end());
	l.sort();
	for(int i:l) {
		cout << i << ", ";
	}
	cout << endl;
}


