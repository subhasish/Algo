/*
 * alien-dictionary.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;


class Solution {

    void DFS(char curr, unordered_map<char, unordered_set<char>> G, vector<char>& topo,
             unordered_map<char, int>& visited, bool& is_cycle) {


        if(visited[curr] != 0) {
        	if(visited[curr] == 1) {
        		is_cycle = true;
        	}
            return;
        }

        visited[curr] = 1;
        if(G.find(curr) != G.end()) {   // Make sure curr is in G before trying to access it
                                        // otherwise it will be a insert and invalidate
                                        // pre-existing iterators
            for(const char& ch: G[curr]) {
                if(visited[ch] != 2) {
                    DFS(ch, G, topo, visited, is_cycle);
                }
            }
        }
        visited[curr] = 2;

        topo.emplace_back(curr);
    }

public:
    string alienOrder(vector<string>& words) {
        //Create DAG from the letters and then do topological order
        //Some letters may not have constraint

        unordered_map<char, unordered_set<char>> G;
        unordered_set<char> alpha;

        for(size_t i = 0 ; i < words.size() ; ++i) {

            //create alphabet
            for(char& ch: words[i]) {
                alpha.emplace(ch);
            }

            if(i+1 == words.size()) {
                break;
            }

            // create the precedence graph
            size_t j = 0;
            while( j < words[i].size() && j < words[i+1].size() && words[i][j] == words[i+1][j]) {
                ++j;
            }
            if(j < words[i].size() && j < words[i+1].size()) {
                G[words[i][j]].emplace(words[i+1][j]);
            }
        }

        vector<char> topo;
        unordered_map<char, int> visited;   //0 -> unvisited, 1 -> expolring, 2 -> done
        bool is_cycle = false;


        for(auto it : G) {
        	if(visited[it.first] != 2) {
        		DFS(it.first, G, topo, visited, is_cycle);
        	}
        }

        if(is_cycle) {
        	return "";
        }

        reverse(topo.begin(), topo.end());
        for(char& ch: topo) {
            alpha.erase(ch);
        }
        for(const char& ch: alpha) {
            topo.emplace_back(ch);
        }

        string ret = "";
        ret.reserve(30);
        for(char& ch: topo) {
        	ret += ch;
        }
        return ret;
    }
};


int main() {
	Solution obj;

	vector<string> VS = { "aac","aabb","aaba" };

	cout << obj.alienOrder(VS) << endl;	//cba

	VS = {"z","x","z"};
	cout << obj.alienOrder(VS) << endl;
}
