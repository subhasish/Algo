/*
 * 03.DeleteDuplicate.cpp
 *
 * Problem: Delete duplicate entries from an array of objects based on one member in the object. Array is not sorted.
 *
 *  Created on: Mar 8, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			O(n) solution is to create hash table that is unordered_set, but that is O(n) additional space.
//			To avoid additional space we can sort and use similar logic we used in Array section problem 05.DeleteDuplicate.cpp
//
// C++:
//			There is C++ STL function "unique" which removes consecutive duplicate elements.
//			It returns the iterator pointing to one element beyond the last unique element.
//			So general practice is to delete all elements from that position to the end.

struct Name {
	string first_name, last_name;

	bool operator==(const Name& that) const {   // Used by unique
		return first_name == that.first_name;
	}

	bool operator<(const Name& that) const {    // Used by sort
		return first_name < that.first_name;
	}
	Name(string a, string b): first_name(a), last_name(b) {}
};

void DeleteDuplicate(vector<Name>& names)
{
	sort(names.begin(), names.end());
	names.erase(
			unique(names.begin(), names.end()),
			names.end());
}

int main()
{
	vector<Name> names = { Name("pui", "saha"), Name("tito", "saha"),Name("pui", "saha"),Name("pui", "saha"), Name("jeet", "saha") };
	DeleteDuplicate(names);
	for(const Name& n: names) {
		cout << n.first_name << " " << n.last_name << endl;
	}
}
