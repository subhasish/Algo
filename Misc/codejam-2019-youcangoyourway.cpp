/*
 * codejam-2019-youcangoyourway.cpp
 *
 *  Created on: Apr 8, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    for(int i=1 ; i<=n ; ++i) {
        int g;
    	string s;
        cin >> g >> s;
        for(size_t j=0 ; j<s.length() ; ++j) {
        	if(s[j] == 'E') {
        		s[j] = 'S';
        	} else {
        		s[j] = 'E';
        	}
        }
        cout << "Case #" << i << ": " << s << endl;
    }
}





