/*
 * 00.BellmanFord.cpp
 *
 * Problem: Find shortest path in a graph where edge can have negative weights, but there is no
 * 			negative cycle.
 *
 * 			In case there is a negative cycle, report that negative cycle exists.
 *
 *  Created on: Jul 15, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Bellman-Ford is the algorithm to find shortest path in graph with negative edge
//			weight but no negative cycle.
//
//			Bellman-Ford is basically relaxing each edge V times.
//			After i rounds of relaxing all the edges, found shortest path containing at most i edges.
//
// Negative Cycle:
//			No shortest path can exists if there is a negative cycle. Then we could loop
//			through the negative cycle infinite number of times to decrease the path cost infinitely.
//
//			If distance to any vertex v is updated in round |V|, then there exists a negative cycle.
//			And we can trace back the edge to the vertex to find the cycle.

struct Vertex
{
	struct VertexWithEdge {
		Vertex& vertex;
		int weight;
	};

	int id;
	vector<VertexWithEdge> edges;

	int distance = numeric_limits<int>::max();
	Vertex* pred = nullptr;
};

void BellmanFord(vector<Vertex*> Graph, Vertex* s, bool& hasNegativeCycle)
{
	hasNegativeCycle = false;
	s->distance = 0;

	for(int i=0 ; i< (int)Graph.size() ; ++i) {				// V times
		for(int j=0 ; j< (int)Graph.size() ; ++j) {			// Relax each edge
			for(const Vertex::VertexWithEdge& e: Graph[j]->edges) {
				if(e.vertex.distance > Graph[j]->distance + e.weight) {
					e.vertex.distance = Graph[j]->distance + e.weight;
					e.vertex.pred = Graph[j];

					//Check negative cycle: If weight change in |V|th iteration
					if(i == ((int)Graph.size() - 1)) {
						hasNegativeCycle = true;
					}
				}
			}
		}
	}
}


int main()
{
	Vertex a,b,c,d,e;

	a.id = 1; b.id = 2; c.id = 3; d.id = 4; e.id = 5;

	a.edges.emplace_back(Vertex::VertexWithEdge{b,-1});
	a.edges.emplace_back(Vertex::VertexWithEdge{c,4});
	b.edges.emplace_back(Vertex::VertexWithEdge{c,3});
	b.edges.emplace_back(Vertex::VertexWithEdge{d,2});
	b.edges.emplace_back(Vertex::VertexWithEdge{e,2});
	d.edges.emplace_back(Vertex::VertexWithEdge{b,1});
	d.edges.emplace_back(Vertex::VertexWithEdge{c,5});
	e.edges.emplace_back(Vertex::VertexWithEdge{d,-3});

	bool hasNegativeCycle;
	vector<Vertex*> graph = {&a, &b, &c, &d, &e};
	BellmanFord(graph, &a, hasNegativeCycle);

	cout << "Distance to a = " << a.distance << endl;
	cout << "Distance to b = " << b.distance << endl;
	cout << "Distance to c = " << c.distance << endl;
	cout << "Distance to d = " << d.distance << endl;
	cout << "Distance to e = " << e.distance << endl;

	cout << boolalpha;
	cout << "Has negative cycle: " << hasNegativeCycle << endl;

	//Negative cycle test
	cout << "Negative cycle test:" << endl;
	c.edges.emplace_back(Vertex::VertexWithEdge{e,-3});

	BellmanFord(graph, &a, hasNegativeCycle);

	cout << "Distance to a = " << a.distance << endl;
	cout << "Distance to b = " << b.distance << endl;
	cout << "Distance to c = " << c.distance << endl;
	cout << "Distance to d = " << d.distance << endl;
	cout << "Distance to e = " << e.distance << endl;

	cout << boolalpha;
	cout << "Has negative cycle: " << hasNegativeCycle << endl;

}
