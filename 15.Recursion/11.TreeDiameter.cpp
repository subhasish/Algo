/*
 * 11.TreeDiameter.cpp
 *
 * Problem: Diameter of a tree is defined as the longest distance between two nodes in the tree.
 * 			Distance is the weighted distance considering the weight of the edges in the path.
 * 			Design an algorithm to compute the diameter of a tree. Tree can be a general tree
 * 			not only binary tree.
 *
 *  Created on: Apr 16, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Brute force can be to run BSF from each node and take the maximum. It is O(n^2).
//
//			One observation is that solution does not differ even if we take different root.
//			Another observation is that in the path of maximum diameter, for any node, the two
//			branches of the diameter are the two branches with maximum height.
//
//			Using the second observation we can solve the problem using postorder traversal.
//			Once we find height of each branch we can compute the diameter passing through
//			that node.
//			Keep track of the maximum to get the final diameter. Note that maximum diameter
//			may not pass through the root.
//
//			Regarding data structure, edge should have weight. So a vertex should have
//			vector of edges.
//
// C++:
//			unique_ptr as well as any object that has unique_ptr in its data model cannot be
//			used in initializer list. This is because initializer list is always copy constructed
//			and unique_ptr cannot be copied.


struct TreeNode
{
	struct Edge{
		double length;
		unique_ptr<TreeNode> other_node;

		Edge(double l, unique_ptr<TreeNode> t) : length(l), other_node(move(t)) {}

	};

	vector<Edge> edges;
};

typedef unique_ptr<TreeNode> UTN;
typedef TreeNode::Edge Edge;

struct HeightAndDiameter{
	double height, diameter;
};

HeightAndDiameter ComputeHeightAndDiameter(unique_ptr<TreeNode>& root)
{
	double max_diameter = numeric_limits<double>::min(); // Stores maximum diameter in subtree
	vector<double> max_2_heights(2 /*size*/, 0.0); // Stores the two maximum heights for diameter {max, 2nd}

	for(TreeNode::Edge& edge: root->edges) {
		HeightAndDiameter h_d = ComputeHeightAndDiameter(edge.other_node);

		// See if height is among top two.
		double path_height = h_d.height + edge.length;
		if(path_height > max_2_heights[0]) {
			max_2_heights = { path_height, max_2_heights[0] };
		}
		else if( path_height > max_2_heights[1]) {
			max_2_heights[1] = path_height;
		}

		// Update maximum diameter in the subtrees
		max_diameter = max(max_diameter, h_d.diameter);
	}

	return {max_2_heights[0], max(max_diameter, max_2_heights[0] + max_2_heights[1]) };
}

double ComputeDiameter(unique_ptr<TreeNode>& root)
{
	return root ? ComputeHeightAndDiameter(root).diameter : 0.0;
}


int main()
{
	Edge a = Edge(6, UTN(new TreeNode{{}}));

	Edge b = Edge(4, UTN(new TreeNode{{}}));
	b.other_node->edges.emplace_back(move(a));
	Edge c = Edge(3, UTN(new TreeNode{{}}));

	Edge d = Edge(7, UTN(new TreeNode{{}}));
	d.other_node->edges.emplace_back(move(b));
	d.other_node->edges.emplace_back(move(c));
	Edge e = Edge(14, UTN(new TreeNode{{}}));
	Edge f = Edge(3, UTN(new TreeNode{{}}));


	unique_ptr<TreeNode> root = UTN(new TreeNode{{}});
	root->edges.emplace_back(move(d));
	root->edges.emplace_back(move(e));
	root->edges.emplace_back(move(f));


	cout << "Diameter of the tree: " << ComputeDiameter(root) << endl;
}
