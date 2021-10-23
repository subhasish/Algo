/*
 * 00.Prim.cpp
 *
 * Problem: Find a minimum spanning tree given a undirected graph
 *
 *  Created on: Jul 15, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Prim's algorithm grows the minimum spanning tree by starting at any vertex and then
//			adding edge with smallest weight that connects the tree with rest of the vertices
//			in the graph.
//
//			Conceptually Prim's and Dijkstra's algorithm are very similar. Prim's algorithm picks
//			a vertex nearest to the tree and Dijkstra's algorithm picks a vertex nearest to the
//			source.
//
//			Maintain Priority Queue of edges with at least one endpoint in T. As you add a vertex in T,
//			add all its neighbors in the Priority Queue. Mark vertex if it is in T

struct Vertex {
	struct VertexWithDistance {
		Vertex& vertex;
		double weight;
	};

	int id;
	double distance = numeric_limits<double>::max();	// Initialized as max distance from MST
	bool inMst = false;									// Initialized as not part of MST

	vector<VertexWithDistance> edges;
	Vertex* pred = nullptr;
};

struct CompVertex {
	bool operator()(const Vertex* a, const Vertex* b) {
		if(a->distance < b->distance) {
			return true;
		} else if(a->distance == b->distance &&
				  a->id < b->id) {
			return true;
		} else {
			return false;
		}
	}
};

struct Edge {
	int u, v;
	double weight;
};

typedef vector<Edge> Edges;
typedef vector<Vertex*> Graph;

Edges PrimMinSpanningTree(Graph graph)
{
	Edges mst;
	set<Vertex*, CompVertex> connected_node_set;

	Vertex* source = graph[0];
	source->distance = 0;
	connected_node_set.emplace(source);

	while(!connected_node_set.empty() && (mst.size() < graph.size() - 1))
	{
		Vertex* nearest = *connected_node_set.cbegin();
		connected_node_set.erase(connected_node_set.cbegin());

		if(nearest->inMst == false) {
			nearest->inMst = true;

			// If not source then add edge with predecessor in MST
			if(nearest->id != source->id) {
				Edge e = Edge{nearest->id, nearest->pred->id, nearest->distance};
				mst.emplace_back(e);
			}

			// Relax all vertices connected with this this vertex
			for(const Vertex::VertexWithDistance& e: nearest->edges) {

				// If the node is near to the tree through this vertex then update its distance
				if(!e.vertex.inMst && e.vertex.distance > e.weight) {
					connected_node_set.erase(&e.vertex);
					e.vertex.distance = e.weight;
					e.vertex.pred = nearest;
					connected_node_set.emplace(&e.vertex);
				}
			}
		}

	}
	return mst;
}

int main()
{
	Vertex a,b,c,d,e,f,g,h;

	a.id=0; b.id=1; c.id=2; d.id=3; e.id=4; f.id=5; g.id=6; h.id=7;

	a.edges.emplace_back(Vertex::VertexWithDistance{c,0.26});
	a.edges.emplace_back(Vertex::VertexWithDistance{e,0.38});
	a.edges.emplace_back(Vertex::VertexWithDistance{g,0.58});
	a.edges.emplace_back(Vertex::VertexWithDistance{h,0.16});
	b.edges.emplace_back(Vertex::VertexWithDistance{c,0.36});
	b.edges.emplace_back(Vertex::VertexWithDistance{d,0.29});
	b.edges.emplace_back(Vertex::VertexWithDistance{f,0.32});
	b.edges.emplace_back(Vertex::VertexWithDistance{h,0.19});
	c.edges.emplace_back(Vertex::VertexWithDistance{a,0.26});
	c.edges.emplace_back(Vertex::VertexWithDistance{b,0.36});
	c.edges.emplace_back(Vertex::VertexWithDistance{d,0.17});
	c.edges.emplace_back(Vertex::VertexWithDistance{g,0.40});
	c.edges.emplace_back(Vertex::VertexWithDistance{h,0.34});
	d.edges.emplace_back(Vertex::VertexWithDistance{b,0.29});
	d.edges.emplace_back(Vertex::VertexWithDistance{c,0.17});
	d.edges.emplace_back(Vertex::VertexWithDistance{g,0.52});
	e.edges.emplace_back(Vertex::VertexWithDistance{a,0.38});
	e.edges.emplace_back(Vertex::VertexWithDistance{f,0.35});
	e.edges.emplace_back(Vertex::VertexWithDistance{g,0.93});
	e.edges.emplace_back(Vertex::VertexWithDistance{h,0.37});
	f.edges.emplace_back(Vertex::VertexWithDistance{b,0.32});
	f.edges.emplace_back(Vertex::VertexWithDistance{e,0.35});
	f.edges.emplace_back(Vertex::VertexWithDistance{h,0.28});
	g.edges.emplace_back(Vertex::VertexWithDistance{a,0.58});
	g.edges.emplace_back(Vertex::VertexWithDistance{c,0.40});
	g.edges.emplace_back(Vertex::VertexWithDistance{d,0.52});
	g.edges.emplace_back(Vertex::VertexWithDistance{e,0.93});
	h.edges.emplace_back(Vertex::VertexWithDistance{a,0.16});
	h.edges.emplace_back(Vertex::VertexWithDistance{b,0.19});
	h.edges.emplace_back(Vertex::VertexWithDistance{c,0.34});
	h.edges.emplace_back(Vertex::VertexWithDistance{e,0.37});
	h.edges.emplace_back(Vertex::VertexWithDistance{f,0.28});

	Graph graph = {&a, &b, &c, &d, &e, &f, &g, &h};

	Edges mst = PrimMinSpanningTree(graph);

	cout << "Minimum spanning tree: " << endl;
	for(const Edge& e: mst) {
		cout << "(" << e.u << ", " << e.v << ") - " << e.weight << endl;
	}

	return 0;
}
