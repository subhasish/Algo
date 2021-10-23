/*
 * 07.BinaryTreeDepthOrder.cpp
 *
 * Problem: Basically do BFS on a binary tree from root. But print one level at a time.
 *
 *  Created on: Jan 3, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Normal BFS can be done using one queue.
//           Level by level differentiation can be done by 2 queues, where one queue stores the nodes for next level
//           and one for current level
//
//           Using 2 queues makes it easier to solve similar cases when we need to print in zig-zag order

typedef vector<int> VI;
typedef vector<VI> VVI;

struct TreeNode
{
	int val;
	TreeNode *left,*right;

	TreeNode(int a, TreeNode* b=nullptr, TreeNode* c=nullptr) : val(a), left(b), right(c) {}
};

VVI BinaryTreeDepthOrder(TreeNode* root)
{
	VVI result;
	queue<TreeNode*> current_level;
	current_level.push(root);

	while(!current_level.empty()) {
		queue<TreeNode*> next_level;
		VI this_level;
		while(!current_level.empty()) {
			TreeNode* p=current_level.front();
			current_level.pop();
			this_level.push_back(p->val);

			if(p->left != nullptr) next_level.push(p->left);
			if(p->right != nullptr) next_level.push(p->right);
		}
		current_level = next_level;
		result.push_back(this_level);
	}

	return result;
}

void PrintTreeLevel(VVI t)
{
	cout << "Tree: " << endl;
	for(size_t i=0; i<t.size() ; ++i) {
		for(size_t j=0; j<t[i].size() ; ++j) {
			cout << t[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	TreeNode root(314,
			new TreeNode(6, new TreeNode(271), new TreeNode(561)),
			new TreeNode(6, new TreeNode(2), new TreeNode(271)));
	VVI levels = BinaryTreeDepthOrder(&root);
	PrintTreeLevel(levels);
}

