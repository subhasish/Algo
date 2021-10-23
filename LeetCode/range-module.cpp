/*
 * range-module.cpp
 *
 *	https://leetcode.com/problems/range-module/
 *
 *
 *  Created on: Jan 24, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class RangeModule {
    struct Range {
        int l, r;
    };
    vector<Range> arr;

    bool IsRightHigherThanLeftOfQuery(const Range& a, const Range& b) {
        return a.r >= b.l;
    }
    bool HasOverlap(const Range& a, const Range& b) {
        return a.r >= b.l && b.r >= a.l;
    }
    bool HasExclusiveOverlap(const Range& a, const Range& b) {
    	return a.r > b.l && b.r > a.l;
    }
    bool Contains(const Range& a, const Range& b) {
    	return a.l <= b.l && a.r >= b.r;
    }

    //
    int findFirstOverlapOrAtRight(const Range& a, bool& hasOverlap) {
        int lo = 0, hi = arr.size()-1;
        if(hi < 0) {
            hasOverlap = false;
            return -1;
        }

        while(lo < hi) {
            int mid = lo + (hi-lo)/2;

            if(IsRightHigherThanLeftOfQuery(arr[mid], a)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        if(!IsRightHigherThanLeftOfQuery(arr[lo], a)) {
            hasOverlap = false;
            return -1;
        } else {
            hasOverlap = HasOverlap(arr[lo], a);
            return lo;
        }
    }

    Range MergeTwoRanges(const Range& a, const Range& b) {
    	Range r = Range{a.l, a.r};
    	if(HasOverlap(a, b)) {
    		r.l = min(r.l, b.l);
    		r.r = max(r.r, b.r);
    	}
    	return r;
    }

public:
    RangeModule() {

    }

    void addRange(int left, int right) {
    	Range t = Range{left, right};
    	bool hasOverlap;
    	int right_hi_index = findFirstOverlapOrAtRight(t, hasOverlap);
    	if(!hasOverlap) {
    		if(right_hi_index == -1) {  //no such; add to end
    			arr.insert(arr.end(), t);
    		} else {
    			arr.insert(arr.begin()+right_hi_index, t);
    		}
    	} else {
    		int p = right_hi_index;
    		Range m = t;
    		while (p < (int)arr.size() && HasOverlap(arr[p], t)) {
    			m = MergeTwoRanges(arr[p], m);
    			++p;
    		}
    		for(int i=p ; i > right_hi_index ; --i) {
    			arr.erase(arr.begin()+(i-1));
    		}
    		arr.insert(arr.begin() + right_hi_index, m);
    	}
    }

    bool queryRange(int left, int right) {
    	Range t = Range{left, right};
    	bool hasOverlap;
    	int right_hi_index = findFirstOverlapOrAtRight(t, hasOverlap);
    	if(!hasOverlap) {
    		return false;
    	}
    	if(Contains(arr[right_hi_index], t)) {
    		return true;
    	}
    	if(right_hi_index < ((int)arr.size()-1) && Contains(arr[right_hi_index+1], t)) {
    		return true;
    	}
    	return false;
    }

    void removeRange(int left, int right) {
    	Range t = Range{left, right};
    	bool hasOverlap;
    	int right_hi_index = findFirstOverlapOrAtRight(t, hasOverlap);
    	if(!hasOverlap) {
    		return;
    	}
    	int p = right_hi_index;
    	Range start = arr[p];
    	Range last = arr[p];
    	while(p < (int)arr.size() && HasExclusiveOverlap(t, arr[p])) {
    		last = arr[p];
    		arr.erase(arr.begin()+p);
    	}

    	if(last.r > t.r) {
    		last.l = t.r;
    		arr.insert(arr.begin()+p, last);
    	}
    	if(start.l < t.l) {
    		start.r = t.l;
    		arr.insert(arr.begin()+p, start);
    	}

    }

    void displayRanges() {
    	for(const Range& r: arr) {
    		cout << "[" << r.l << "," << r.r << "]" << endl;
    	}
    	cout << "End" << endl;
    }
};



int main() {
	RangeModule obj;
//	obj.addRange(10,20);
//	obj.removeRange(14,16);
//	obj.displayRanges();
//
//	cout << "Q [10,14] : " << obj.queryRange(10,14) << endl;
//	cout << "Q [13,15] : " << obj.queryRange(13,15) << endl;
//	cout << "Q [16,17] : " << obj.queryRange(16,17) << endl;
//
//	obj.addRange(30, 40);
//	obj.displayRanges();
//
//	obj.removeRange(12,33);
//	obj.displayRanges();
//
//	obj.removeRange(1,3);
//	obj.displayRanges();
//
//	obj.removeRange(43,55);
//	obj.displayRanges();

	//["RangeModule","addRange","queryRange","removeRange","removeRange","addRange","queryRange","addRange","queryRange","removeRange"]
//	[[],[5,8],[3,4],[5,6],[3,6],[1,3],[2,3],[4,8],[2,3],[4,9]]
//	obj.addRange(5,8);
//	cout << obj.queryRange(3,4) << endl;
//	obj.removeRange(5,6);
//	obj.removeRange(3,6);
//	obj.addRange(1,3);
//	cout << obj.queryRange(2,3) << endl;
//	obj.addRange(4,8);
//	cout << obj.queryRange(2,3) << endl;
//	obj.removeRange(4,9);

	obj.addRange(55,62);
	obj.addRange(1,29);
	obj.removeRange(18,49);
	cout << obj.queryRange(6,98) << endl;
	cout << obj.queryRange(59,71) << endl;
	obj.removeRange(40,45);
	obj.removeRange(4,58);
	obj.removeRange(57,69);
	obj.removeRange(20,30);
	obj.removeRange(1,40);
	cout << obj.queryRange(73,93) << endl;
	obj.removeRange(32,93);
	obj.addRange(38,100);
	obj.removeRange(50,64);
	obj.addRange(26,72);
	cout << obj.queryRange(8,74) << endl;
	cout << obj.queryRange(15,53) << endl;
	obj.addRange(44,85);
	obj.addRange(10,71);
	cout << obj.queryRange(54,70) << endl;
	obj.removeRange(10,45);
	cout << obj.queryRange(30,66) << endl;
	obj.addRange(47,98);
	cout << obj.queryRange(1,7) << endl;
	obj.removeRange(44,78);
	obj.removeRange(31,49);
	obj.addRange(62,63);
	obj.addRange(49,88);
	obj.removeRange(47,72);
	obj.removeRange(8,50);
	obj.removeRange(49,79);
	obj.addRange(31,47);
	obj.addRange(54,87);
	cout << obj.queryRange(77,78) << endl;
	cout << obj.queryRange(59,100) << endl;
	cout << obj.queryRange(8,9) << endl;
	cout << obj.queryRange(50,51) << endl;
	cout << obj.queryRange(67,93) << endl;
	obj.removeRange(25,86);
	obj.removeRange(8,92);
	cout << obj.queryRange(31,87) << endl;
	obj.addRange(90,95);
	obj.addRange(28,56);
	obj.addRange(10,42);
	cout << obj.queryRange(27,34) << endl;
	obj.addRange(75,81);
	obj.addRange(17,63);
	obj.removeRange(78,90);
	obj.addRange(9,18);
	cout << obj.queryRange(51,74) << endl;
	obj.removeRange(20,54);
	obj.addRange(35,72);
	cout << obj.queryRange(2,29) << endl;
	obj.addRange(28,41);
	obj.addRange(17,95);
	obj.addRange(73,75);
	cout << obj.queryRange(34,43) << endl;
	obj.addRange(57,96);
	cout << obj.queryRange(51,72) << endl;
	obj.removeRange(21,67);
	obj.removeRange(40,73);
	obj.removeRange(14,26);
	obj.removeRange(71,86);
	cout << obj.queryRange(34,41) << endl;
	obj.removeRange(10,25);
	cout << obj.queryRange(27,68) << endl;
	cout << obj.queryRange(18,32) << endl;
	obj.removeRange(30,31);
	cout << obj.queryRange(45,61) << endl;
	obj.addRange(64,66);
	obj.addRange(18,93);
	cout << obj.queryRange(13,21) << endl;
	obj.removeRange(13,46);
	obj.removeRange(56,99);
	cout << obj.queryRange(6,93) << endl;
	obj.addRange(25,36);
	obj.removeRange(27,88);
	obj.removeRange(82,83);
	obj.addRange(30,71);
	obj.addRange(31,73);
//	obj.displayRanges();	//DISPLAY
	obj.addRange(10,41);
//	obj.displayRanges();	//DISPLAY
	cout << obj.queryRange(71,72) << endl;
	cout << obj.queryRange(9,56) << endl; //Wrong
	obj.addRange(22,76);
	cout << obj.queryRange(38,74) << endl;
	obj.removeRange(2,77);
	cout << obj.queryRange(33,61) << endl;
	obj.removeRange(74,75);
	obj.addRange(11,43);
	cout << obj.queryRange(27,75) << endl;



	return 0;
}
