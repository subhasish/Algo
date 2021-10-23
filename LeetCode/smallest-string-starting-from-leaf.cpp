/*
 * smallest-string-starting-from-leaf.cpp
 *
 *  Created on: May 5, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    bool foundOne;
    string result;

    bool isSmaller(const string& a, const string& b) {
        return a < b;
    }

    void smallestFromLeafPostOrder(TreeNode* root, string s) {
        if(root == nullptr) {
            if(!foundOne) {
                result = s;
                foundOne = true;
            } else {
                if(isSmaller(s, result)) {
                    result = s;
                }
            }
        } else {
            char ch = 'a' + root->val;
            string new_s = ch + s;
            smallestFromLeafPostOrder(root->left, new_s);
            smallestFromLeafPostOrder(root->right, new_s);
        }
    }
public:
    string smallestFromLeaf(TreeNode* root) {
        foundOne = false;
        result = "";

        string s = "";
        smallestFromLeafPostOrder(root, s);
        return result;
    }
};

int main() {
	TreeNode a(0);
	TreeNode b(1);
	TreeNode c(2);
	TreeNode d1(3);
	TreeNode e1(4);
	TreeNode d2(3);
	TreeNode e2(4);

	a.left = &b;
	a.right = &c;
	b.left = &d1;
	b.right = &e1;
	c.left = &d2;
	c.right = &e2;

	Solution obj;
	cout << obj.smallestFromLeaf(&a) << endl;
}

