/*
 * 00.FloydWarshall.cpp
 *
 * Problem: Find shortest paths between all pair of vertices in a weighted graph with
 * 			positive or negative weights (but no negative cycle).
 *
 *  Created on: Jul 21, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			The idea behind Floyd-Warshall algorithm is to consider all possible paths
//			by considering all vertices as intermediate vertex for path between
//			every pair of vertices.
//
//			For k th iteration, we already have found shortest path for all pair of vertices
//			through 0..(k-1) vertices. So for any pair i,j we already found shortest path
//			from i to k and k to j (through 0..k-1). Now k th iteration would combine them
//
// Time complexity:
//			O(V^3)

// Input is the weight matrix between each pair of vertices
void FloydWarshall(vector<vector<double>>& G)
{
	for(size_t k=0 ; k<G.size() ; ++k) {			// Intermediate vertex
		for(size_t i=0; i<G.size() ; ++i) {			// Source vertex
			for(size_t j=0; j<G.size() ; ++j) {		// Destination vertex
				if(G[i][k] != numeric_limits<double>::max() &&
						G[k][j] != numeric_limits<double>::max() &&
						G[i][j] > G[i][k] + G[k][j]) {
					G[i][j] = G[i][k] + G[k][j];
				}
			}
		}
	}
}

struct Edge
{
	int u, v;
	double weight;
};

void PrintShortestDistance(vector<vector<double>>& G)
{
	for(size_t i=0 ; i<G.size() ; ++i) {
		for(size_t j=0 ; j<G.size() ; ++j) {
			cout << i << " - " << j << " is " << G[i][j] << endl;
		}
	}
}

void FindAllPairShortestPath(int N, vector<Edge>& edges)
{

	vector<vector<double>> G(N, vector<double>(N, numeric_limits<double>::max()));

	for(int i=0 ; i<N ; ++i) {
		G[i][i] = 0;
	}

	for(const Edge& e: edges) {
		G[e.u][e.v] = e.weight;
		G[e.v][e.u] = e.weight;		// Comment this line out for directed graph
	}

	FloydWarshall(G);

	PrintShortestDistance(G);
}

int main()
{
	int N = 4;
	Edge a {0,1,5}, b {1,2,3}, c {2,3,1}, d {0,3,10};
	vector<Edge> edges = {a,b,c,d};
	FindAllPairShortestPath(N, edges);
}
