/*
 * 01matrix.cpp
 *
 *  Created on: Jun 26, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool isValid(int x, int y, const vector<vector<int>>& matrix) {
        return x >= 0 && y >= 0 && x < matrix.size() && y < matrix[0].size();
    }

    vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};


public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) {
            return matrix;
        }

        vector<vector<int>> res(matrix.size(), vector<int>(matrix[0].size(), 0));
        vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size(), false));
        queue<pair<int,int>> Q;

        for(int i = 0 ; i < matrix.size() ; ++i) {
            for(int j = 0 ; j < matrix[i].size() ; ++j) {
                if(matrix[i][j] == 0) {
                    res[i][j] = 0;
                    visited[i][j] = true;

                    for(int k = 0 ; k < 4 ; ++k) {
                        int nx = i + dir[k][0];
                        int ny = j + dir[k][1];

                        if(isValid(nx, ny, matrix)) {
                            if(matrix[nx][ny] == 1 && visited[nx][ny] == false) {
                                res[nx][ny] = 1;
                                visited[nx][ny] = true;
                                Q.push(make_pair(nx, ny));
                            }
                        }
                    }
                }
            }
        }

        while(!Q.empty()) {
            pair<int,int> p = Q.front();
            Q.pop();

            int x = p.first;
            int y = p.second;
            int d = res[x][y];

            for(int k = 0 ; k < 4 ; ++k) {
                int nx = x + dir[k][0];
                int ny = y + dir[k][1];

                if(isValid(nx, ny, matrix)) {
                    if(matrix[nx][ny] == 1 && visited[nx][ny] == false) {
                        res[nx][ny] = d + 1;
                        visited[nx][ny] = true;
                        Q.push(make_pair(nx, ny));
                    }
                }
            }

        }

        return res;
    }
};

int main() {
	Solution obj;
	vector<vector<int>> A = {{0}};

	vector<vector<int>> B = obj.updateMatrix(A);

}

