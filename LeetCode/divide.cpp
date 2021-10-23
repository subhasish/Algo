/*
 * divide.cpp
 *
 *  Created on: May 29, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        int sign = (dividend < 0) ^ (divisor < 0);



        long long dend = abs(static_cast<long long>(dividend));
        long long dsor = abs(static_cast<long long>(divisor));

        cout << sign << "," << dend << "," << dsor << endl;

        int pow = 32;
        long long res = 0;
        long long dsor_pow = static_cast<long long>(dsor) << pow;
        while(dend >= dsor) {
            while(dend < dsor_pow) {
                dsor_pow >>= 1;
                --pow;
            }

            dend -= dsor_pow;
            res += (1ULL << pow);
        }
        cout << res << endl;

        if(sign) {
            res *= -1;
        }

        return (res > numeric_limits<int>::max()) ? numeric_limits<int>::max() : res;
    }
};

int main() {
	int a = -2147483648;
	int b = -1;

	Solution obj;

	cout << obj.divide(a,b) << endl;
}

