/*
 * find-and-replace-in-string.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
        int len = 0;
        for(string& t: targets) {
            len += t.length();
        }
        map<int, string> ordered;
        unordered_map<int, string> s_map;
        map<int, string> ord_out;
        for(int i=0 ; i< (int)indexes.size() ; ++i) {
            ordered[indexes[i]] = targets[i];
            s_map[indexes[i]] = sources[i];
        }

        string res = "";
        res.reserve(len + S.length()); //max length
        for(size_t i=0 ; i<S.length() ; ++i) {
            if(!ordered.empty() && ordered.begin()->first == (int)i) {
            	string sub = S.substr(i,s_map[ordered.begin()->first].length());
            	string org = s_map[ordered.begin()->first];

            	//cout << i << ": " <<sub << " " << org << endl;
            	if(sub == org) {
                    res += ordered.begin()->second;
                    i += (s_map[ordered.begin()->first].length() - 1);

            	} else {
            		res += S[i];
            	}
            	ordered.erase(ordered.begin());
        	} else {
        		res += S[i];
        	}
        }

        return res;
    }
};

int main() {
	Solution obj;
	string s = "mhnbzxkwzxtaanmhtoirxheyanoplbvjrovzudznmetkkxrdmr";
	vector<int> indices = {46,29,2,44,31,26,42,9,38,23,36,12,16,7,33,18};
	vector<string> originals = {"rym","kv","nbzxu","vx","js","tp","tc","jta","zqm","ya","uz","avm","tz","wn","yv","ird"};
	vector<string> targets = {"gfhc","uq","dntkw","wql","s","dmp","jqi","fp","hs","aqz","ix","jag","n","l","y","zww"};

	string res = obj.findReplaceString(s, indices, originals, targets);

	cout << res << endl;
}
