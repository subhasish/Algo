/*
 * palindrome-number.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(int x) {
    if(x < 0) {
        return false;
    }
    if(x == 0) {
        return true;
    }
    int digits = floor(log10(x))+1;

    //Cannot work

    int msb_mask = (int) pow(10, digits-1);
    while(msb_mask>=10) {
        int msb = x/msb_mask;
        int lsb = x%10;
        if(msb != lsb) {
            return false;
        }
        x %= msb_mask;
        x /= 10;
        msb_mask /= 100;
    }
    return true;
}

int main()
{
	cout << isPalindrome(121) << endl;
	cout << isPalindrome(-121) << endl;
	cout << isPalindrome(10) << endl;
	cout << isPalindrome(102323201) << endl;
	cout << isPalindrome(1000101) << endl;
	cout << isPalindrome(100010001) << endl;
}

