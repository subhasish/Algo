/*
 * count-complete-tree-nodes.cpp
 *
 *  Created on: Feb 2, 2019
 *      Author: subha
 */




#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    int max_height(TreeNode* root) {
        int max_h = 0;
        while(root != NULL) {
            ++max_h;
            root = root->left;
        }
        return max_h;
    }

public:
    int countNodes(TreeNode* root) {
        if(root == NULL) {
            return 0;
        }
        int count = 1;  //root
        int height = max_height(root);
        int r_height = max_height(root->right);
        if(r_height < height-1) { //right subtree is full
            count += (1 << r_height) - 1;
            count += countNodes(root->left);
        } else {                //left subtree is full
            count += (1 << (height - 1)) - 1;
            count += countNodes(root->right);
        }
        return count;
    }
};

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

TreeNode* stringToTreeNode(string input) {
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    if (!input.size()) {
        return nullptr;
    }

    string item;
    stringstream ss;
    ss.str(input);

    getline(ss, item, ',');
    TreeNode* root = new TreeNode(stoi(item));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (true) {
        TreeNode* node = nodeQueue.front();
        nodeQueue.pop();

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->left = new TreeNode(leftNumber);
            nodeQueue.push(node->left);
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->right = new TreeNode(rightNumber);
            nodeQueue.push(node->right);
        }
    }
    return root;
}

int main() {
    string line = "[1,2,3,4,5,6]";

	TreeNode* root = stringToTreeNode(line);

	int ret = Solution().countNodes(root);

	string out = to_string(ret);
	cout << out << endl;

    return 0;
}
