/*
 * 00.Kruskal.cpp
 *
 * Problem: Find a minimum spanning tree given a undirected graph
 *
 *  Created on: Jul 15, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Kruskal's algorithm considers edges in the ascending order of weights.
//			If a new edge does not create a cycle then we add that to the spanning tree.
//			Union find like data structure can be used to detect cycle.
//			Use priority queue to get edges in ascending order.

struct Edge {
	int u, v;			// two vertices
	double weight;		// edge weight
};

typedef vector<Edge> Edges;

struct UnionFind {
	int *ids;
	int N;

	UnionFind(int n) {
		N = n;
		ids = new int[n];
		for(int i = 0; i< n ; ++i) {
			ids[i] = i;
		}
	}

	void Union(int a, int b) {
		if(a >= 0 && a < N && b >= 0 && b < N) {
			ids[root(a)] = ids[root(b)];					// Tricky!!!
		}
	}

	int root(int a) {
		int i = a;
		while(ids[i] != i) {
			ids[i] = ids[ids[i]];	//Reduce depth
			i = ids[i];				//Traverse up
		}
		return i;
	}

	bool Connected(int a, int b) {
		return root(a) == root(b);
	}
};

Edges KruskalMinSpanningTree(Edges& graph, int V)
{
	Edges mst;

	priority_queue<Edge, Edges, function<bool(Edge&, Edge&)>>
			min_heap([] (Edge& a, Edge& b) {return a.weight > b.weight; });

	for(const Edge& e: graph) {
		min_heap.emplace(e);
	}

	UnionFind uf(V);
	while(!min_heap.empty() && ((int)mst.size() < (V-1))) {
		Edge e = min_heap.top();
		min_heap.pop();

		if(!uf.Connected(e.u, e.v)) { // They are not connected, so cannot form a cycle
			mst.emplace_back(e);
			uf.Union(e.u, e.v);
		}
	}

	return mst;
}

int main()
{
	Edges graph;
	graph.emplace_back(Edge{0,7,0.16});		// included
	graph.emplace_back(Edge{2,3,0.17});		// included
	graph.emplace_back(Edge{1,7,0.19});		// included
	graph.emplace_back(Edge{0,2,0.26});		// included
	graph.emplace_back(Edge{5,7,0.28});		// included
	graph.emplace_back(Edge{1,3,0.29});
	graph.emplace_back(Edge{1,5,0.32});
	graph.emplace_back(Edge{2,7,0.34});
	graph.emplace_back(Edge{4,5,0.35});		// included
	graph.emplace_back(Edge{1,2,0.36});
	graph.emplace_back(Edge{4,7,0.37});
	graph.emplace_back(Edge{0,4,0.38});
	graph.emplace_back(Edge{6,2,0.40});		// included
	graph.emplace_back(Edge{3,6,0.52});
	graph.emplace_back(Edge{6,0,0.58});
	graph.emplace_back(Edge{6,4,0.93});

	Edges mst = KruskalMinSpanningTree(graph, 8);

	cout << "Minimum spanning tree: " << endl;
	for(const Edge& e: mst) {
		cout << "(" << e.u << ", " << e.v << ") - " << e.weight << endl;
	}

	return 0;
}
