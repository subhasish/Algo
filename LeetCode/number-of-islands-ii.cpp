/*
 * number-of-islands-ii.cpp
 *
 *  Created on: May 28, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    int getKey(int i, int j, int cols) {
        return i * cols + j;
    }
    vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    bool isValid(int i, int j, int m, int n) {
        return i >= 0 && j >= 0 && i < m && j < n;
    }

    int getRoot(int i, int j, int cols, const vector<int>& resp) {
        int key = getKey(i, j, cols);
        while(resp[key] != key) {
            key = resp[key];
            resp[key] = resp[resp[key]];
        }
        return key;
    }

public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        vector<int> reps(m * n);
        for(int i = 0 ; i < m ; ++i) {
            for(int j = 0 ; j < n ; ++j) {
                int key = getKey(i, j, n);
                reps[key] = key;
            }
        }

        vector<vector<bool>> grid(m, vector<int>(n, false));
        vector<int> res;
        res.emplace_back(0);
        for(auto pt: positions) {
            int x = pt[0];
            int y = pt[1];

            if(grid[x][y] == true) {
                res.emplace_back(res.back());
                continue;
            }

            grid[x][y] = true;
            res.emplace_back(res.back() + 1);
            int dec = 0;
            for(int i = 0 ; i < 4 ; ++i) {
                int nx = x + dir[i][0];
                int ny = y + dir[i][1];
                if(isValid(nx, ny, m, n) && grid[nx][ny] == true) {

                }
            }

        }
        return *(res.begin()+1);
    }
};

