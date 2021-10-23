/*
 * 08.OnlineKMostFrequent.cpp
 *
 * Problem: This is the online version of the KMostFrequent problem.
 * 			Given a online server log that keeps growing, give the top k pages when asked.
 *
 *  Created on: Mar 24, 2018
 *      Author: subha
 */

// Related problems: Heaps/00.OnlineTopK.cpp and HashTable/05.KMostFrequent.cpp

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			This problem is different from both the related problems. In onlineTopK element is new; no need to track frequency.
// 			Other one is just static version of this problem.
//
//			So one brute force approach could be to do what do for static version is to traverse the hash table and find top k using a priority queue.
//			But doing that every time is not good, even if result has not changed much.
//
//			Another approach is to incremental updates while preserving the sortedness.
//			Height balanced BST is a good data structure to do such incremental updates.
//
//			Therefore it makes sense to store the page-to-visit-counts in a balanced BST. The BST nodes store
//			(visit-count, page) pairs. These pairs will be ordered by visit-count with ties broken on page.
//
//			Another challenge is how to update the page frequencies efficiently as BST is keyed based on visit-counts and not on page id.
//			Solution is additional data structure, namely hash table that maps pages to (visit-count,page) pair in the BST.
//
//			Another challenge is we want to update the visit count in BST, but that is part of key and not the value.
//			Keys are not mutable and cannot be updated. Solution is to delete the node increment count and add it back.
//
// C++:
//			next() of an iterator returns so remember to update

typedef vector<int> VI;

struct OnlineLog
{
	// Count and Id pair that will be stored in a BST node
	struct CountId
	{
		int count,id;

		CountId(int C, int I): count(C), id(I) {}

		bool operator< (const CountId& that) const
		{
			if(count == that.count) {
				return id < that.id;
			} else {
				return count < that.count;
			}
		}
	};

	set<CountId> count_id_bst;										// BST of count and page id
	unordered_map<int, set<CountId>::iterator> pageId_to_bstnode;	// page id to BST node map

	// Function to add another page to log
	void add(int pageId)
	{
		auto it = pageId_to_bstnode.find(pageId);			// Find the node in BST using hash table

		if(it == pageId_to_bstnode.end()) {					// Not found

			auto posIt = count_id_bst.emplace(CountId(1,pageId));	// Add with count 1. Get the iterator
			pageId_to_bstnode[pageId] = posIt.first;				// Add the iterator to hash table

		} else {

			auto it_to_bst = it->second;							// Get the BST iterator
			CountId oldNode = *it_to_bst;
			int newCount = oldNode.count+1;

			count_id_bst.erase(it_to_bst);							// Remove the node from BST
			auto posIt = count_id_bst.emplace(CountId(newCount, pageId));	// Add the new node and record its position
			pageId_to_bstnode[pageId] = posIt.first;						// Update the hash table with new iterator
		}
	}

	VI KMostFrequent(int k)
	{
		VI res;

		auto rit = count_id_bst.rbegin();		// rbegin() will give the most frequent one
		for(int i=0 ; i<k ; ++i)
		{
			res.push_back((*rit).id);
			//cout << "* " << (*rit).id << ": " << (*rit).count << endl;
			rit = next(rit);					// remember to update the iterator
		}
		return res;
	}
};

int main()
{
	OnlineLog log;

	log.add(23);
	log.add(3);
	log.add(2);
	log.add(23);
	log.add(3);
	log.add(33);
	log.add(233);
	log.add(33);
	log.add(23);

	VI top3 = log.KMostFrequent(3);
	cout << "Top 3: ";
	for(int id: top3) {
		cout << id << ", ";
	}
	cout << endl;

	log.add(2);
	log.add(4);
	log.add(2);
	log.add(33);
	log.add(2);

	top3 = log.KMostFrequent(3);
	cout << "Top 3: ";
	for(int id: top3) {
		cout << id << ", ";
	}
	cout << endl;
}
