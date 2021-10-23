/*
 * 12.PattenConcatenations.cpp
 *
 * Problem: Write a program that takes an input string (sentence) and a set of strings (words) and
 * 			find substring of the sentence that is concatenation of all the words in the set.
 * 			Each string must appear only once and their order is immaterial. But set of words can contain duplicates.
 * 			Also assume all strings in the set has equal length.
 *
 *  Created on: Feb 26, 2018
 *      Author: subha
 */

#include<bits/stdc++.h>

using namespace std;

// Solution:
//				Problem can have a very specific solution due to fixed length of the words
//
//				In general, for each position, we need to find a string in the set that is a prefix of the string in the sentence.
//				And then recurse the remaining string with remaining words.
//
//				But due to equal lengths of words, only one word can be the prefix. So we can directly check the prefix with
//				the set of words
//
// C++:
//				string.substr(start, length) returns the substring starting at position "start" with length of "length"

int FindPattenConcatenations(const string& s, vector<string> words)
{
	int unit_size = words.front().size();
	int num_units = words.size();

	unordered_map<string, int> word_count;
	for(string w: words) {
		++word_count[w];
	}

	for(int i=0 ; i + num_units * unit_size <= (int)s.size() ; ++i )	// NOTE: the <= sign and not only <
	{
		unordered_map<string, int> current_count;
		for(int j=0 ; j < num_units ; ++j)
		{
			int start = i + j * unit_size;
			string sub = s.substr(start, unit_size);			// C++: extract substring
			++current_count[sub];
		}

		bool found_mismatch = false;
		for(auto it: current_count)
		{
			if(it.second != word_count[it.first])
			{
				found_mismatch = true;
				break;
			}
		}

		if(!found_mismatch)
			return i;
	}

	return -1;
}

int main()
{
	string sentence = "amanaplanacanal";
	vector<string> words = {"can", "apl", "ana"};
	cout << "Starting index: " << FindPattenConcatenations(sentence, words) << endl;

}
