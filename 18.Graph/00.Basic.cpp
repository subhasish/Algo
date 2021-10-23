/*
 * 00.Basic.cpp
 *
 * Problem: Create a basic graph from scratch
 *
 *  Created on: Jun 18, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;


class Graph
{
	int V;
	unordered_map<int, unordered_set<int>> adj;

public:

	Graph(int v) {
		V = v;
		for (int i = 0; i < V; ++i) {
			adj[i] = unordered_set<int>();
		}
	}

	void addEdge(int v, int w) {
		// Undirected: add both edges
		adj[v].emplace(w);
		adj[w].emplace(v);
	}

	unordered_set<int> edges(int v) {
		return adj[v];
	}

	void PrintEdge(int v) {
		cout << "Edges from " << v << ": ";
		for(int w: adj[v]) {
			cout << w << ", ";
		}
		cout << endl;
	}
};



int main()
{
	Graph G(4);
	G.addEdge(0,1);
	G.addEdge(2,3);
	G.addEdge(0,2);
	G.addEdge(0,3);

	G.PrintEdge(0);
	G.PrintEdge(1);
	G.PrintEdge(2);
	G.PrintEdge(3);
}
