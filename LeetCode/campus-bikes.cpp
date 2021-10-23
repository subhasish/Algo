/*
 * campus-bikes.cpp
 *
 *  Created on: Jun 29, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> W;
vector<vector<int>> B;
int getD(int iw, int ib) {
    return abs(W[iw][0] - B[ib][0]) + abs(W[iw][1] - B[ib][1]);
}

struct WB {
    int iw, ib;

    bool operator< (const WB& that) const {
        int d1 = getD(iw, ib);
        int d2 = getD(that.iw, that.ib);

        if(d1 == d2) {
            if(iw == that.iw) {
                return ib < that.ib;
            } else {
                return iw < that.iw;
            }
        } else {
            return d1 < d2;
        }
    }
};

class Solution {

public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        W = workers;
        B = bikes;

        vector<int> res(workers.size());

        set<WB> ord;
        map<int, vector<set<WB>::iterator>> avl_bs;

        for(int i = 0 ; i < (int)bikes.size() ; ++i) {
            avl_bs[i] = vector<set<WB>::iterator>();
        }

        for(int i = 0 ; i < (int)workers.size() ; ++i) {
            int minD = getD(i,0), minb = 0;

            for(int j = 1 ; j < (int)bikes.size() ; ++j) {
                int d = getD(i, j);
                if(minD > d) {
                    minD = d;
                    minb = j;
                }
            }
            auto it = ord.emplace(WB{i, minb});
            avl_bs[minb].emplace_back(it.first);
        }

        while(!ord.empty()) {
            auto it = ord.begin();
            int b = (*it).ib;
            int w = (*it).iw;
            res[w] = b;


            vector<set<WB>::iterator> nws = avl_bs[b];
            vector<int> wis;
            for(auto nw: nws) {
            	if((*nw).iw == w) {
            		continue;
            	}
                wis.emplace_back((*nw).iw);
                ord.erase(nw);
            }
            avl_bs.erase(b);
            ord.erase(ord.begin());

            for(auto nw: wis) {
                int minD = getD(nw, avl_bs.begin()->first);
                int minb = avl_bs.begin()->first;

                for(auto itb: avl_bs) {
                    int d = getD(nw, itb.first);
                    if(minD > d) {
                        minD = d;
                        minb = itb.first;
                    }
                }

                auto it = ord.emplace(WB{nw, minb});
                avl_bs[minb].emplace_back(it.first);
            }
        }
        return res;
    }
};

int main() {
	Solution obj;

	vector<vector<int>> w = {{0, 0}, {2, 1}};
	vector<vector<int>> b = {{1, 2}, {3, 3}};

	vector<int> res = obj.assignBikes(w, b);

	for(int i: res) {
		cout << i << " ";
	}
	cout << endl;
}


