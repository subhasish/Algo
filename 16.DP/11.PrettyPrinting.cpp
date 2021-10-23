/*
 * 11.PrettyPrinting.cpp
 *
 * Problem: Given text decompose the text into lines such that no word is split across lines and
 * 			the sum of the squares of the whitespace after each each line is minimized.
 *
 * Variant 1:
 * 			Order of the string does not matter
 * Variant 2:
 * 			Penalty for space b is only b and not b^2.
 *
 *  Created on: May 12, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			One thing is clear is that greedy will not work. Keeping more space in one line can
//			can result in lesser space in following lines. So we need to consider all possible
//			scenarios.
//
//			Also optimal solution for i words may not have optimal solution for (i-1) words.
//			However, if in the optimal placement of i words, last line consists of words
//			j,j+1,..,i then first j-1 words must be placed optimally.
//
//			So the recurrence would be like M(i) = min {f(j,i) + M(j-1)} where
//			M(i) is the optimal solution for i words and f(j,i) is the penalty for putting
//			word j to word i in a single line.
//
// Variant 1:
//			The line length can be thought as bucket capacity and string lengths can be thought
//			as volume of balls. But they have to go in sequence. Without the sequence it is greedy.
//
// Variant 2:
//			Does not matter if one line has more space or not. If we minimize the number of lines
//			then we minimize the number of total whitespace as size of the words is constant.
//			Also minimum line means more space between words, so less penalty.
//
// Time complexity:
//			O(nL) as a line cannot have more than L words

int PrettyPrintingMinMess(const vector<string>& para, int Lmax)
{
	// DP[i] stores the minimum messiness of placing word[0..i]
	vector<int> DP(para.size(), numeric_limits<int>::max());

	//Base case: for placing 0th word
	DP[0] = (Lmax - para[0].length()) * (Lmax - para[0].length());

	for(size_t i=1 ; i < para.size() ; ++i) {											  // O(n)
		int remainin_blank = Lmax - para[i].size();
		int min_mess = remainin_blank * remainin_blank + DP[i-1];

		for(int j = i-1 ; j>=0 ; --j) {						// Now try adding more word   // O(L)
			remainin_blank -= (para[j].length() + 1);
			if(remainin_blank < 0) {						// No more space
				break;
			}

			int j_1_mess = (j-1 < 0) ? 0 : DP[j-1];
			int curr_line_mess = remainin_blank * remainin_blank;

			if(min_mess > curr_line_mess + j_1_mess) {
				min_mess = curr_line_mess + j_1_mess;
			}
		}

		DP[i] = min_mess;
	}

	return DP[para.size()-1];
}


int main()
{
	vector<string> para1 = {
			"I", "have", "inserted", "a", "large", "number", "of", "new",
			"examples", "from", "the", "papers", "for", "the", "Mathematical",
			"Tripos", "during", "the", "last", "twenty", "years,", "which", "should",
			"be", "useful", "to", "Cambridge", "students."
	};

	cout << "Minimum messiness of the paragraph = " << PrettyPrintingMinMess(para1, 36) << endl;

	vector<string> para2 = {
			"a", "b", "c", "d"
	};

	cout << "Minimum messiness of the paragraph = " << PrettyPrintingMinMess(para2, 5) << endl;
}
