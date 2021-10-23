/*
 * HC.08.JustifyText.cpp
 *
 * Problem: Write a program that takes as input an array A of strings and a positive length L,
 * 			and compute the justification of the text specified by A.
 * 			Each line containing more than one word should not end in a blank and all the blanks
 * 			in a line should be evenly spaced out between words.
 *
 *  Created on: Nov 3, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Seems straightforward. Compute how many words will get into a line and then space out
//			the words evenly.

typedef vector<string> VS;

string JoinALineWithBlank(const VS& words, size_t start, size_t end, size_t num_blank);

VS JustifyText(const VS& words, size_t L) {
	VS result;
	size_t curr_line_start=0, num_words_curr_line=0, curr_line_length=0;

	for(size_t i=0 ; i<words.size() ; ++i) {
		//curr_line_start is the first word in the line and i is used to identify the last word
		++num_words_curr_line;
		size_t lookahead_line_length = curr_line_length + words[i].length() + (num_words_curr_line-1);
		if(lookahead_line_length == L) {
			result.emplace_back(JoinALineWithBlank(words,curr_line_start, i, num_words_curr_line-1));
			curr_line_length=0;
			num_words_curr_line=0;
			curr_line_start=i+1;
		} else if (lookahead_line_length > L) {
			result.emplace_back(JoinALineWithBlank(words,curr_line_start, i-1, L - curr_line_length));
			curr_line_length=words[i].length();
			num_words_curr_line=1;
			curr_line_start=i;
		} else {	// lookahead_line_length < L
			curr_line_length += words[i].length();
		}
	}

	// Handle last line.
	if(num_words_curr_line > 0) {
		result.emplace_back(JoinALineWithBlank(words, curr_line_start, words.size()-1, L-curr_line_length));
	}
	return result;
}

// Join strings in word[start, end] with num_blank blanks spaced evenly
string JoinALineWithBlank(const VS& words, size_t start, size_t end, size_t num_blank) {
	size_t num_words = end-start+1;
	string line;
	for(size_t i=start ; i<end ; ++i) {
		line += words[i];
		--num_words;
		size_t num_curr_blank = ceil(static_cast<double>(num_blank) / num_words);
		line.append(num_curr_blank, ' ');
		num_blank -= num_curr_blank;
	}
	line += words[end];
	return line;
}


int main() {
	VS A = {"The", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dogs"};
	VS result = JustifyText(A, 11);
	for(size_t i=0 ; i<result.size() ; ++i) {
		cout << result[i] << endl;
	}
}
