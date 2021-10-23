/*
 * 00.FordFulkerson.cpp
 *
 * Problem: Max-Flow problem.
 * 			We are given an edge weighted directed graph with a source and destination vertex,
 * 			where the edge weights represents capacity of the edge. There can be flow from
 * 			source to destination such that at each edge flow is less than the capacity of
 * 			the edge and at each vertex incoming flow equals outgoing flow.
 *
 * 			Find the maximum possible flow that can be sent from source to destination.
 *
 *
 *  Created on: Jul 17, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			This is max-flow problem, also known as its dual min-cut problem. Maximum value of
//			flow is equals the minimum capacity of all possible cuts where source and destination
//			appear in two different sides of the cut.
//
//			Ford-Fulkerson algorithm can be used to solve this problem. Each time it tries to find
//			an augmenting path from source to destination and increases flow along that path.
//
//			Augmenting path can have both forward and backward edges. So the search need to be done
//			on undirected version of the graph. Reason for having backward edge is following:
//				Suppose v two outgoing edge u and w. Edge v to w is full but not v to u.
//				Now there is another edge to w from other vertex say x with some capacity.
//				In this situation existing flow can be rearranged to flow from v to u,
//				and new flow from x to w can be accommodated as previous flow was doing.
//
//			To simplify this we can think of one directed edge from u to v with capacity c and flow f
//			as two edges: one from u to v with residual capacity c-f and one edge from v to u with
//			residual capacity f.
//
//			This will result in finding an augmenting path in original network getting reduced to
//			finding a directed path in residual network.
//
// Time complexity:
//			The time complexity very much depends on how we find the augmenting path. For BFS/DFS
//			it would take O(V+E). For integer capacities, each iteration will increase flow by
//			at least 1. So if C is the maximum capacity in the network then worst case time
//			complexity will be O(C * (V + E))


struct FlowEdge {
	int from, to;		// Vertex IDs of from and to vertex for the directed edge
	double capacity;	// Capacity of the edge
	double flow;		// Flow in the edge

	FlowEdge(int f, int t, double c) : from(f), to(t), capacity(c), flow(0) {}

	// Get the other vertex from the edge**
	int other(int vertex)
	{
		if     (vertex == from) return to;
		else if(vertex == to)   return from;
		else throw new invalid_argument("Invalid vertex passed in.");
	}

	// Residual capacity of the edge TO the given vertex
	// NOTE**: This is TO the vertex and not from the vertex
	double residualCapacityTo(int vertex)
	{
		if     (vertex == from) return flow;
		else if(vertex == to)   return capacity - flow;
		else throw new invalid_argument("Invalid vertex passed in.");
	}

	// Add residual flow to the edge coming from the vertex
	// It will decrease the residual capacity from that vertex and increase it from other vertex
	void addResidualFlowTo(int vertex, double delta)
	{
		if     (vertex == from) flow -= delta;
		else if(vertex == to)   flow += delta;
		else throw new invalid_argument("Invalid vertex passed in.");

		if(flow>capacity) throw new runtime_error("Flow larger than capacity!");
		if(flow<0) throw new runtime_error("Flow less than 0!");
	}
};

struct FlowVertex
{
	int id;
	vector<FlowEdge*> edges;

	FlowVertex(int i) :id(i) {}
};

struct FlowNetwork
{
	int V;									// Vertex count
	vector<FlowVertex*> graph;				// Adjacency list

	FlowNetwork (int v)
	{
		this->V = v;
		for(int i=0 ; i<v ; ++i) {
			graph.emplace_back(new FlowVertex(i));
		}
	}

	void addEdge(int from, int to, double capacity)
	{
		FlowEdge* e = new FlowEdge(from, to, capacity);

		graph[from]->edges.emplace_back(e);
		graph[to]->edges.emplace_back(e);
	}
};

struct FordFulkerson
{
	bool      *marked = nullptr;		// marked[v] is true if s->v is a path in residual network
	FlowEdge **edgeTo = nullptr;		// last

	double flow;

	FordFulkerson(FlowNetwork& network, int source, int destination)
	{
		flow = 0;
		int iteration = 0;
		while(HasAugmentingPath(network, source, destination)) {
			double bottleNeck = numeric_limits<double>::max();

			// Compute bottleneck capacity
			for(int v=destination ; v != source ; v = edgeTo[v]->other(v)) {
				bottleNeck = min(bottleNeck, edgeTo[v]->residualCapacityTo(v));
			}

			cout << "Augmenting path in iteration " << ++iteration << ":  ";
			PrintAugmentingPath(source,destination);
			cout << endl;

			cout << "Bottleneck is "  << bottleNeck << endl;

			// Augment flow with bottleneck value
			for(int v=destination ; v != source ; v = edgeTo[v]->other(v)) {
				edgeTo[v]->addResidualFlowTo(v, bottleNeck);
			}

			flow += bottleNeck;

			delete [] edgeTo;
			delete [] marked;
			marked = nullptr;
			edgeTo = nullptr;
		}
	}

	bool HasAugmentingPath(FlowNetwork& network, int source, int destination)
	{
		edgeTo = new FlowEdge*[network.V]();
		marked = new bool[network.V]();

		// BFS in residual graph to find a (augmenting) path
		queue<int> Q;
		Q.emplace(source);

		marked[source] = true;
		while(!Q.empty()) {
			int v = Q.front();
			Q.pop();

			for(FlowEdge*& e: network.graph[v]->edges) {
				int w = e->other(v);

				// Check if there is a path from source to w in residual network
				if(e->residualCapacityTo(w) > 0 && !marked[w]) {
					edgeTo[w] = e;
					marked[w] = true;
					Q.push(w);
				}
			}
		}
		return marked[destination];
	}

	void PrintAugmentingPath(int source, int v)
	{
		if(source != v) {
			PrintAugmentingPath(source, edgeTo[v]->other(v));
		}
		cout << v << " -> ";
	}
};

int main()
{
	FlowNetwork network(6);
	network.addEdge(0, 1, 2.0);
	network.addEdge(0, 2, 3.0);
	network.addEdge(1, 3, 3.0);
	network.addEdge(1, 4, 1.0);
	network.addEdge(2, 3, 1.0);
	network.addEdge(2, 4, 1.0);
	network.addEdge(3, 5, 2.0);
	network.addEdge(4, 5, 3.0);

	FordFulkerson maxflow(network, 0, 5);

	cout << "Max flow = " << maxflow.flow << endl; //Should be 4 for this graph
}
