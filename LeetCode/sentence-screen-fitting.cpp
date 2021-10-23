/*
 * sentence-screen-fitting.cpp
 *
 *  Created on: May 28, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    pair<int, int> fromHere (const vector<string>& sentence, int cols, int start, int total) {
        int count = 0;
        int words = 0;
        int size = sentence.size();


        if(cols >= total + 1) {
            count += (cols / (total + 1));
            cols %= (total + 1);
        }

        if(cols >= total) {
            count += 1;
            cols -= total;

            --cols; // last space
        }

        while(cols >= (int)sentence[(start + words) % size].length()) {
            cols -= sentence[(start + words) % size].length();
            ++words;
            --cols; // space;
        }

        int next_word = (start + words) % size;
        return make_pair(count, next_word);
    }

public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int maxLen = 0;
        for(auto s: sentence) {
            maxLen = max(maxLen, (int)s.length());
        }
        if(maxLen > cols) {
            return 0;
        }

        int total = 0;
        for(string& s: sentence) {
            total += s.length();
        }
        total += (sentence.size() - 1);

        vector<pair<int,int>> mm(sentence.size());
        int size = sentence.size();

        for(int i = 0; i < size ; ++i) {
            mm[i] = fromHere(sentence, cols, i, total);
        }

        int last = 0;
        int count = 0;
        int carry = 0;
        for(int i = 0 ; i < rows ; ++i) {
            pair<int,int> p = mm[last];
            count += p.first;

            if(last != p.second) {
                carry += (last < p.second) ? (p.second - last) : (size + p.second - last);
                if(carry >= size) {
                    ++count;
                    carry %= size;
                }

                last = p.second;
            }

        }

        return count;
    }
};


int main() {
	Solution obj;

	vector<string> A;
	int r, c;

	A = {"a", "bcd", "e"};
	r = 2;
	c = 20;

	cout << obj.wordsTyping(A, r, c) << endl;
}


