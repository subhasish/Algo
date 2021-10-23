/*
 * 00.HasPath.cpp
 *
 * Problem: Basic graph problem is to find if there exists a path between two vertices in a
 * 			directed graph.
 *
 *  Created on: Jun 18, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef unordered_set<string> USStr;
typedef unordered_map<string, USStr> GraphType;

struct Edge {
	string first, second;	// Indicate an edge from first to second
};

GraphType BuildGraph(const vector<Edge>& edges)
{
	GraphType graph;
	for(const Edge& e: edges) {
		graph[e.first].emplace(e.second);
	}
	return graph;
}

bool IsReachableDFS(GraphType& graph, const string& current, const string& dest, USStr* visited_ptr)
{
	USStr& visited = *visited_ptr;

	if(current == dest) {			// reached destination
		return true;
	}

	if(visited.find(current) != visited.end()) {  // already visited
		return false;
	}
	visited.emplace(current);		// mark as visited

	bool found_path = false;
	for(const string& other: graph[current]) {
		found_path |= IsReachableDFS(graph, other, dest, visited_ptr);
	}

	return found_path;
}

bool HasPath(const vector<Edge>& edges, const string& src, const string& dest)
{
	unordered_map<string, unordered_set<string>> graph = BuildGraph(edges);


	unique_ptr<USStr> visited(new USStr());
	return IsReachableDFS(graph, src, dest, visited.get());
}

int main()
{
	vector<Edge> edges = { {"1","2"}, {"2","3"}, {"3","4"}, {"2","5"}, {"4","6"} };

	cout << boolalpha;
	cout << HasPath(edges,"1","6") << endl;
	cout << HasPath(edges,"5","6") << endl;
}
