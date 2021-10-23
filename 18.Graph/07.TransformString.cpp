/*
 * 07.TransformString.cpp
 *
 * Problem: Given a dictionary D and two strings s and t, write a program to determine if s
 * 			produces t through a series of transforms from the dictionary D.
 * 			A string can be transformed to another string only if they match in length and
 * 			has difference in only one character.
 *
 * 			Also find the shortest path of transformation from s to t. If there is one return the
 * 			length of the shortest path, otherwise retuen -1.
 *
 *			Assume all characters are in lower case.
 *
 *  Created on: Jun 25, 2018
 *      Author: subha
 */


#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Shortest transformation sounds like BFS.
//
//			It could be expensive to build the whole graph from dictionary if do not
//			use it too many times. Even if we build graph we would need to have mapping
//			words to their corresponding vertex in the graph.
//
//			In contrast it would be easy to not explicitly create the graph and check the
//			string's existence in the dictionary to detect whether there is an edge.
//
//			If we could alter the dictionary then we can mark a vertex as visited by
//			removing it from the dictionary.
//
// Time complexity:
//			If the number of words in the dictionary is d then worst case number of edges
//			is O(d^2).
//			If string length n is less than d then number of edges out of a vertex is n, and
//			total time is O(nd)

struct StringWithDistance{
	string candidate_string;
	int distance;
};

int TransformString(unordered_set<string>& D, const string& s, const string& t)
{
	queue<StringWithDistance> Q;
	D.erase(s);		// mark s as visited
	Q.emplace(StringWithDistance{s,0});

	while(!Q.empty()) {
		StringWithDistance curr = Q.front();
		Q.pop();

		if(curr.candidate_string == t) {
			return curr.distance;
		}

		// Try all possible transformation of curr.candidate_string
		string str = curr.candidate_string;
		for(int i=0 ; i< (int)str.size() ; ++i) {
			for(int c=0; c<26 ; ++c) {
				str[i] = 'a'+c;
				if(D.find(str) != D.end()) {
					D.erase(str);
					Q.emplace(StringWithDistance{str, curr.distance+1});
				}
			}
			str[i] = curr.candidate_string[i]; // Reverts the change
		}
	}
	return -1;
}

int main()
{
	unordered_set<string> D = {"abc", "ddd", "add", "adc","ant","adt","bad"};

	cout << TransformString(D, "add", "ant") << endl;
	cout << TransformString(D, "add", "bad") << endl;
}
