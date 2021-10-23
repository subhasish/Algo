/*
 * 09.ShortestPathWEdges.cpp
 *
 * Problem: Design an algorithm that takes a graph G = (V,E), directed or undirected, a nonnegative
 *          cost function on E, and vertices s and t, and outputs the shortest path from s to t
 *          that has minimum number of edges among the all shortest paths.
 *
 *  Created on: Jul 11, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//          Heuristically, we may think that adding small cost with edge will penalize path with most
//          edges. But it may penalize path with more edges such that a shortest path with more edges
//          may result in higher cost than an original path of higher cost and less number of edges.
//          Example, <1,1,1> and <4> being two path. Now adding penalty 1 to each edge cause wrong
//          result.
//
//          For shortest path with weighted edges, we know Dijkstra's algorithm. But it only
//          considers distance from source vertex in terms of sum of edge weights.
//
//          One important observation that new metric for distance is also monotonic similar to
//          nonnegative edge weights used in Dijkstra. So these two can be combined to form a new
//          metric that would also be monotonic.
//
//          If we make the scalar metric of distance from <sum of weights> to
//          <sum of weights, number of edges> and use it in comparison then Dijkstra's algorithm
//          can find the shortest path as well.
//
//          Regarding implementation of Dijkstra, we need to select the vertex with minimum distance
//          each time. So heap may be used. We also need to keep updating distance of the
//          vertices in the heap as we keep relaxing more edges. But STL heap unordered_set does
//          not support efficient updates. So it is more convenient to use BST set instead.

struct GraphVertex {

    struct Distance {
        int distance, min_num_edges;
    };

    // For unexplored vertices second parameter does not matter as comparison will fail with first one
    // and second parameter will be set with its predecessor + 1
    // Still it may be better to initialize it with max instead of 0
    Distance distance_with_fewest_edges = Distance{numeric_limits<int>::max(), 0};

    struct VertexWithDistance {   // For weighted edges
        GraphVertex& vertex;
        int distance;
    };
    vector<VertexWithDistance> edges;

    int id;
    const GraphVertex* pred = nullptr;           // predecessor in the shortest path
};


struct Comp {
    bool operator() (const GraphVertex* lhs, const GraphVertex* rhs) {
        return lhs->distance_with_fewest_edges.distance < rhs->distance_with_fewest_edges.distance
            || (lhs->distance_with_fewest_edges.distance == rhs->distance_with_fewest_edges.distance &&
                lhs->distance_with_fewest_edges.min_num_edges < rhs->distance_with_fewest_edges.min_num_edges)
        	|| (lhs->id < rhs->id); // This is needed so that set adds two different vertices with same distance
    }
};

void OutputShortestPath(const GraphVertex* v)
{
    if(v != nullptr) {
        OutputShortestPath(v->pred);        // NICE: nice way to get the path in proper order
        cout << v->id << " -> ";
    }
}

void DijkstraShortestPath(GraphVertex* s, GraphVertex* t)
{
    // Next set of vertices reachable from the explored tree. We will choose vertex of minimum
    // distance from this collection.
    set<GraphVertex*, Comp> node_set;  //BST instead of heap

    // Initialize the source
    s->distance_with_fewest_edges = {0,0};
    node_set.emplace(s);

    while(!node_set.empty()) {
        // Extract vertex of minimum distance from the set
        GraphVertex* u = *node_set.cbegin();
        if(u->id == t->id) {
            break;
        }

        // Remove the nearest from the set
        node_set.erase(node_set.cbegin());

        // Add all the neighbors of the newly explored nodes to the set
        for(const GraphVertex::VertexWithDistance& v: u->edges) {
            int v_distance = u->distance_with_fewest_edges.distance + v.distance;
            int v_num_edges = u->distance_with_fewest_edges.min_num_edges + 1;

            if(v_distance < v.vertex.distance_with_fewest_edges.distance ||
                    (v_distance == v.vertex.distance_with_fewest_edges.distance &&
                     v_num_edges < v.vertex.distance_with_fewest_edges.min_num_edges))
            {
                node_set.erase(&v.vertex);
                v.vertex.pred = u;
                v.vertex.distance_with_fewest_edges = {v_distance, v_num_edges};
                node_set.emplace(&v.vertex);
            }
        }
    }

    cout << "Shortest path: ";
    OutputShortestPath(t);
    cout << endl;
}

int main() {

    GraphVertex a,b,c,d;

    a.id=1; b.id=2; c.id=3; d.id=4;

    a.edges.emplace_back(GraphVertex::VertexWithDistance{b,1});
    a.edges.emplace_back(GraphVertex::VertexWithDistance{c,1});
    c.edges.emplace_back(GraphVertex::VertexWithDistance{d,2});


    DijkstraShortestPath(&a, &d);
}
