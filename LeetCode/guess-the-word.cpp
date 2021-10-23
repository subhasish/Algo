/*
 * guess-the-word.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

int match_score(const string& s1, const string& s2);


// This is the Master's API interface.
// You should not implement it, or speculate about its implementation
class Master {
  public:
	unordered_set<string> word_set;
	string secret;

    int guess(string word) {
    	cout << "Guessed word: " << word ;
    	if(word_set.find(word) == word_set.end()) {
    		cout << ", score = -1" << endl;
    		return -1;

    	}
    	int m = match_score(word, secret);
    	cout << ", score = " << m << endl;
    	return m;
    }
};


int match_score(const string& s1, const string& s2) {
	int match = 0;
	for(size_t i = 0 ; i < s1.length() ; ++i) {
		if(s1[i] == s2[i]) {
			++match;
		}
	}
	return match;
}


class Solution {
	string getRandomString(const unordered_set<string>& ws) {
		srand(time(NULL));
		int r = (int) rand() % ws.size();
		auto it = ws.begin();

		for( ; it != ws.end() && r>0 ; ++it, --r) {

		}
		if(it != ws.end()) {
			return *it;
		} else {
			return *(ws.begin());
		}
	}

public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        unordered_set<string> ws;       //Set of candidates
        for(const string& s: wordlist) {
            ws.emplace(s);
        }

        for(int i = 0 ; i < 10 && !ws.empty() ; ++i) {
            //string guess_word = *(ws.begin());  //Pick the first word, pseudo random!!
        	string guess_word = getRandomString(ws);

//        	cout << "At round: " << (i+1) << ", word: " << guess_word << ", among total word count " << ws.size() << endl;

            int match = master.guess(guess_word);

            ws.erase(guess_word);

            if(match == (int)guess_word.length()) {    // All 6 charaters matched!
                break;
            } else {
                vector<string> to_remove;
                for(const string& s: ws) {          //All words with different match score are not the answer
                    int m = match_score(s, guess_word);
                    if(m != match) {
                        to_remove.emplace_back(s);
                    }
                }
                for(const string& s: to_remove) {   //Remove words that are not possible
                    ws.erase(s);
                }
            }
        }
    }
};

int main() {
	vector<string> A = {"pzrooh","aaakrw","vgvkxb","ilaumf","snzsrz","qymapx","hhjgwz","mymxyu","jglmrs","yycsvl","fuyzco","ivfyfx","hzlhqt","ansstc","ujkfnr","jrekmp","himbkv","tjztqw","jmcapu","gwwwmd","ffpond","ytzssw","afyjnp","ttrfzi","xkwmsz","oavtsf","krwjwb","bkgjcs","vsigmc","qhpxxt","apzrtt","posjnv","zlatkz","zynlqc","czajmi","smmbhm","rvlxav","wkytta","dzkfer","urajfh","lsroct","gihvuu","qtnlhu","ucjgio","xyycvd","fsssoo","kdtmux","bxnppe","usucra","hvsmau","gstvvg","ypueay","qdlvod","djfbgs","mcufib","prohkc","dsqgms","eoasya","kzplbv","rcuevr","iwapqf","ucqdac","anqomr","msztnf","tppefv","mplbgz","xnskvo","euhxrh","xrqxzw","wraxvn","zjhlou","xwdvvl","dkbiys","zbtnuv","gxrhjh","ctrczk","iwylwn","wefuhr","enlcrg","eimtep","xzvntq","zvygyf","tbzmzk","xjptby","uxyacb","mbalze","bjosah","ckojzr","ihboso","ogxylw","cfnatk","zijwnl","eczmmc","uazfyo","apywnl","jiraqa","yjksyd","mrpczo","qqmhnb","xxvsbx"};
	Master m;
	m.secret = "anqomr";
	unordered_set<string> ws;
	for(const string& s: A) {
		ws.emplace(s);
	}
	m.word_set = ws;

	Solution obj;
	obj.findSecretWord(A, m);

}
