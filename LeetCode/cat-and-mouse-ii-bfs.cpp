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
		Pos() : x(-1), y(-1) {}
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

		State(int Mx, int My, int Cx, int Cy, bool isM) : mouse(Mx,My), cat(Cx,Cy), isMsMove(isM) {}
		State(Pos M, Pos C, bool isM) : mouse(M), cat(C), isMsMove(isM) {}
		State(const State& that) : mouse(that.mouse), cat(that.cat), isMsMove(that.isMsMove) {}

		//for hash table
		bool operator== (const State& that) const {
			return mouse == that.mouse && cat == that.cat && isMsMove == that.isMsMove;
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
		if(a < 0 || b < 0 || a >= R || b >= C) {
			return false;
		}
		Pos p(a,b);
		if(W.find(p) != W.end()) {
			return false;
		}
		return true;
	}


	bool isAllLost(vector<string>& grid, Pos m, Pos c, int check) {
		//check means next move: 1 = mouse, 2 = cat
		int x = (check == 1) ? m.x : c.x;
		int y = (check == 1) ? m.y : c.y;
		int jmp = (check == 1) ? MJ : CJ;

		bool allLost = true;
		for(int d = 0 ; d < 4 ; ++d) {
			for(int j = 0 ; j <= jmp ; ++j) {
				int nx = x + dir[d][0] * j;
				int ny = y + dir[d][1] * j;

				if(isValid(nx,ny)) {
					Pos np(nx, ny);
					Pos nm = (check == 1) ? np : m;
					Pos nc = (check == 1) ? c : np;
					State ns(nm, nc, (check != 1));
					if(known.find(ns) == known.end() || (check == known[ns])) {
						allLost = false;
						break;
					}
				} else {
					break;
				}
			}
		}

		return allLost;
	}

	bool canWin(vector<string>& grid, Pos m, Pos c, int check) {
		//check means next move: 1 = mouse, 2 = cat
		int x = (check == 1) ? m.x : c.x;
		int y = (check == 1) ? m.y : c.y;
		int jmp = (check == 1) ? MJ : CJ;


		bool canWin = false;
		for(int d = 0 ; d < 4 ; ++d) {
			for(int j = 0 ; j <= jmp ; ++j) {
				int nx = x + dir[d][0] * j;
				int ny = y + dir[d][1] * j;

				if(isValid(nx,ny)) {
					Pos np(nx, ny);
					Pos nm = (check == 1) ? np : m;
					Pos nc = (check == 1) ? c : np;
					State ns(nm, nc, (check != 1));
					if(known.find(ns) != known.end() && (check == known[ns])) {
						canWin = true;
						break;
					}
				} else {
					break;
				}
			}
		}

		return canWin;
	}

	void checkNeighborState(vector<string>& grid, Pos m, Pos c, int check, queue<State>& nextFound) {
		State ns(m,c,(check == 1));

		if(known.find(ns) != known.end()) {
			return;
		}

		if(canWin(grid, m, c, check)) {
			known[ns] = check;
			nextFound.push(ns);
		} else {
			bool allLost = isAllLost(grid, m, c, check);
			if(allLost) {
				known[ns] = ((check == 1) ? 2 : 1);
				nextFound.push(ns);
			}
		}
	}

	void init(vector<string>& grid, int cJ, int mJ) {
		R = grid.size();
		C = grid[0].length();
		MJ = mJ;
		CJ = cJ;

		for(int i = 0 ; i < R ; ++i) {
			for(int j = 0 ; j < C ; ++j) {
				if(grid[i][j] == '.') {
					continue;
				} else if(grid[i][j] == '#') {
					W.emplace(Pos(i,j));
				} else if(grid[i][j] == 'M') {
					im = Pos(i,j);
				} else if(grid[i][j] == 'C') {
					ic = Pos(i,j);
				} else if(grid[i][j] == 'F') {
					f = Pos(i,j);
				}
			}
		}
	}

	void populateKnownStates() {
		for(int i = 0 ; i < R ; ++i) {
			for(int j = 0 ; j < C ; ++j) {
				Pos p(i,j);

				//Not at food or at wall
				if(p != f && W.find(p) == W.end()) {
					//mouse at food
					State s1(f, p, true);
					State s2(f, p, false);
					known[s1] = known[s2] = 1;

					//cat at food
					State s3(p, f, true);
					State s4(p, f, false);
					known[s3] = known[s4] = 2;

					//Mouse & and cat at same position
					State s5(p, p, true);
					State s6(p, p, false);
					known[s5] = known[s6] = 2;

					newFound.push(s1);
					newFound.push(s2);
					newFound.push(s3);
					newFound.push(s4);
					newFound.push(s5);
					newFound.push(s6);

				}
			}
		}
	}

	int R, C;
	Pos f,ic,im;
	unordered_set<Pos, PosHash> W;
	unordered_map<State, int, StateHash> known; //State that we know has final results
												// 1 = mouse won, 2 = cat won, 0 = draw
	queue<State> newFound;
	int MJ, CJ;
	vector<vector<int>> dir = {{0,1}, {0,-1}, {1,0}, {-1,0}};

