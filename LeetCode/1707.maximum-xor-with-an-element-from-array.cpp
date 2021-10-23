/*
 * 1707.maximum-xor-with-an-element-from-array.cpp
 *
 *  Created on: Jan 2, 2021
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct TrieNode {
        TrieNode* next[2];

        int num;
        int minInSubtree;

        TrieNode() {
            minInSubtree = numeric_limits<int>::max();
            num = -1;
            next[0] = nullptr;
            next[1] = nullptr;
        }

        ~TrieNode() {
            if(next[0] != nullptr) { delete next[0]; }
            if(next[1] != nullptr) { delete next[1]; }
        }
    };

    TrieNode* getNewTrieNode() {
        return new TrieNode();
    }

    void TrieInsert(TrieNode* root, int num) {
        TrieNode* p = root;

        for(int i = (1 << 4) ; i > 0 ; i = (i >> 1)) {
            int b = num & i;

            p->minInSubtree = min(p->minInSubtree, num);

            if(b == 0) {
                if(p->next[0] == nullptr) {
                	p->next[0] = new TrieNode();
                }
                p = p->next[0];
            } else if(b == i) {
                if(p->next[1] == nullptr) {
                	p->next[1] = new TrieNode();
                }
                p = p->next[1];
            }
        }
        p->num = num;
        p->minInSubtree = min(p->minInSubtree, num);
    }

public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        TrieNode* root = new TrieNode();
        vector<int> res(queries.size(), -1);

        for(int i = 0 ; i < (int)nums.size() ; ++i) {
            TrieInsert(root, nums[i]);
        }

        for(int i = 0 ; i < (int)queries.size() ; ++i) {
            int x = queries[i][0];
            int m = queries[i][1];

            TrieNode* p = root;
            for(int j = (1 << 4) ; j > 0 ; j = (j >> 1)) {
                int b = (x & j);
                if(b == j) {
                    if(p->next[0] != nullptr && p->next[0]->minInSubtree <= m) {
                        p = p->next[0];
                    } else if(p->next[1] != nullptr && p->next[1]->minInSubtree <= m) {
                        p = p->next[1];
                    } else {
                    	p = nullptr;
                    	break;
                    }
                } else {
                     if(p->next[1] != nullptr && p->next[1]->minInSubtree <= m) {
                        p = p->next[1];
                    } else if(p->next[0] != nullptr && p->next[0]->minInSubtree <= m) {
                        p = p->next[0];
                    } else {
                    	p = nullptr;
                    	break;
                    }
                }
            }
            if(p != nullptr && p->num != -1) {
                res[i] = (x ^ p->num);
            }

        }

        return res;
    }
};


int main() {
	Solution obj;
	vector<int> nums;
	vector<vector<int>> queries;
	vector<int> res;;

	nums = {0,1,2,3,4};
	queries = {{3,1},{1,3},{5,6}};
	res = obj.maximizeXor(nums, queries);
	cout << "Expected: [3, 3, 7], Actual: [";
	for(auto i: res) {
		cout << i << ", " ;
	}
	cout << "]" << endl;
}



