/*
 * 00.Basic.cpp
 *
 * Problem: Create a basic graph from scratch where edges have weights
 *
 *  Created on: Jun 18, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

struct Edge {
	int eitherId, otherId;
	double weight;

	Edge(int id1, int id2, double w) :eitherId(id1), otherId(id2), weight(w) {}

	// Equal function for hash table
	bool operator== (const Edge& that) const
	{
		return (otherId == that.otherId || otherId == that.eitherId) &&
				(eitherId == that.eitherId || eitherId == that.otherId);
	}

	// Less than function for ordering
	bool operator< (const Edge& that) const
	{
		return weight < that.weight;
	}
};

// Custom hash function to use STL. There are two ways: 1) Create a Hash Function class and pass that class as template parameter
// 2) Declare the specialization of hash<Edge> then we do not need to pass the template parameter
namespace std {

  template <>
  struct hash<Edge>
  {
    std::size_t operator()(const Edge& e) const
    {
    	size_t hash_code = 0;
    	hash_code ^= hash<int>()(e.eitherId);
    	hash_code ^= hash<int>()(e.otherId);
    	return hash_code;
    }
  };

}

class Graph
{
	int V;
	unordered_map<int, unordered_set<Edge>> adj;

public:

	Graph(int v) {
		V = v;
		for (int i = 0; i < V; ++i) {
			adj[i] = unordered_set<Edge>();
		}
	}

	void addEdge(int u, int v, double wt) {
		// Undirected: add both edges
		Edge e(u,v, wt);
		adj[u].emplace(e);
		adj[v].emplace(e);
	}

	unordered_set<Edge> edges(int v) {
		return adj[v];
	}

	void PrintEdge(int v) {
		cout << "Edges from " << v << ": ";
		for(const Edge& e: adj[v]) {
			cout << ((e.otherId != v) ? e.otherId : e.eitherId) << "(" << e.weight << "), ";
		}
		cout << endl;
	}
};



int main()
{
	Graph G(4);
	G.addEdge(0,1,4.3);
	G.addEdge(2,3,2.6);
	G.addEdge(0,2,6);
	G.addEdge(0,3,4.1);

	G.PrintEdge(0);
	G.PrintEdge(1);
	G.PrintEdge(2);
	G.PrintEdge(3);
}
