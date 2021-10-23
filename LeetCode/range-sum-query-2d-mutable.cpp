/*
 * range-sum-query-2d-mutable.cpp
 *
 *  Created on: Mar 6, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class NumMatrix {
    int R, C;

    vector<vector<int>> sum;			// sum[i,j] will contain sum of cells of rectangle whose top-left corner is [i,j]
    vector<vector<int>> col_sum;		// col_sum[i,j] will contain sum of cells through [i,j] to [row_max, j]
    vector<vector<int>> grid;			// Will contain actual values on the grid

    map<pair<int,int>, int> deltas;		// Will contain some intermediate updates

    void PrintSum() {
    	cout << "Sum matrix:" << endl;
    	for(int i=0 ; i< (int)sum.size() ; ++i) {
    		cout << "[ ";
    		for(int j=0 ; j < (int) sum[0].size() ; ++j) {
    			cout << sum[i][j] << ", ";
    		}
    		cout << "]" << endl;
    	}
    }

    void UpdateSum() {
        for(int j = 0 ; j < C ; ++j) {
            col_sum[R-1][j] = grid[R-1][j];
            for(int i = R-2 ; i >= 0 ; --i) {
                col_sum[i][j] = col_sum[i+1][j] + grid[i][j];
            }
        }

        for(int i = 0 ; i < R ; ++i) {
            sum[i][C-1] = col_sum[i][C-1];
        }
        for(int j = C-2 ; j >= 0 ; --j) {
            for(int i = R-1 ; i >= 0 ; --i) {
                sum[i][j] = grid[i][j] + sum[i][j+1] + ((i < R-1) ? col_sum[i+1][j] : 0);
            }
        }

        dirty = false;
    }

    bool dirty;
public:
    NumMatrix(vector<vector<int>> matrix) {
        R = matrix.size();
        C = (R>0) ? matrix[0].size() : 0;
        grid = matrix;
        sum = vector<vector<int>>(R, vector<int>(C,0));
        col_sum = vector<vector<int>>(R, vector<int>(C,0));
        UpdateSum();
    }

    void update(int row, int col, int val) {
        deltas[make_pair(row, col)] = val - grid[row][col];

        dirty = true;

        if((int) deltas.size() > R+C) {
            for(auto p: deltas) {
                int r = p.first.first;
                int c = p.first.second;
                grid[r][c] += p.second;
            }
            UpdateSum();
            deltas.clear();
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int s1 = sum[row1][col1];
        int s2 = (col2 < C-1) ? sum[row1][col2+1] : 0;
        int s3 = (row2 < R-1) ? sum[row2+1][col1] : 0;
        int s4 = (col2 < C-1 && row2 < R-1) ? sum[row2+1][col2+1] : 0;
        int s = s1 - s2 - s3 + s4;

        if(dirty) {
            for(auto p: deltas) {
                int r = p.first.first;
                int c = p.first.second;
                if(r >= row1 && r <= row2 && c >= col1 && c <= col2) {
                    s += p.second;
                }
            }
        }
        return s;
    }


};

/*
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */

int main() {
	vector<vector<int>> matrix = {
			{3, 0, 1, 4, 2},
			{5, 6, 3, 2, 1},
			{1, 2, 0, 1, 5},
			{4, 1, 0, 1, 7},
			{1, 0, 3, 0, 5}
	};
	NumMatrix obj(matrix);

//	obj.PrintSum();

	cout << "Sum region: " << obj.sumRegion(2, 1, 4, 3) << endl;
	obj.update(3, 2, 2);

//	obj.PrintSum();

	cout << "Sum region: " << obj.sumRegion(2, 1, 4, 3) << endl;
}



