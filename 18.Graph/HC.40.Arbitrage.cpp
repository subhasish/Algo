/*
 * HC.40.Arbitrage.cpp
 *
 * Problem: Suppose you are given a set of exchange rates among currencies and you want to determine
 * 			if an arbitrage is possible, i.e., there is a way by which you can start with one unit of
 * 			some currency C and perform a series of exchanges which results in having more than one
 * 			unit of C.
 *
 *  Created on: Jan 14, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * Solution:
 *			The arbitrage involves a cycle. So lets try to model the problem in the form of graph.
 *			The currencies can be vertices and exchange rate can be edge weights.
 *
 *			But edge weights are additive in a path but the normal exchange rate is multiplicative.
 *
 *			This can be solved by making log of exchange rate as edge weights. We can do this
 *			because log(a * b) = log a + log b. So the path distance will represent the log of
 *			the final exchanged value.
 *			Specifically if path weights from a->b->c is log x + log y, then
 *			that means when we convert unit amount of currency a to currency b and then to
 *			currency c, then path weight is actually log of final amount of a. That is final
 *			amount of a is log inverse(log x + log y) = log inverse (log (x*y)) = x*y.
 *
 *			Now coming back to the problem, we need to detect the product of cycle of
 *			exchange is greater than 1. That is from example x*y > 1. So log (x*y) will be positive.
 *			So log of product has to be positive.
 *			So finally problem is to find a cycle whose path weight is positive.
 *
 *			This would require finding all distinct cycles in the graph and checking their weights.
 *			Finding all "simple" (no repetition) cycle is NP complete. This is because if it were
 *			polynomial then we can find maximum length cycle also in polynomial time
 *			and then determine if graph has a Hamiltonian path in polynomial time.
 *
 *			But finding whether the graph has a negative cycle can be done using Bellman-Ford.
 *			So instead of making weight as (log x) if make it (-log x) then if the product of
 *			the exchange rates are greater than 1 then sum of the weights will be negative.
 *
 *			Bellman-Ford is basically relaxing each edge V times. So time O(|V||E|).
 *			If distance to any vertex v is updated in round |V|, then there exists a negative cycle.
 *			And we can trace back the edge to the vertex to find the cycle.
 *
 *			Can perform little better by checking if at one iteration any distance got updated.
 *
 *			Usually finding a negative weight cycle is done by adding a dummy vertex s with weight 0
 *			edge to each vertex in the given graph and running Bellman-Ford single source
 *			shortest path algorithm from s. However for arbitrage problem the graph is complete.
 *			So we can run from any source vertex.
 *
 *			For arbitrage the graph is complete so we can use the adjacency matrix representation
 *			instead of adjacency list as done is 18.Graph/00.BellmanFord.cpp
 *
 */

bool BellmanFord(const vector<vector<double>>& G, int source);

bool IsArbitragePossible(vector<vector<double>>& G) {
	//Transform each edge edge weight
	for(vector<double>& edge_list: G) {
		for(double& edge_weight: edge_list) {
			edge_weight = -log10(edge_weight);
		}
	}

	//Use Bellman-Ford to detect negative cycle
	return BellmanFord(G, 0);
}

// Returns if the graph G has a negative cycle
bool BellmanFord(const vector<vector<double>>& G, int source) {
	vector<double> dis_from_source(G.size(), numeric_limits<double>::max());
	dis_from_source[source] = 0;

	for(size_t times = 0 ; times < G.size() ; ++times) {	// Relax |V| times
		bool have_update = false;
		for(size_t i = 0 ; i < G.size() ; ++i) {
			for(size_t j = 0 ; j < G[i].size() ; ++j) {
				if(dis_from_source[i] != numeric_limits<double>::max() &&
						dis_from_source[j] > dis_from_source[i] + G[i][j]) {
					have_update = true;
					dis_from_source[j] = dis_from_source[i] + G[i][j];
				}
			}
		}
		// No update in this iteration means no further update and no negative cycle
		if(have_update == false) {
			return false;
		}
	}

	//We could have checked the negative cycle in the previous loop at |V|th iteration
	//Or do another iteration to see if any further update
	for(size_t i = 0 ; i < G.size() ; ++i) {
		for(size_t j = 0 ; j < G[i].size() ; ++j) {
			if(dis_from_source[i] != numeric_limits<double>::max() &&
					dis_from_source[j] > dis_from_source[i] + G[i][j]) {
				return true;
			}
		}
	}
	return false;
}


int main() {
	vector<vector<double>> G =
	{
			{1, 0.8123, 0.6404, 78.125, 0.9784, 0.9924, 0.9465},
			{1.2275, 1, 0.7860, 96.55, 1.2010, 1.2182, 1.1616},
			{1.1516, 1.2724, 1, 122.83, 1.5280, 1.5498, 1.4778},
			{0.0128, 0.0104, 0.0081, 1, 1.2442, 0.0126, 0.0120},
			{1.0219, 0.8327, 0.6546, 80.39, 1, 1.0142, 0.9672},
			{1.0076, 0.8206, 0.6453, 79.26, 0.9859, 1, 0.9535},
			{1.0567, 0.8609, 0.6767, 83.12, 1.0339, 1.0487, 1}
	};

	cout << "Arbitrage possible: " << IsArbitragePossible(G) << endl;

	vector<vector<double>> G1 =
	{
			{1, 0.8},
			{0.9, 1}
	};

	cout << "Arbitrage possible: " << IsArbitragePossible(G1) << endl;
}
