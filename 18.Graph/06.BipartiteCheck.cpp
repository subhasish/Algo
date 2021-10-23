/*
 * 06.BipartiteCheck.cpp
 *
 * Problem: Given an undirected graph determine whether it is a bipartite graph or not.
 *
 * 			Bipartite graph whose vertices can be divided into two sets where each edge
 * 			only goes from one set to another.
 *
 *  Created on: Jun 24, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			While traversing we need to make sure parent and child are not part of same set.
//			Need an auxiliary data in the vertex to track which set it belongs, say color.
//
//			Another way could be using BFS property on undirected graph. In BFS on undirected graph
//			any new edge can only be from vertex at distance d to a vertex at distance (d+1)
//			or from a vertex at distance d to another vertex at distance d.
//
//			If we use the second property then the seconds case would detect that graph is not a
//			bipartite graph.

enum class Color { WHITE, RED, BLACK }; // WHITE means unvisited, RED and BLACK are two sets

struct GraphVertex{
	Color color = Color::WHITE;
	vector<GraphVertex*> edges;
};

bool IsBipartiteBFS(GraphVertex* G) {
	queue<GraphVertex*> Q;
	Q.emplace(G);

	while(!Q.empty()) {
		GraphVertex* curr = Q.front();
		Q.pop();
		Color otherColor = (curr->color == Color::RED) ? Color::BLACK : Color::RED;

		for(GraphVertex*& next: curr->edges) {
			if(next->color == curr->color) {
				return false;
			}
			if(next->color == Color::WHITE) {
				next->color = otherColor;
				Q.emplace(next);
			}
		}
	}
	return true;
}

bool IsBipartitie(vector<GraphVertex*> graph)
{
	for(GraphVertex*& v: graph) {
		if(v->color == Color::WHITE) {
			v->color = Color::RED;
			if(!IsBipartiteBFS(v)) {
				return false;
			}
		}
	}
	return true;
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

	cout << IsBipartitie( {&a,&b,&c,&d,&e} ) << endl;


	GraphVertex f;
	e.edges.clear();
	e.edges.emplace_back(&f);
	f.edges.emplace_back(&b);
	cout << IsBipartitie( {&a,&b,&c,&d,&e,&f} ) << endl;
}
