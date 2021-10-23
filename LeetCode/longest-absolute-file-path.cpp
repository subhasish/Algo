/*
 * longest-absolute-file-path.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: subha
 */

/*
 * NOTE: \n \t all count as 1 character while string processing
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {

public:
    int lengthLongestPath(string input) {
        size_t pos=0, oldpos=0;

        stack<int> st;	//stores the length of the path upto current directory
        st.push(0);

        int level = 0;
        size_t tpos=0;
        int curr_level = 0;
        int max_len = 0;

        while(oldpos != string::npos && pos != string::npos) {
        	pos = input.find("\n", oldpos);
            string a = input.substr(oldpos, pos-oldpos);

            bool is_file = (a.find(".") != string::npos);

            tpos = 0;
            curr_level = 0;
            string name = a;

            while((tpos = a.find("\t", tpos)) != string::npos) {
            	++curr_level;
            	tpos += 1;
            	name = a.substr(tpos);
            }

//            cout << name << " at level " << curr_level << endl;


            while(level > curr_level) {
            	st.pop();
            	--level;
            }

//            cout << "parent level = " << level << ", length upto parent = " << st.top() << endl;

            int current_len = (int)(st.top() + name.length() + (level > 0 ? 1 : 0));
            if(is_file) {
            	max_len = max(max_len, current_len);
            } else {
            	++level;
            	st.push(current_len);
            }

//            cout << a << endl;

            oldpos = pos+1;
        }
        return max_len;
    }
};


int main() {
	Solution obj;
	string s = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
	cout << obj.lengthLongestPath(s) << endl;
}

