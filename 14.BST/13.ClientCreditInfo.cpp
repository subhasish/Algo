/*
 * 13.ClientCreditInfo.cpp
 *
 * Problem: Design a data structure that implement the following methods of a client credit system:
 * 			Insert: Add client with specified credit, replace any existing
 * 			Delete: Delete a specified client
 * 			Lookup: Return the credit associated with a client
 * 			Add-to-all: Increment credit count for all clients
 * 			Max: Return the client with maximum credit
 *
 *  Created on: Mar 27, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Hash table is a natural data structure for this, however it does not support efficient
//			max operation, nor the simultaneous update.
//
//			For add-to-all we just keep a offset variable whose value applies to all.
//			One thing to be careful if we do that, then while inserting a new entry with some
//			credit should subtract the offset.
//
//			For max operation we can have a BST with credit as key. But many client can have same
//			key. So keep a set of such client as value in the map. Remove operation should
//			remove from the set. Alternatively <value, hash-key> pair can be used as BST key as
//			done in Online K Most Frequent problem.
//
//			But that will not support efficient lookup given a client. For that we will need a
//			hash table where client is the key.

struct ClientCreditInfo {

	int offset = 0;
	unordered_map<string, int>  client_to_credit;
	map<int, unordered_set<string>> credit_to_clients;

	void Insert(const string& client_id, int credit) {
		credit -= offset;

		Remove(client_id);
		client_to_credit[client_id] = credit;
		credit_to_clients[credit].emplace(client_id);
	}

	void Remove(const string& client_id) {
		int credit = client_to_credit[client_id];

		client_to_credit.erase(client_id);
		credit_to_clients[credit].erase(client_id);
		if(credit_to_clients[credit].empty()) { // remove empty node so not affect max operation
			credit_to_clients.erase(credit);
		}
	}

	int Lookup(const string& client_id) {
		if(client_to_credit.find(client_id) == client_to_credit.end())  return -1;
		return offset + client_to_credit[client_id];
	}

	void AddToAll(int C) {
		offset += C;
	}

	string Max() {
		auto iter = credit_to_clients.rbegin();		// Max at rbegin()

		return iter == credit_to_clients.rend() ? "" : *iter->second.begin();
	}

};

int main()
{
	ClientCreditInfo data;

	cout << "Max: " << data.Max() << endl;

	data.Insert("pui", 4);
	data.Insert("tito", 5);
	data.Insert("pui", 6);
	data.Insert("jeet", 3);
	data.Insert("papai", 9);

	cout << "Max: " << data.Max() << endl;

	data.Remove("papai");
	data.AddToAll(4);

	cout << "pui: " << data.Lookup("pui") << endl;
	cout << "Max: " << data.Max() << endl;
}
