/*
 * evaluate-division.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    string o_id;
    double weight;

    bool operator== (const Edge& that) const {
        return o_id == that.o_id;
    }
};

struct HashEdge {
    size_t operator() (const Edge& e) const {
        return hash<string>() (e.o_id);
    }
};

struct Vertex {
    string id;

    unordered_set<Edge, HashEdge> edges;
};


class Solution {
    double FindPathWeight(const unordered_map<string, Vertex>& graph, string source, string dest, bool& found, unordered_set<string>& visited)  {
        if(source == dest) {
            found = true;
            return 1.0;
        } else {
            visited.emplace(source);
            for(const Edge& e: graph.at(source).edges) {
                if(visited.find(e.o_id) == visited.end()) {
                	if(graph.find(e.o_id) != graph.end()) {
                		double res = FindPathWeight(graph, e.o_id, dest, found, visited);
                		if(found) {
                			return res * e.weight;
                		}
                	}
                }
            }
        }
        found = false;
        return -1.0;
    }

public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string, Vertex> graph;
        for(size_t i = 0 ; i < equations.size() ; ++i) {
            string first = equations[i].first;
            string second = equations[i].second;
            graph[first].edges.emplace(Edge{second, values[i]});
            graph[second].edges.emplace(Edge{first, 1.0 / values[i]});
        }

        vector<double> result;

        for(size_t i = 0 ; i < queries.size() ; ++i) {
            string source = queries[i].first;
            string dest = queries[i].second;
            if(graph.find(source) == graph.end() || graph.find(dest) == graph.end()) {
                result.emplace_back(-1.0);
            } else if(source == dest) {
                result.emplace_back(1.0);
        	} else {
                bool found = false;
                unordered_set<string> visited;
                double res = FindPathWeight(graph, source, dest, found, visited);
                if(found) {
                    result.emplace_back(res);
                } else {
                    result.emplace_back(-1.0);
                }
            }
        }
        return result;
    }
};

int main() {
	vector<pair<string, string>> equations = {make_pair("a", "b"), make_pair("b", "c")};
	vector<double> values = {2.0, 3.0};
	vector<pair<string, string>> queries = {make_pair("a","c"), make_pair("b","c"), make_pair("a","e"), make_pair("a","a"), make_pair("x","x")};

	Solution obj;
	vector<double> res = obj.calcEquation(equations, values, queries);

	for(double d: res) {
		cout << d << endl;
	}
}

