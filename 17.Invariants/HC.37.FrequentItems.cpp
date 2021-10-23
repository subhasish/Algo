/*
 * HC.37.FrequentItems.cpp
 *
 * Problem: You are reading a sequence of strings separated by whitespace. You are allowed to read
 * 			the sequence twice. Device an algorithm that uses O(k) memory to identify the words that
 * 			occur more than n/k times, where n is the length of the sequence.
 *
 *  Created on: Jan 13, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * Solution:
 * 			For k=2 we have solved the problem in 17.Invariants/05.MajorityElement.cpp.
 * 			In general for general k, there cannot be more than (k-1) items that have frequency more
 * 			than n/k.
 *
 * 			Trying to solve for k=3 using similar strategy gives hint how to solve for the general
 * 			case. We can keep k candidates all the time. When we get an element from the candidates
 * 			we increase its frequency. When we get an element that is not in the set of candidates,
 * 			we can add it in its new entry. But that will increase the total candidates to k+1.
 * 			However, the same relative effect can be achieved by subtracting 1 from the count of each
 * 			of the candidates.
 *
 * 			When adding a new candidate we need to use the space of any old candidate with count 0.
 * 			All these can be done using hash table when we can remove a candidate when it reaches
 * 			count 0.
 *
 * 			We need to another pass to check if the items remaining actually has frequency more than
 * 			n/k. Otherwise if string is 'a a a a a a a a a b' and k = 3 we would output b which
 * 			will be incorrect.
 *
 */

vector<string> SearchFrequentItems(istringstream* stream, int k) {
	unordered_map<string, int> table;
	int n=0;

	string word;
	while(*stream >> word) {
		++table[word];
		++n;

		//We will maintain table of (k-1) items.
		//If size is k that means we found one not in the candidates and inserted it.
		//Make relative count equivalent by decrementing everyone.
		if(k == (int)table.size()) {
			auto it = table.begin();
			while(it != table.end()) {
				if(--(it->second) == 0) {
					table.erase(it++);
				} else {
					++it;
				}
			}
		}
	}

	//Reset the table
	for(auto& it: table) {
		it.second = 0;
	}

	//Reset the stream
	stream->clear();
	stream->seekg(0, ios::beg);

	//Read the stream again
	while(*stream >> word) {
		auto it = table.find(word);
		if(it != table.end()) {
			++(it->second);
		}
	}

	vector<string> result;
	//Select the words that occurs > n/k times
	for(auto it = table.begin() ; it != table.end() ; ++it) {
		if(it->second >= static_cast<double>(n)/k) {
			result.emplace_back(it->first);
		}
	}
	return result;
}

int main() {
	string str = "a a a a a a a a a b";
	istringstream ss(str);
	vector<string> res = SearchFrequentItems(&ss, 3);
	cout << "Stings are: " << endl;
	for(string& s: res) {
		cout << s << endl;
	}
	cout << "--END--" << endl;

	str = "ab ax ax a ab cc x  y ax ab a ax ";
	istringstream ss2(str);
	res = SearchFrequentItems(&ss2, 4);
	cout << "Stings are: " << endl;
	for(string& s: res) {
		cout << s << endl;
	}
	cout << "--END--" << endl;

}
