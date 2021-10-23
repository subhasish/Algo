/*
 * is-graph-bipartite.cpp
 *
 *  Created on: May 4, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool DFS(const vector<vector<int>>& graph, vector<int>& color, int start) {
        int c = color[start];
        int cc = (c==1) ? 2 : 1;
        for(int j = 0 ; j < (int)graph[start].size() ; ++j) {
            int v = graph[start][j];
            if(color[v] == c) {
                return false;
            } else {
                if(color[v] == 0) {
                    color[v] = cc;
                    if(!DFS(graph, color, v)) {
                        return false;
                    }
                } else {
                    //already done
                }
            }
        }
        return true;
    }
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> color(graph.size(),0);
        //We will color it in 1 or 2
        for(int i=0 ; i< (int)graph.size() ; ++i) {
            if(color[i] == 0) {
            	color[i] = 1;
                if(!DFS(graph, color, i)) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
	vector<vector<int>> graph;
	graph = {{1,3},{0,2},{1,3},{0,2}};

	Solution obj;

	cout << obj.isBipartite(graph) << endl;
}

