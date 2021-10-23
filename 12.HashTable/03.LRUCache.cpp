/*
 * 03.LRUCache.cpp
 *
 * Problem: Implement a LRU (Least Recently Used) cache where we store ISBN of a book and their corresponding price.
 * 			If an ISBN present then insert should not update the price but should make it most recent entry.
 * 			Similarly find should make one most recent entry.
 *
 *  Created on: Feb 21, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//				ISBN to price is a map, but here we have limited size.
//				Problem is to find LRU entry while evicting a node in case of overflow.
//
//				A queue would be good to track the LRU property. But it has to be doubly linked list implementation
//				so that an entry can be moved from middle to the front.
//
//				To readily know where an entry reside in the queue given an ISBN key
//				we would also store the pointer/iterator to the queue in the map itself.
//				We would need this to move a entry to the front of the queue.
//
//
//				We would store the key in the queue, so that when we remove the LRU entry from tail
//				we can locate the entry in the map using the key and remove it from there.
//
// C++:
//				Capacity could be the template parameter of the class. Template parameter will be of type size_t.
//
//				STL list<> can be used for the doubly linked list.

template<size_t capacity>
struct LRUCache
{
private:
	unordered_map<string, pair<int, list<string>::iterator>> cache;  // Key: ISBN string, Value: Pair of price and iterator to LRU queue
	list<string> lru_queue;

	typedef unordered_map<string, pair<int, list<string>::iterator>> Table;
	typedef pair<Table::iterator, bool> AddSuccess;

	void MoveToFrontOfQueue(Table::iterator& cache_it)
	{
		list<string>::iterator queue_it = cache_it->second.second;

		auto val = *queue_it;						// Save the value of the entry to be deleted
		lru_queue.erase(queue_it);					// Delete the entry
		lru_queue.emplace_front(val);				// Create new entry in front with same value

		cache_it->second.second = lru_queue.begin();	// New entry at the front. Update the entry in map
	}


public:

	bool Lookup(string isbn, int* price)
	{
		auto cache_it = cache.find(isbn);

		if(cache_it == cache.end()) {
			return false;
		}

		// Found. Return price and bring the entry to the front in the queue
		*price = cache_it->second.first;
		MoveToFrontOfQueue(cache_it);
		return true;
	}

	AddSuccess Insert(string isbn, int price)
	{
		AddSuccess ret = cache.emplace(isbn, make_pair(price, lru_queue.begin() /* dummy */));

		if(ret.second == true) 								// New entry
		{
			lru_queue.emplace_front(isbn);						// Insert in the queue and update the iterator in
			ret.first->second.second = lru_queue.begin();

			if(cache.size() > capacity)							// caused overflow
			{
				cache.erase(lru_queue.back());					// Remove LRU entry from map
				lru_queue.pop_back();							// Remove LRU entry from queue
			}
		}
		else												// Existing entry: Insertion was Not done, but iterator was returned
		{
			MoveToFrontOfQueue(ret.first);						// Move to the front of the queue
		}

		return ret;
	}

	bool Erase(string isbn)
	{
		auto it = cache.find(isbn);

		if(it == cache.end()) 		// Not found
		{
			return false;
		}

		lru_queue.erase(it->second.second);
		cache.erase(isbn);
		return true;
	}

	void Print()
	{
		cout << "ISBN cache: " << endl;
		for(auto item: cache)
		{
			cout << setw(12) << item.first << ": " << item.second.first << endl;
		}
		cout << endl;
	}

	void PrintOrder()
	{
		cout << "ISBN cache in LRU order: " << endl;
		for(string isbn: lru_queue)
		{
			cout << setw(12) << isbn << endl;
		}
		cout << endl;
	}
};


int main()
{
	LRUCache<3> isbn_price;
	int price;

	isbn_price.Insert("Amrita", 5);
	isbn_price.Insert("Subhasish", 3);
	isbn_price.Insert("Pui", 1);
	isbn_price.Lookup("Amrita", &price);
	isbn_price.Insert("Tito", 6);

	isbn_price.Print();
	isbn_price.PrintOrder();
}
