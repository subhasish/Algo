/*
 * next-closest-time.cpp
 *
 *  Created on: Feb 9, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    int nextInt(int a, int limit, const vector<int>& A) {
        for(int i = a+1 ; i <= limit ; ++i) {
            int lsb = i%10;
            int msb = i/10;
            if(A[lsb] == 1 && A[msb] == 1) {
                return i;
            }
        }
        int min_r = a/10;
        for(size_t i=0; i<A.size() ; ++i) {
            if(A[i] == 1) {
                min_r = i;
                break;
            }
        }
        return min_r * 10 + min_r;
    }
public:
    string nextClosestTime(string time) {
        unordered_set<int> all_set;
        for(const char& c: time) {
            if(isdigit(c)) {
                all_set.emplace(c-'0');
            }
        }
        vector<int> present(10, 0);
        for(const int& i: all_set) {
            present[i] = 1;
        }

        string ret = time;
        int lsb = time[4] - '0';
        int msb = time[3] - '0';
        int minutes = msb * 10 + lsb;
        int next_min = nextInt(minutes , 59, present);

        ret[3] = next_min / 10 + '0';
        ret[4] = next_min % 10 + '0';

        if(next_min <= minutes) {
            lsb = time[1] - '0';
            msb = time[0] - '0';
            int hours = msb * 10 + lsb;
            int next_hour = nextInt(hours , 23, present);

            ret[0] = next_hour / 10 + '0';
            ret[1] = next_hour % 10 + '0';
        }

        return ret;
    }
};

int main() {
	Solution obj;
	string t = "13:55";

	cout << obj.nextClosestTime(t) << endl;
}

