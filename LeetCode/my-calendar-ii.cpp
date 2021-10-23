/*
 * my-calendar-ii.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;




class MyCalendarTwo {
    map<int, int> p_map;



public:
    MyCalendarTwo() {

    }

    bool book(int start, int end) {

    	int start_count = 0;
    	auto p = p_map.lower_bound(start);
    	if(p != p_map.end() && p != p_map.begin() && p->first != start) {
    		--p;
    	}

    	if(p != p_map.end() && p->first <= start) {
    		start_count = p->second;
    	}

    	while(p != p_map.end() && p->first < end) {
    		if(p->second >= 2) {
    			return false;
    		}
    		++p;
    	}

    	auto s_it = p_map.find(start);
    	if(s_it == p_map.end()) {
    		p_map[start] = (++start_count);
    		s_it = p_map.find(start);
    	} else {
    		++p_map[start];
    		start_count=p_map[start];
    	}

    	p = next(s_it);
    	while(p != p_map.end() && p->first < end) {
    		++(p->second);
    		start_count = p->second;
    		++p;
    	}

    	auto e_it = p_map.find(end);
    	if(e_it == p_map.end()) {
    		p_map[end] = start_count-1;
    	}

    	cout << "After inserting interval: [" << start << ", " << end << "]" << endl;
    	for(auto it: p_map) {
    		cout << it.first << ": " << it.second << endl;
    	}

        return true;
    }
};

 //Your MyCalendarTwo object will be instantiated and called as such:
int main() {
	MyCalendarTwo obj;
	//[],[],[],[],[],[],[],[],[],[]
//	cout << obj.book(26,35) << endl; // returns true
//	cout << obj.book(26,32) << endl; // returns true
//	cout << obj.book(25,32) << endl; // returns true
//	cout << obj.book(18,26) << endl; // returns false
//	cout << obj.book(40,45) << endl; // returns true
//	cout << obj.book(19,26) << endl; // returns true
//	cout << obj.book(48,50) << endl;
//	cout << obj.book(1,6) << endl;
//	cout << obj.book(46,50) << endl;
//	cout << obj.book(11,18) << endl;

//	cout << obj.book(47,48) << endl;
//	cout << obj.book(27,28) << endl;
//	cout << obj.book(40,41) << endl;
//	cout << obj.book(47,48) << endl;
//	cout << obj.book(77,78) << endl;
//	cout << obj.book(77,78) << endl;
//	cout << obj.book(77,78) << endl;
//	cout << obj.book(47,48) << endl;
	cout << obj.book(21,22) << endl;
	cout << obj.book(86,87) << endl;
	cout << obj.book(71,72) << endl;
	cout << obj.book(76,77) << endl;
	cout << obj.book(50,51) << endl;
	cout << obj.book(92,93) << endl;
	cout << obj.book(99,100) << endl;
	cout << obj.book(5,6) << endl;
	cout << obj.book(71,72) << endl;
	cout << obj.book(42,43) << endl;
	cout << obj.book(72,73) << endl;
	cout << obj.book(22,23) << endl;
	cout << obj.book(51,52) << endl;
	cout << obj.book(15,16) << endl;
	cout << obj.book(70,71) << endl;
	cout << obj.book(64,65) << endl;
	cout << obj.book(57,58) << endl;
	cout << obj.book(47,48) << endl;
	cout << obj.book(4,5) << endl;
	cout << obj.book(14,15) << endl;
	cout << obj.book(2,3) << endl;
	cout << obj.book(28,29) << endl;
	cout << obj.book(35,36) << endl;
	cout << obj.book(86,87) << endl;
	cout << obj.book(72,73) << endl;
	cout << obj.book(99,100) << endl;
	cout << obj.book(50,51) << endl;
	cout << obj.book(25,26) << endl;
	cout << obj.book(8,9) << endl;
	cout << obj.book(69,70) << endl;
	cout << obj.book(37,38) << endl;
	cout << obj.book(55,56) << endl;
	cout << obj.book(0,1) << endl;
	cout << obj.book(20,21) << endl;
	cout << obj.book(21,22) << endl;
	cout << obj.book(96,97) << endl;
	cout << obj.book(88,89) << endl;
	cout << obj.book(40,41) << endl;
	cout << obj.book(20,21) << endl;
	cout << obj.book(94,95) << endl;
	cout << obj.book(99,100) << endl;
	cout << obj.book(19,20) << endl;
	cout << obj.book(41,42) << endl;
	cout << obj.book(0,1) << endl;
	cout << obj.book(47,48) << endl;
	cout << obj.book(51,52) << endl;
	cout << obj.book(62,63) << endl;
	cout << obj.book(32,33) << endl;
	cout << obj.book(83,84) << endl;
	cout << obj.book(39,40) << endl;
	cout << obj.book(70,71) << endl;
	cout << obj.book(36,37) << endl;
	cout << obj.book(16,17) << endl;
	cout << obj.book(63,64) << endl;
	cout << obj.book(32,33) << endl;
	cout << obj.book(35,36) << endl;
	cout << obj.book(57,58) << endl;
	cout << obj.book(68,69) << endl;
	cout << obj.book(24,25) << endl;
	cout << obj.book(73,74) << endl;
	cout << obj.book(94,95) << endl;
	cout << obj.book(32,33) << endl;

}

