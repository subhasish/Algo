/*
 * codejam-2019-foregone.cpp
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
        string s;
        cin >> s;
        string a="", b="";
        bool b_started = false;
        for(auto c: s) {
            if(c == '4') {
                a += '2';
                b += '2';
                b_started = true;
            } else {
                a += c;
                if(b_started) {
                    b += '0';
                }
            }
        }

        cout << "Case #" << i << ": " << a << " " << b << endl;
    }
}


