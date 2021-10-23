/*
 * HC.34.HuffmanCoding.cpp
 *
 * Problem: One way to compress text is to build a code book that maps each character to a bit string,
 *			and then concatenate all the codes. For decompressing the restriction will be that one
 *			code cannot be prefix of another code.
 *
 *			Shorter code to more frequent characters will result in better compression. Better
 *			compression can be achieved if code is assigned to common sequence of characters, but
 *			increases complexity. So restrict to individual characters.
 *
 *			When frequency is normalized, the term 'average code length' is the defined as sum of
 *			the product of the length of each character with its normalized frequency.
 *			Normalized frequency means when sum of all frequencies is 1.
 *
 *			Given a set of characters with corresponding frequencies, find a code book that has the
 *			smallest average code length.
 *
 *  Created on: Jan 11, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

/*Solution:
 *			One natural heuristic is to split the set of characters into two subsets, which have
 *			approximately equal aggregated frequencies, solve the problem for each subset, and then
 *			add 0 and 1 to each set. But this approach may not yield optimum coding and also
 *			such partitioning into two equal sets is challenging.
 *
 *			Another strategy could be assign 0 to the most frequent character and then solve the
 *			problem for rest of the characters and then prepend 1 with their solution. But it
 *			fares poorly when frequencies are same.
 *
 *			Huffman coding yields optimum coding for this problem. There may be other optimum codes
 *			as well. Basic idea is to focus on least frequent characters, rather than most frequent
 *			ones. Specifically, combine the two least frequent characters into a new character and
 *			recursively solve the problem for the resulting n-1 characters.
 *
 *			More precisely, Huffman coding proceeds in three steps:
 *			1. Sort characters based on frequencies and create binary tree nodes for each character.
 *			   Denote the set as S.
 *			2. Create a new node whose children are the two least frequent characters. Assign sum
 *			   of their frequencies to the new parent node.
 *			3. Add the new node to S and remove its children from S. Repeat from step 2 till S
 *			   consist of a single node.
 *			Mark all the left edge with 0 and right edge with 1. Path to character is its code.
 *
 *			No code being other's prefix is maintained by all the character being leaf node.
 *
 *			Regarding implementation, we need to form a tree when nodes are taken out of set S.
 *			From set S we only need minimum and has to be dynamic, so priority queue will work.
 *			But as nodes need to form a tree we can make priority queue of tree nodes.
 *
 *			While making the priority queue use shared_ptr of nodes instead of copy of nodes.
 *
 *			Rigorous proof for optimality is tough. Actual proof uses induction on the number of
 *			characters. It uses proof by contradiction, with two leaves in Huffman tree corresponding
 *			to the rarest character playing central role.
 *
 *			The tree for code word can be skewed. In such case codes will be of length 1,2,3,..,n.
 *			So time to generate the code cords is O(1+2+..+n)=O(n^2)
 *
 */

// input comes as vector of character with frequency
struct CharWithFrequency {
	char c;
	double freq;
};

struct BinaryTreeNode {
	double aggregate_freq;
	const CharWithFrequency* s;
	shared_ptr<BinaryTreeNode> left, right;
};

void AssignHuffmanCoding(const shared_ptr<BinaryTreeNode>& tree, unordered_map<char, string>& huffman_encoding,
						 const unique_ptr<string>& curr_code);

unordered_map<char, string> HuffmanCoding(const vector<CharWithFrequency>& symbols) {

	//Initially assign each symbol into candidate. Candidate will be a priority queue of BST nodes

	//**NOTE: make priority queue of shared_ptr of nodes instead of copy of nodes
	priority_queue<shared_ptr<BinaryTreeNode>, vector<shared_ptr<BinaryTreeNode>>,
			function<bool(const shared_ptr<BinaryTreeNode>, const shared_ptr<BinaryTreeNode>)>>
			candidates([](const shared_ptr<BinaryTreeNode>& lhs, const shared_ptr<BinaryTreeNode>& rhs)
					{
						return lhs->aggregate_freq > rhs->aggregate_freq;
					});

	for(const CharWithFrequency& c: symbols) {
		candidates.emplace(new BinaryTreeNode{c.freq, &c, nullptr, nullptr});
	}

	//Keep combining two nodes until there is one node left
	while(candidates.size() > 1) {
		shared_ptr<BinaryTreeNode> left = candidates.top();
		candidates.pop();
		shared_ptr<BinaryTreeNode> right = candidates.top();
		candidates.pop();
		candidates.emplace(new BinaryTreeNode{left->aggregate_freq + right->aggregate_freq, nullptr, left, right});
	}

	shared_ptr<BinaryTreeNode> root = candidates.top();
	//Now we got the Huffman tree. We need to assign the codes

	unordered_map<char, string> huffman_encoding;
	unique_ptr<string> curr_code(new string(""));
	//Traversing binary tree is done easily using recursive function
	AssignHuffmanCoding(root, huffman_encoding, curr_code);

	return huffman_encoding;
}

void AssignHuffmanCoding(const shared_ptr<BinaryTreeNode>& tree, unordered_map<char, string>& huffman_encoding,
						 const unique_ptr<string>& curr_code) {
	if(tree) {
		if(tree->s) {
			//Leaf node
			huffman_encoding[tree->s->c] = *curr_code;
		} else {
			//Non leaf node
			curr_code->push_back('0');
			AssignHuffmanCoding(tree->left, huffman_encoding, curr_code);
			curr_code->back() = '1';	//it returns reference
			AssignHuffmanCoding(tree->right, huffman_encoding, curr_code);
			curr_code->pop_back();
		}
	}
}

int main() {
	vector<CharWithFrequency> symbols =
	{
			{'a', 8.17},
			{'b', 1.49},
			{'c', 2.78},
			{'d', 4.25},
			{'e', 12.70},
			{'f', 2.23},
			{'g', 2.02},
			{'h', 6.09},
			{'i', 6.97},
			{'j', 0.15},
			{'k', 0.77},
			{'l', 4.07},
			{'m', 2.41},
			{'n', 6.75},
			{'o', 7.51},
			{'p', 1.93},
			{'q', 0.10},
			{'r', 5.99},
			{'s', 6.33},
			{'t', 9.02},
			{'u', 2.76},
			{'v', 0.98},
			{'w', 2.23},
			{'x', 0.15},
			{'y', 1.97},
			{'z', 0.07},
	};

	unordered_map<char, string> huffman_coding = HuffmanCoding(symbols);

	for(auto& it: huffman_coding) {
		cout << it.first << ": " << it.second << endl;
	}
}
