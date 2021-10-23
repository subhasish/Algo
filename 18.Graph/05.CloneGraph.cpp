/*
 * 05.CloneGraph.cpp
 *
 * Problem: Consider a directed graph where vertex stores an label and reference of vertices
 * 			it has edges to. Design an algorithm that takes a reference to a vertex u and
 * 			creates a copy of the graph of the vertices that are reachable from vertex u.
 *
 *  Created on: Jun 24, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Say u has edges to v and w, also v has edge to w. Main challenge is to have
//			copy of v to have an edge to copy of w.
//
//			For this to work we need to maintain a map from original vertex to its copy.
//			So when we see and edge from x to y, we take their copy from the map and make
//			an edge between them.
//
//			Any traversal BFS or DFS should work. We will do BSF here.
//
//			The same map can be used to mark a node as visited

struct GraphVertex {
	string label;
	vector<GraphVertex*> edges;
};

GraphVertex* CloneGraph(GraphVertex* G)
{
	if(!G) {
		return nullptr;
	}

	unordered_map<GraphVertex*, GraphVertex*> vertex_map;	//In case two share same label
	queue<GraphVertex*> Q;

	Q.emplace(G);
	vertex_map.emplace(G, new GraphVertex{{G->label}});

	while(!Q.empty()) {
		GraphVertex* curr = Q.front();
		Q.pop();

		GraphVertex* copy = vertex_map[curr];

		// Traverse all nodes reachable from this node
		for(GraphVertex*& node: curr->edges) {
			if(vertex_map.find(node) == vertex_map.end()) {
				// That means we reached the vertex for the first time. Do two things:
				// 1) Create its copy, 2) Add it in queue to be explored
				vertex_map.emplace(node, new GraphVertex{{node->label}});
				Q.emplace(node);
			}

			// Add the edge in the copy
			copy->edges.emplace_back(vertex_map[node]);
		}
	}

	return vertex_map[G];
}

void PrintEdges(GraphVertex* V)
{
	cout << V->label << ": ";
	for(GraphVertex*& node: V->edges) {
		cout << node->label << ", ";
	}
	cout << endl;
}

void PrintGraph(GraphVertex* G) {
	unordered_set<GraphVertex*> visited;
	queue<GraphVertex*> Q;
	Q.emplace(G);
	visited.emplace(G);

	while(!Q.empty()) {
		GraphVertex* curr = Q.front();
		Q.pop();

		//visited.emplace(curr);	// Marking here visited can cause multiple entries in the queue

		PrintEdges(curr);

		for(GraphVertex*& node: curr->edges) {
			if(visited.find(node) == visited.end()) {
				Q.emplace(node);
				visited.emplace(node);
			}
		}
	}
	cout << endl;
}

int main()
{
	GraphVertex a,b,c;
	a.label = "A";
	b.label = "B";
	c.label = "C";

	a.edges.emplace_back(&b);
	a.edges.emplace_back(&c);
	b.edges.emplace_back(&c);

	cout << "Original:" << endl;
	PrintGraph(&a);

	GraphVertex* a_copy = CloneGraph(&a);
	cout << "Clone:" << endl;
	PrintGraph(a_copy);
}
