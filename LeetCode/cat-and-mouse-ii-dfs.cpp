/*
 * cat-and-mouse-ii.cpp
 *
 *  Created on: Jan 16, 2021
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;


class Solution {
	struct Pos {
		int x, y;
		Pos(int X, int Y) : x(X), y(Y) {}
		Pos() : x(0), y(0) {}
		Pos(const Pos& that) : x(that.x), y(that.y) {}

		bool operator== (const Pos& that) const {
			return x == that.x && y == that.y;
		}
		bool operator!= (const Pos& that) const {
			return x != that.x || y != that.y;
		}
	};

	struct PosHash {
		size_t operator()(const Pos& pt) const {
			return hash<int>()(pt.x) ^ hash<int>()(pt.y);
		}
	};

	struct State {
		Pos mouse,cat;
		bool isMsMove;
		int turn;

		State(int Mx, int My, int Cx, int Cy, bool isM, int T) : mouse(Mx,My), cat(Cx,Cy), isMsMove(isM), turn(T) {}
		State(Pos M, Pos C, bool isM, int T) : mouse(M), cat(C), isMsMove(isM), turn(T) {}
		State(const State& that) : mouse(that.mouse), cat(that.cat), isMsMove(that.isMsMove), turn(that.turn) {}

		//for hash table
		bool operator== (const State& that) const {
			return mouse == that.mouse && cat == that.cat && isMsMove == that.isMsMove && turn == that.turn;
		}
	};

	struct StateHash {
		size_t operator()(const State& st) const {
			return  PosHash()(st.mouse) ^
					PosHash()(st.cat) ^
					hash<bool>()(st.isMsMove);
		}
	};

	bool isValid(int a, int b) {
		if(a < 0 || b < 0 || a >= R || b >= C || grid[a][b] == '#') {
			return false;
		}
		return true;
	}

	void init(vector<string>& G, int cJ, int mJ) {
		grid = G;
		R = grid.size();
		C = grid[0].length();
		MJ = mJ;
		CJ = cJ;

		for(int i = 0 ; i < R ; ++i) {
			for(int j = 0 ; j < C ; ++j) {
				if(grid[i][j] == '.') {
					continue;
				} else if(grid[i][j] == 'M') {
					im = Pos(i,j);
				} else if(grid[i][j] == 'C') {
					ic = Pos(i,j);
				} else if(grid[i][j] == 'F') {
					f = Pos(i,j);
				}
			}
		}

		memset(DP, -1, sizeof(DP));
	}



	int DFS(State s) {

		if(s.cat == s.mouse) { 	return 2;	}
		if(s.mouse == f) {	return 1;	}
		if(s.cat == f) { return 2;	}
		if(s.turn >= 50) {	return 0;	}

		int& val = DP[s.mouse.x][s.mouse.y][s.cat.x][s.cat.y][s.isMsMove][s.turn];

		//cout << s.mouse.x << ", " << s.mouse.y << " | " << s.cat.x << ", " << s.cat.y << " - " << s.isMsMove << " - " << s.turn	<< " = " << val << endl;

		if(val != -1) {
			return val;
		}

		if(s.isMsMove) {
			bool canWin = false;
			for(int d = 0 ; !canWin && d < 4 ; ++d) {
				for(int j = 0 ; !canWin && j <= MJ ; ++j) {
					int nx = s.mouse.x + dir[d][0] * j;
					int ny = s.mouse.y + dir[d][1] * j;

					if(isValid(nx,ny)) {
						Pos np(nx, ny);

						State ns(np, s.cat, false, s.turn + 1);
						if(DFS(ns) == 1) {
							canWin = true;
						}
					} else {	//Cannot go further in this direction
						break;
					}
				}
			}

			if(canWin) {
				val = 1;
			} else {
				val = 2;
			}

		} else { //Cat
			bool canWin = false;
			for(int d = 0 ; !canWin && d < 4 ; ++d) {
				for(int j = 0 ; !canWin && j <= CJ ; ++j) {
					int nx = s.cat.x + dir[d][0] * j;
					int ny = s.cat.y + dir[d][1] * j;

					if(isValid(nx,ny)) {
						Pos np(nx, ny);
						State ns(s.mouse, np, true, s.turn + 1);
						if(DFS(ns) != 1) {
							canWin = true;
						}
					} else {	//Cannot go further in this direction
						break;
					}
				}
			}

			if(canWin) {
				val = 2;
			} else {
				val = 1;
			}
		}

		return val;
	}

	int R, C;
	Pos f,ic,im;
	//unordered_set<Pos, PosHash> W;
//	unordered_map<State, int, StateHash> known; //State that we know has final results
//												// 1 = mouse won, 2 = cat won, 0 = draw
	int DP[8][8][8][8][2][50];
	int MJ, CJ;
	vector<vector<int>> dir = {{0,1}, {0,-1}, {1,0}, {-1,0}};
	vector<string> grid;

public:
	bool canMouseWin(vector<string>& G, int cJ, int mJ) {

		init(G, cJ, mJ);
		State start(im, ic, true, 0);
		int res = DFS(start);

		return res == 1;
	}
};

int main() {
	Solution obj;
	vector<string> grid;
	bool res;

	//grid = {"F...C","...#.","##...","#.##M","#.##.",".#..."};
	//grid = {"F.C..","...#.","##M..","#.##.","#.##.",".#..."};
//	grid = {"F..C.","...#.","##.M.","#.##.","#.##.",".#..."};
//	res = obj.canMouseWin(grid, 1, 6);
//	cout << "Expected: 0, Actual: " << res << endl;

//	grid = {"..#C","...#","..M.","#F..","...."};
//	res = obj.canMouseWin(grid, 2, 1);
//	cout << "Expected: 1, Actual: " << res << endl;

//	grid = {"####F","#C...","M...."};
//	res = obj.canMouseWin(grid, 1, 4);
//	cout << "Expected: 1, Actual: " << res << endl;


	grid = {"####F","#C...","M...."};
	res = obj.canMouseWin(grid, 1, 2);
	cout << "Expected: 1, Actual: " << res << endl;

}
