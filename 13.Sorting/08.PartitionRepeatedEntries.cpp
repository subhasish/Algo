/*
 * 08.PartitionRepeatedEntries.cpp
 *
 * Problem: You are given an array of student objects. Each student has an integer valued age field that is to be treated as a key.
 * 			Rearrange the elements of the array so that students of equal age appear together.
 *
 * 			The order in which different age appear is not important.
 * 			How would your solution change if ages have to appear in sorted order?
 *
 *  Created on: Mar 10, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Sorting can solve the problem. But in O(n log n).
//			Now number of distinct age will be small compared to the size of input. So something like counting sort can be done in O(n).
//			Counting sort is counting number of frequencies for each value and then compute the offset for each values as cumulative. Then place values directly.
//
//			That strategy is easy for normal integers, but harder for objects.
//			We will have to use hash tables to compute the count and offsets for objects.
//
//			If we have extra space for result array then it is easy. But it is still possible to put every element in their correct position through cyclic rotation.
//			Here we can use the two hash tables to facilitate the cyclic positioning. Conceptually similar to 10.ApplyPermutation.cpp in Array.
//
//			*** Difficult logic ***
//
//			One thing need to be clear at cyclic rotation that not to touch the items that are already in their correct position.
//			How can we ensure that without extra map saying which elements are done or not?
//
//			Let item at position 0 needs to go to position 3. Then clearly item at position 3 is not in its correct position.
//			Then we can put it in its correct position.
//
//			But how to know item at position i is not in its correct position? We can use the map from item to offset to keep track of
//			items not placed so far and remove item from that map when all of its items are placed.
//
//			How to know when all items of an age are placed? We can use the map of item to count to track that.
//
//			If we find an item A in offset map that needs to position i, we know item is in position in not in its correct place.
//			Now we have two choice, to find the item A that needs to go to i. But among several A's we do not know which one to place.
//			So better t take item at position i and place it in its correct position. So we again look up the offset map to find where
//			item at i needs to go, say j. Note that item at j is also not in its correct place. Then we swap items at i and j.
//			We also needs to update offset map for item that was at position i; either increment the offset or remove all of them are
//			properly placed.

struct Person {
	string name;
	int age;
};

void swap(Person& a, Person& b) {
	Person t = a; a = b; b = t;
}

void GroupByAge(vector<Person>& people)
{
	unordered_map<int, int> age_to_count;
	unordered_map<int, int> age_to_offset;		// I would use map here to get things in order

	for(const Person& p: people) {
		++age_to_count[p.age];
	}

	int offset = 0;
	for(auto p: age_to_count) {
		age_to_offset[p.first] = offset;
		offset += p.second;
	}

	for(auto it: age_to_offset) {
		cout << "(" << it.first << ", " << it.second << "), ";
	}
	cout << endl;

	while(!age_to_offset.empty()) {
		auto a_displaced_item = age_to_offset.begin();	// We are NOT moving this item, but item now in its position!!!

		int from_offset = a_displaced_item->second;		// Position from where we are moving item to its correct position
		Person from = people[from_offset];

		int to_offset = age_to_offset[from.age];		// Position where the item needs to go

		swap(people[from_offset], people[to_offset]);

		// Use age_to_count to see if we are done with a particular age
		--age_to_count[from.age];
		if(age_to_count[from.age] > 0) {
			++age_to_offset[from.age]; 	// For this age next time use next past the current position used
		} else {
			age_to_offset.erase(from.age);
		}
	}
}


int main()
{
	vector<Person> persons = { {"Greg",14}, {"John",12}, {"Tim",14}, {"Andy",11}, {"Jim",13}, {"Phil",12}, {"Bob",13}, {"Chip",13} };
	GroupByAge(persons);

	for(const Person& p: persons) {
		cout << p.age << ", " << p.name << endl;
	}
}
