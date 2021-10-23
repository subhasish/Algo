/*
 * 08.OnlineKMostFrequentInWindow.cpp
 *
 * Problem: This is another variation of the online K most frequent problem.
 * 			Given a online server log that keeps growing, give the top k pages when asked,
 * 			within window size of W from the current page's visit time.
 *
 * 			Window size W is fixed for the log file.
 * 			You can assume that the visit time increases as we process the file.
 *
 *  Created on: Mar 24, 2018
 *      Author: subha
 */

// Related problems:
//			Heaps/00.OnlineTopK.cpp
//			HashTable/05.KMostFrequent.cpp
//			BST/08.OnlineKMostFrequent.cpp

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			The online K most frequent version of the problem is solved using a BST where can make
//			incremental updates while preserving the sortedness.
//			We used page-to-visit-counts in a balanced BST. The BST nodes store	(visit-count, page) pairs.
//			These pairs will be ordered by visit-count with ties broken on page.
//
//			Another challenge was how to update the page frequencies efficiently as BST is keyed based on
//			visit-counts and not on page id. Solution was additional data structure, namely hash table that
//			maps pages to (visit-count,page) pair in the BST.
//
//			Here additional challenge is to consider only pages that are inside a recent time window
//			of W from the recent most page.
//			The natural way to age-out something is to store them in a queue. Whenever we add a new entry
//			it goes to the head of the queue and we pop entries which are outside the window size.
//
//			The rest of the algorithms will be very similar. Only when a page is evicted from the queue
//			we need to decrement its count.
//
//			Another challenge was we want to update the visit count in BST, but that is part of key
//			and not the value. Keys are not mutable and cannot be updated.
//			Solution was to delete the node increment count and add it back.
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

	struct PageEntry {
		int id, visit_time;
	};

	set<CountId> count_id_bst;										// BST of count and page id
	unordered_map<int, set<CountId>::iterator> pageId_to_bstnode;	// page id to BST node map
	int W;															// window size
	queue<PageEntry> entry_queue;									// pages as per entry sequence

	// Function to add another page to log
	void add(int pageId, int visit_time)
	{
		entry_queue.push(PageEntry{pageId, visit_time});			// Enter in the queue

		auto it = pageId_to_bstnode.find(pageId);					// Find the node in BST using hash table

		if(it == pageId_to_bstnode.end()) {							// Not found

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

		while(!entry_queue.empty() && (entry_queue.front().visit_time < visit_time - W)) {
			int page_to_evict = entry_queue.front().id;
			entry_queue.pop();

			// Remove
			auto it = pageId_to_bstnode.find(page_to_evict);
			if(it != pageId_to_bstnode.end()) {
				auto it_to_bst = it->second;
				CountId oldNode = *it_to_bst;
				int newCount = oldNode.count-1;

				count_id_bst.erase(it_to_bst);
				if(newCount > 0) {
					auto posIt = count_id_bst.emplace(CountId(newCount, page_to_evict));
					pageId_to_bstnode[page_to_evict] = posIt.first;
				} else {
					pageId_to_bstnode.erase(page_to_evict);
				}
			}
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
	log.W = 4; // window size 4

	log.add(7, 1);
	log.add(1, 2);
	log.add(20, 3);
	log.add(20, 6);
	log.add(1, 7);

	VI top1 = log.KMostFrequent(1);
	cout << "Top 1 after 5 entries: ";
	for(int id: top1) {
		cout << id << ", ";
	}
	cout << endl;


	log.add(1, 11);

	top1 = log.KMostFrequent(1);
	cout << "Top 1 after 6 entries: ";
	for(int id: top1) {
		cout << id << ", ";
	}
	cout << endl;

	log.add(7, 15);
	log.add(20, 17);
	log.add(20, 18);
	log.add(1, 19);
	log.add(7, 21);

	VI top2 = log.KMostFrequent(2);
	cout << "Top 2 entries after all the inputs: ";
	for(int id: top2) {
		cout << id << ", ";
	}
	cout << endl;

}
