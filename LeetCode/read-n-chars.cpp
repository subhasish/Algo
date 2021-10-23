/*
 * read-n-chars.cpp
 *
 *  Created on: Jan 27, 2019
 *      Author: subha
 */
#include <bits/stdc++.h>
using namespace std;

char arr[200] = "";
int fp=0;
// Forward declaration of the read4 API.
int read4(char *buf) {
	int count = 0;
	for(int i=fp ; i< (int)strlen(arr) && count<4 ; ++i) {
		buf[count++] = arr[i];
	}
	fp += count;
	return count;
}

class Solution {
    char t[4];
    int rd;
    int curr=0;
    bool eof = false;
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int c = 0;
        int rem = n;
        int to_read;

        if(eof && curr == rd) {
            return c;
        }

        while(rem > 0) {

            if(curr < rd) {
            	cout << "**" << curr << " " << rd << endl;
                buf[c++] = t[curr];
                ++curr;
                --rem;
                continue;
            }

            rd = read4(t);
            curr=0;

            to_read = min(rd, rem);
            for(int i=0 ; i<to_read ; ++i) {
                buf[c+i] = t[i];
                ++curr;
            }
            c += to_read;
            rem -= to_read;

            if(rd < 4) {
                eof = true;
                break;
            }
        }
        return c;
    }
};

int main()
{
	Solution obj;
	strcpy(arr, "abcsfsgrshdejgdbdrrhthrtjrjehwehjrertjrehwewewebg");
	char t[100] = "";

	vector<int> lens = {31,2,2,1,5,11,7,8,4,3,7,3,5,2,7};
	for(int i = 0; i< (int)lens.size() ; ++i) {

		int len = obj.read(t, lens[i]);

		if(len == 0) {
			cout << "EMPTY" << endl;
		}

		for(int i=0; i<len ; ++i) {
			cout << t[i] ;
		}
		cout << endl;

	}
}


