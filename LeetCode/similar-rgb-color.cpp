/*
 * similar-rgb-color.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    int hextodecchar(char ch) {
        if(isdigit(ch)) {
            return ch - '0';
        } else if(isalpha(ch)) {
            return tolower(ch) - 'a' + 10;
        } else {
            return -1; // not a number
        }
    }
    int hextodec(string hexstr) {
    	stringstream ss;
    	ss << hexstr;
    	int dec;
    	ss >> std::hex >> dec;
    	return dec;
    }
    char dectohexchar(int num) {
        if(num <= 9 && num >= 0) {
            return '0' + num;
        } else if(num < 16) {
            return 'a' + (num - 10);
        } else {
            return 'x'; //not hex
        }
    }
    string dectohex(int num) {
    	stringstream ss;
    	ss << std::setw(2) << std::setfill('0') << std::hex << num;
    	return ss.str();
//        string ret="";
//        ret.reserve(2);
//        int lsb = num % 16;
//        int msb = num / 16;
//        ret += dectohexchar(msb);
//        ret += dectohexchar(lsb);
//        return ret;
    }

    int nearestsym(int a) {
        int lsb = a % 17;
        int floor = (a / 17) * 17 ;
        int ceiling = floor + 17;
        if(lsb <= 8) {
            return floor;
        } else {
            return ceiling;
        }
    }

public:
    string similarRGB(string color) {
        string r = color.substr(1,2);
        string g = color.substr(3,2);
        string b = color.substr(5,2);


        int ri = hextodec(r);
        int gi = hextodec(g);
        int bi = hextodec(b);

        ri = nearestsym(ri);
        gi = nearestsym(gi);
        bi = nearestsym(bi);

        string ret = "#";
        ret.reserve(7);
        ret += dectohex(ri);
        ret += dectohex(gi);
        ret += dectohex(bi);

        return ret;
    }
};

int main() {
	Solution obj;
	string a = obj.similarRGB("#65d09f");
	cout << a << endl; //"#66cc99"

	a = obj.similarRGB("#1c9e03");
	cout << a << endl; //"#229900"
}

