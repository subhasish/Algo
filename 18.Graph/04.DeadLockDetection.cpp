/*
 * 04.DeadLockDetection.cpp
 *
 * Problem: In wait-for graph each vertex is a process and edge between process A and B means
 * 			process A is waiting on a resource currently locked by process B.
 * 			Given a wait-for graph detect whether a dead lock has occurred.
 *
 * 			This is same as detecting a cycle in a directed graph.
 *
 * 			Variant 1:
 * 			Solve for undirected graph
 *
 * 			Variant 2:
 * 			Take a connected graph and check if the graph remains connected if any one edge is
 * 			removed.
 *
 *  Created on: Jun 24, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			DFS search by path. Idea is to see if find another vertex already seen on the path.
//
//			For undirected, one search explores whole connected component. So if we find a
//			new node that is already explored then we found a cycle.
//
//			For directed, exploring a visited vertex is not always a cycle. Edge may go from one
//			connected component to another but not the other way round. Cycle is actually when
//			explore a node that is already explored but not finished.
//
//			DFS uses color to track this. Initially all vertices are white. When a vertex is
//			discovered for the first time it is colored gray. When DFS finishes exploring all
//			vertices under a vertex it is colored black.
//
//			When we discover a edge from a white/gray vertex to a gray vertex, we found a cycle.
//
// Time Complexity:
//			O(|V| + |E|): We iterate over all vertices and spend constant amount of time per edge.
//
// Variant 1:
//			No need to check black color. Undirected graph is always connected if edge exists.
//
// Variant 2:
//			Start with any node and do DFS. Do not explore through that edge and see if we can
//			still reach each vertices.

enum class Color { WHITE, GRAY, BLACK };

struct GraphVertex {
	Color color = Color::WHITE;
	vector<GraphVertex*> edges;				// edge list
};

bool HasCycleDFS(GraphVertex* curr)
{
	if(curr->color == Color::GRAY) {
		return true;
	}

	curr->color = Color::GRAY;				// Mark as discovered

	// Traverse all neighbors
	for(GraphVertex*& v: curr->edges) {
		if(v->color != Color::BLACK && HasCycleDFS(v)) {
			return true;
		}
	}

	curr->color = Color::BLACK;				// Mark as finished
	return false;
}

bool HasCycle (vector<GraphVertex*> graph) 	// adjacency list representations
{
	for(GraphVertex*& v: graph) {
		if(v->color == Color::WHITE && HasCycleDFS(v)) {
			return true;
		}
	}
	return false;
}

int main()
{
	GraphVertex a,b,c,d,e;
	a.edges.emplace_back(&b);
	a.edges.emplace_back(&c);
	b.edges.emplace_back(&c);
	c.edges.emplace_back(&d);
	d.edges.emplace_back(&e);
	e.edges.emplace_back(&b);

	cout << boolalpha;
	cout << HasCycle( {&a,&b,&c,&d,&e} ) << endl;
	cout << HasCycle( {&a,&b,&c,&d} ) << endl;
}
