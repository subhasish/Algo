/*
 * swap-adjacent-in-lr-string.cpp
 *
 *  Created on: Feb 2, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;


//Exploring BFS graph takes time proportional to the graph size.
//Here different possible strings is in the order of factorial. So takes BSF takes too much time.
class SolutionGraph {
    unordered_set<string> checked;
public:
    bool canTransform(string start, string end) {
        if(start == end) {
            return true;
        }
        if(checked.find(start) != checked.end()) {
            return false;
        }

        size_t pos = 0;
        while((pos = start.find("XL", pos)) != string::npos) {
        	string s1 = start;
            s1.replace(pos, 2, "LX");
            pos +=2;
            if(canTransform(s1, end)) {
                return true;
            }
        }

        pos = 0;
        while((pos = start.find("RX", pos)) != string::npos) {
        	string s2 = start;
        	s2.replace(pos, 2, "XR");
            pos +=2;
            if(canTransform(s2, end)) {
                return true;
            }
        }

        checked.emplace(start);
        return false;
    }
};


// Let's think of 'L' and 'R' as people facing left and right standing on one line,
// and 'X' as an empty space on that line.
//
// One invariant is that 'L' and 'R' characters in the string can never cross each other.
// People walking on the line cannot pass through each other. That means the starting and
// target strings must be the same when reading only the 'L' and 'R's.
//
// Additionally ith L ins start must appear at or after ith L in target as L only can move
// left. Similarly R in start must appear at or before ith R in target as R can only move right.

class Solution {
    string getCanonical(string str) {
        for(size_t i=0; i<str.length() ; ++i) {
        	if(str[i] == 'X') {
        		str.erase(str.begin()+i);
        		--i;
        	}
        }
        return str;
    }
public:
    bool canTransform(string start, string end) {
    	if(start.length() != end.length()) {
    		return false;
    	}
    	if(getCanonical(start) != getCanonical(end)) {
    		return false;
    	}

    	int i = 0, j = 0;
    	while(i != (int)start.length() && j != (int)end.length() ) {
    		while(start[i] == 'X') {
    			++i;
    		}
    		while(end[j] == 'X') {
    			++j;
    		}

    		if(i == (int)start.length() && j == (int)end.length()) {
    			return true;
    		}
    		if(i == (int)start.length() || j == (int)end.length()) {
    			return false;
    		}

    		if(start[i] != end[j]) {
    			return false;
    		}

    		if(start[i] == 'L' && i < j) {
    			return false;
    		}

    		if(start[i] == 'R' && i > j) {
    			return false;
    		}
    		++i;
    		++j;
    	}


    	return true;
    }
};



int main() {
	string start = "XXXXXXRXXLXRXXXXXRXXXXXRXXXXXLXXXLXLXXRXXXXXLXXXXX";
	string end = "XXRXXXXLXXRXXXRXXXXRXXXXXLXXLXXXXXXLXXXXRXXXXLXXXX";

	bool ret = Solution().canTransform(start, end);
	cout << ret << endl;

	start = "RXXLRXRXL";
	end = "XRLXXRRLX";
	ret = Solution().canTransform(start, end);
	cout << ret << endl;

	start = "XXXLXXXXXX";
	end = "XXXLXXXXXX";
	ret = Solution().canTransform(start, end);
	cout << ret << endl;

    return 0;
}

