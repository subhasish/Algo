/*
 * HC.39.RoadNetwork.cpp
 *
 * Problem: Write a program that takes existing highway network (set of edges between cities)
 * 			and proposal for new highway sections (edges), and returns the proposed highway
 * 			section (new edge) which leads to most improvement in the total driving distance.
 * 			Total driving distance is measured as sum of shortest path between all pairs of
 * 			cities. Assume bidirectional traffic.
 *
 *  Created on: Jan 14, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * Solution:
 * 			Brute force solution would be add one edge to the original network and run shortest
 * 			path between all pairs, and do it for each new proposed edge.
 *
 * 			All pair shortest path problem can be solved in time O(n^3) time using Floyd-Warshall
 * 			algorithm. So total time complexity	is O(k * n^3) for k proposed edges.
 *
 * 			Now for the newly proposed edge (x,y) the distance for existing path between (a,b)
 * 			can only improve if it passes through the new edge. So the new shortest distance
 * 			between a and b can be min(D(a,b), D(a,x)+d(x,y)+D(y,b), D(a,y)+d(x,y)+D(x,b)).
 * 			So resultant time complexity for each new proposal id O(n^2). So total time is
 * 			O(n^3 + k * n^2)
 */

struct Edge {
	int x,y;
	double distance;
};

void FloydWarshall(vector<vector<double>>& G);

//Passed in existing network, proposal, and number of vertices
Edge FindBestProposal(const vector<Edge>& network, const vector<Edge>& proposals, int n) {
	//dist_matrix stores the shortest path distances between all pairs of vertices
	vector<vector<double>> dist_matrix(n, vector<double>(n, numeric_limits<double>::max()));
	for(int i=0; i<n ; ++i) {
		dist_matrix[i][i] = 0;
	}

	//build the distance matrix for existing highway network
	for(const Edge& e: network) {
		dist_matrix[e.x][e.y] = dist_matrix[e.y][e.x] = e.distance;
	}

	//Perform Floyd-Warshall to build shortest path between vertices
	FloydWarshall(dist_matrix);

	//Examine each proposal
	double best_saving = numeric_limits<double>::min();
	Edge best_edge = Edge {-1, -1, 0.0}; //default

	for(const Edge& p: proposals) {
		double proposed_saving = 0;
		for(int a=0; a<n ; ++a) {
			for(int b=0 ; b<n ; ++b) {
				double saving = dist_matrix[a][b] -
								min(dist_matrix[a][p.x] + p.distance + dist_matrix[p.y][b],
									dist_matrix[a][p.y] + p.distance + dist_matrix[p.x][b]);
				proposed_saving += (saving > 0) ? saving : 0;
			}
		}

		if(best_saving < proposed_saving) {
			best_saving = proposed_saving;
			best_edge = p;
		}
	}
	return best_edge;
}

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


int main() {
	vector<Edge> network =
	{
			Edge{0, 1, 2720},
			Edge{1, 2, 3842},
			Edge{2, 3, 113},
			Edge{3, 4, 2418},
			Edge{4, 5, 7213},
			Edge{3, 0, 4965},
			Edge{0, 5, 3848},
			Edge{1, 5, 9469},
			Edge{2, 5, 8578}
	};

	vector<Edge> proposal =
	{
			Edge{4, 0, 37},
			Edge{4, 2, 25},
			Edge{3, 1, 6}
	};

	Edge best_proposal = FindBestProposal(network, proposal, 6);	// Solution is {4, 0, 37}

	cout << "Best edge = " << best_proposal.x << " -> " << best_proposal.y << "; distance = " << best_proposal.distance << endl;
}
