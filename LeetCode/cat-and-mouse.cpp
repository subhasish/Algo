/*
 * cat-and-mouse.cpp
 *
 *  Created on: Feb 11, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

struct State {
	int mouse, cat;
	bool isMsMove;

	State() : mouse(1), cat(2), isMsMove(true) {}
	State(int M, int C, bool isM) : mouse(M), cat(C), isMsMove(isM) {}

	//for hash table
	bool operator== (const State& that) const {
		return mouse == that.mouse && cat == that.cat && isMsMove == that.isMsMove;
	}
};

struct StateHash {
	size_t operator()(const State& st) const {
		return  hash<int>()(st.mouse) ^
				hash<int>()(st.cat) ^
				hash<bool>()(st.isMsMove);
	}
};

class Solution {

	unordered_map<State, int, StateHash> known; //State that we know has final results
												// 1 = mouse won, 2 = cat won, 0 = draw

	queue<State> to_explore;

	void AddParents(const State& s, const vector<vector<int>>& graph) {
		if(s.isMsMove) {	// That means parents came due to cat move. So parents are neighbor of cat move
			for(int i = 0 ; i < (int)graph[s.cat].size() ; ++i) {	//try all neighbors
				if(graph[s.cat][i] != 0) {
					to_explore.push(State(s.mouse, graph[s.cat][i], false));
				}
			}
		} else {
			for(int i = 0 ; i < (int)graph[s.mouse].size() ; ++i) {	//try all neighbors
				to_explore.push(State(graph[s.mouse][i], s.cat, true));
			}
		}
	}

public:
	int catMouseGame(vector<vector<int>>& graph) {
		int N = (int) graph.size();

		//Base cases and populate all to explore nodes
		for(int i = 0 ; i < N ; ++i) {
			for(int j = 1 ; j < N ; ++j) {
				if(i == j) {			//Mouse loses if mouse and cat are at same node (except 0) and whoever's move
					known[State(i, j, true)] = known[State(i, j, false)] = 2;
					AddParents(State(i, j, true), graph);
					AddParents(State(i, j, false), graph);
				} else if(i == 0) {		//Mouse wins at 0 and its whoever's move
					known[State(0, j, true)] = known[State(0, j, false)] = 1;
					AddParents(State(0, j, true), graph);
					AddParents(State(0, j, false), graph);
				}
			}
		}


		while(!to_explore.empty()) {
			State s = to_explore.front();
			to_explore.pop();

			if(known.find(s) != known.end() && (known[s] == 1 || known[s] == 2)) {
				continue;
			}

			int count_all_lose = 0;
			bool done = false;

			// First try to win, then draw and then if nothing possible then lose
			if(s.isMsMove) {
				for(int i = 0 ; i < (int)graph[s.mouse].size() ; ++i) {	//try all neighbors
					State next(graph[s.mouse][i], s.cat, false);
					if(known.find(next) != known.end()) {
						if(known[next] == 1) {
							known[s] = 1;
							done = true;
							break;
						} else if(known[next] == 2) {
							++count_all_lose;
						}
					}
				}
				if(count_all_lose == (int)graph[s.mouse].size()) {
					known[s] = 2;
					done = true;
				}
			} else {
				bool zero_was_ngb = false;
				for(int i = 0 ; i < (int)graph[s.cat].size() ; ++i) {	//try all neighbors
					if(graph[s.cat][i] == 0) {	// cat will not go to node 0
						zero_was_ngb = true;
						continue;
					}
					State next(s.mouse, graph[s.cat][i], true);

					if(known.find(next) != known.end()) {
						if(known[next] == 2) {
							known[s] = 2;
							done = true;
							break;
						} else if(known[next] == 1) {
							++count_all_lose;
						}
					}
				}
				if(count_all_lose == ((int)graph[s.cat].size() - (zero_was_ngb?1:0))) {
					known[s] = 1;
					done = true;
				}
			}

			if(done) {
				AddParents(s, graph);
			}
		}

		State start(1, 2, true);
		if(known.find(start) != known.end()) {
			return known[start];
		} else {
			return 0;	// Draw
		}
	}
};


int main() {

	Solution obj;

	vector<vector<int>> G = {
			{2,5},{3},{0,4,5},{1,4,5},{2,3},{0,2,3}
	};
	cout << obj.catMouseGame(G) << endl;	// 0

	Solution obj1;

	vector<vector<int>> G1 = {
			{6},{4},{9},{5},{1,5},{3,4,6},{0,5,10},{8,9,10},{7},{2,7},{6,7}
	};
	cout << obj1.catMouseGame(G1) << endl;	// 1


	Solution obj2;
	vector<vector<int>> G2 = {
			{{2,3},{3,4},{0,4},{0,1},{1,2}}
	};
	cout << obj2.catMouseGame(G2) << endl;	// 1
}


