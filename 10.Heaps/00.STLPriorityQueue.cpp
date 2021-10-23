/*
 * 00.STLPriorityQueue.cpp
 *
 * Problem: Use STL priority_queue for strings that compares based on string length
 *
 *  Created on: Jan 21, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
	// Priority queue of strings, container used internally is vector and comparison function
	// 3rd template is function object that takes two strings and return boolean
	// Here, the constructor is taking lambda function

	// C++:
	// 		Match the parameter types of function object and lambda function
	priority_queue<string, vector<string>, function<bool(string&, string&)>>
			min_heap([] (string& s1, string& s2) {return s1.length() > s2.length(); });

	min_heap.push("Hello world saturn the great");
	min_heap.push("Hello world neptune");
	min_heap.push("Hello world mercury!");
	min_heap.push("Hello world earth");
	min_heap.push("Hello world jupitar");

	cout << "Min heap according to length of string: " << endl;
	while(!min_heap.empty()) {
		cout << min_heap.top() << endl;
		min_heap.pop();
	}
}


