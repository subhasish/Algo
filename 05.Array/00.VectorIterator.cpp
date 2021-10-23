/*
 * 00.VectorIterator.cpp
 *
 * Problem: Implement iterator on 2D array
 *
 *  Created on: May 11, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Vector2D {
    vector<vector<int>> V;
    vector<vector<int>>::iterator it_row;
    vector<int>::iterator it;
public:
    Vector2D(vector<vector<int>>& v) {
        V = v;
        it_row = V.begin();
        while(it_row != V.end() && (*it_row).size() == 0) {
            ++it_row;
        }
        if(it_row != V.end()) {
            it = (*it_row).begin();
        }
    }

    int next() {
        int val = *it;

        ++it;
        while(it_row != V.end() && it == (*it_row).end()) {
            ++it_row;
            if(it_row != V.end()) {
                it = (*it_row).begin();
            }
        }
        return val;
    }

    bool hasNext() {
        if(it_row == V.end()) {
            return false;
        } else {
            return true;
        }
    }
};

int main () {
	vector<vector<int>> v = {{}};
	Vector2D obj(v);
	cout << obj.hasNext() << endl;
}
