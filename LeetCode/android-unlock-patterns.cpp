/*
 * android-unlock-patterns.cpp
 *
 *  Created on: May 30, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

void CombinationHelper(int k, int n, VI& A, VVI& result)
{
	if(k < 1) {
		return;
	}
	if(k > n) {
		return;
	}
	if(k == n) {
		result.emplace_back(A.begin(), A.begin()+n);
		return;
	}
	if(k == 1) {
		for(int i=0; i < n ; ++i) {
			VI single = { A[i] };
			result.emplace_back(single);
		}
		return;
	}

	VVI temp_result;
	CombinationHelper(k-1, n-1, A, temp_result);
	for(VI& t: temp_result) {
		t.emplace_back(A[n-1]);
		result.emplace_back(t);
	}

	CombinationHelper(k, n-1, A, result);
}

VVI Combinations(VI A, int k)
{
	VI partial_result;
	VVI result;

	CombinationHelper(k, A.size(), A, result);

	return result;
}

class Solution {
    vector<unordered_set<int>> grid =
    {{}, {2,4,5}, {1,3,4,5,6}, {2,5,6}, {1,2,5,7,8}, {1,2,3,4,6,7,8,9}, {2,3,5,8,9}, {4,5,8}, {4,5,6,7,9}, {5,6,8}};
    vector<vector<int>> cross{10, vector<int>(10,0)};

    void setCross() {
        cross[1][3] = 2;
        cross[3][1] = 2;
        cross[1][7] = 4;
        cross[7][1] = 4;
        cross[1][9] = 5;
        cross[9][1] = 5;
        cross[4][6] = 5;
        cross[6][4] = 5;
        cross[7][3] = 5;
        cross[3][7] = 5;
        cross[2][8] = 5;
        cross[8][2] = 5;
        cross[7][9] = 8;
        cross[9][7] = 8;
        cross[9][3] = 6;
        cross[3][9] = 6;
    }

    bool isValid(const VI& A) {
        unordered_set<int> past;
        for(int i = 0 ; i < (int)A.size()-1 ; ++i) {
            if(grid[A[i]].find(A[i+1]) == grid[A[i]].end() &&
               ((cross[A[i]][A[i+1]] == 0) || past.find(cross[A[i]][A[i+1]]) == past.end())) {
                return false;
            }
            past.emplace(A[i]);
        }
        return true;
    }

public:
    int numberOfPatterns(int m, int n) {

        int count = 0;
        VI A = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        setCross();

        for(int i = m ; i <= n ; ++i) {
            VVI result = Combinations(A, i);

            for(auto arr: result) {

//            	for(auto j: arr) {
//            		cout << j << ", ";
//            	}
//            	cout << endl;

                sort(arr.begin(), arr.end());
                do {

                    if(isValid(arr)) {
                        ++count;
                    }
                } while(next_permutation(arr.begin(), arr.end()));
            }
        }

        return count;
    }
};

int main()
{
	Solution obj;
	cout << obj.numberOfPatterns(1,1) << endl;
}

