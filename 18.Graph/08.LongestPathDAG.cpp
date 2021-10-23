/*
 * 08.LongestPathDAG.cpp
 *
 * Problem: Given a DAG find the longest path in the graph (DAG)
 *
 * 			The real life problem given in the book is that two teams can take photo together
 * 			if all the members of one team can be placed in front of members of another team
 * 			without hiding anyone.
 * 			Now given a set of teams find the largest number of teams that can be photographed
 * 			together.
 *
 *  Created on: Jul 9, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Shortest or longest path in DAG can be easily found by relaxing edges in the
//			topological sort order. This is because no edge pointing to a vertex will be relaxed
//			after the vertex is relaxed.
//
//			For longest path instead of a shortest path either we need to negate all edge weights
//			and find shortest path or relax all edges to maximize the distance.


struct Vertex {
	vector<Vertex*> edges;
	int max_distance = 0;	// potentially can be re-used instead of extra visited flag
	bool visited = false;
};

typedef stack<Vertex*> SV;

SV BuildTopologicalOrdering(vector<Vertex*>& G);
int FindLongestPathDAG(SV& vertex_order);
void TopologicalDFS(Vertex* v, SV* vertex_order);

int FindLongestDAGPathLength(vector<Vertex*>& Graph)
{
	SV vertex_order(BuildTopologicalOrdering(Graph));
	return FindLongestPathDAG(vertex_order);
}

SV BuildTopologicalOrdering(vector<Vertex*>& Graph)
{
	SV vertex_order;
	for(Vertex*& g: Graph) {
		if(!g->visited) {
			TopologicalDFS(g, &vertex_order);
		}
	}
	return vertex_order;
}

int FindLongestPathDAG(SV& vertex_order)
{
	int max_distance = 0;

	while(!vertex_order.empty())
	{
		Vertex*& v = vertex_order.top();
		vertex_order.pop();

		max_distance = max(max_distance, v->max_distance);
		for(Vertex*& neighbor: v->edges) {
			neighbor->max_distance = max(neighbor->max_distance, v->max_distance + 1);
		}
	}

	return max_distance;
}

void TopologicalDFS(Vertex* v, SV* vertex_order) {
	v->visited = true;
	for(Vertex*& neighbor: v->edges) {
		if(!neighbor->visited) {
			TopologicalDFS(neighbor, vertex_order);
		}
	}
	vertex_order->emplace(v);
}


int main()
{
	Vertex a,b,c,d,e,f,g,h;

	a.edges.emplace_back(&b);
	e.edges.emplace_back(&f);
	f.edges.emplace_back(&c);
	c.edges.emplace_back(&d);
	g.edges.emplace_back(&c);
	c.edges.emplace_back(&h);

	vector<Vertex*> graph = {&a, &b, &c, &d, &e, &f, &g, &h};

	cout << "Longest distance in the DAG: " << FindLongestDAGPathLength(graph) << endl;

	return 0;
}