public:
	bool canMouseWin(vector<string>& grid, int cJ, int mJ) {

		init(grid, cJ, mJ);
		populateKnownStates();


		State start(im, ic, true);
		int iter = 0;

		while(iter < 1000 && known.find(start) == known.end() && !newFound.empty()) {
			//cout << "Iter: "<< iter << ", New states: " << newFound.size() <<  endl;
			++iter;
			queue<State> nextFound;

			while(!newFound.empty()) {
				State top = newFound.front();
				newFound.pop();

				if(known.find(top) == known.end()) {
					cout << "Problem: only known states can be in the queue!!" << endl;
					continue;
				}

				Pos m = top.mouse;
				Pos c = top.cat;
				bool isMsMove = top.isMsMove;

				//cout << m.x << ", " << m.y << ";" << c.x << ", " << c.y << " - Mouse move: " << isMsMove << " # Res = " << res <<endl;

				if(isMsMove) { //Now mouse so last move was cat
					for(int d = 0 ; d < 4 ; ++d) {
						for(int j = 0 ; j <= CJ ; ++j) {
							int nx = c.x + dir[d][0] * j;
							int ny = c.y + dir[d][1] * j;

							if(isValid(nx,ny)) {
								Pos np(nx, ny);
								checkNeighborState(grid, m, np, 2, nextFound);
							} else {
								break;
							}
						}
					}


				} else { //last was mouse
					for(int d = 0 ; d < 4 ; ++d) {
						for(int j = 0 ; j <= MJ ; ++j) {
							int nx = m.x + dir[d][0] * j;
							int ny = m.y + dir[d][1] * j;

							if(isValid(nx,ny)) {
								Pos np(nx, ny);
								checkNeighborState(grid, np, c, 1, nextFound);
							} else {
								break;
							}
						}
					}
				}

			}
			newFound = nextFound;
		}

		//cout << "Is found: " << (known.find(start) != known.end()) << ", Res: " << known[start] << ", is next empty: " << newFound.empty() << endl;
		return (known.find(start) != known.end()) && (known[start] == 1);
	}
};

int main() {
	Solution obj;
	vector<string> grid;
	bool res;

	//grid = {"F...C","...#.","##...","#.##M","#.##.",".#..."};
	//grid = {"F.C..","...#.","##M..","#.##.","#.##.",".#..."};
	grid = {"F..C.","...#.","##.M.","#.##.","#.##.",".#..."};
	res = obj.canMouseWin(grid, 1, 6);
	cout << "Expected: 0, Actual: " << res << endl;

//	grid = {"..#C","...#","..M.","#F..","...."};
//	res = obj.canMouseWin(grid, 2, 1);
//	cout << "Expected: 1, Actual: " << res << endl;

//	grid = {"####F","#C...","M...."};
//	res = obj.canMouseWin(grid, 1, 4);
//	cout << "Expected: 1, Actual: " << res << endl;

}
