/*
 * HC.30.DefectiveJugs.cpp
 *
 * Problem: You have three measuring jugs that can only say that volume of item is in range [l,r],
 * 			but cannot say for sure what is the actual volume. Now for one recipe we need to have
 * 			milk of volume between L and R.
 *
 * 			Write a program that determines if there exists a sequence of steps by which the
 * 			required amount of milk can be obtained using the defective jugs.
 *
 *  Created on: Jan 3, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			To me it is a complex version of the coin change problem. In coin change problem we
//			tried to find the combination of the coins such that sum is a single target value.
//			Here we have a range instead of a single value.
//			Also another difference is that there we tried to count all possible combinations, and
//			here we are only concerned if there exists any such combination.
//
//			Base case is if the range of the jug totally falls inside the range we are
//			trying to measure then return true.
//
//			For finding any combination, search is easy, for each jugs continuously try to see if
//			there exists a solution containing one measurement using that jug. Then we can
//			recursively use again for new set of measurements.
//
//			For recursive logic, if we are trying to see if [L,R] can be measured using a jug of [l,r],
//			then that should be possible if [L-l, R-r] has a feasible solution.
//
//			To speed up computation, we can keep storing the ranges that do not have a feasible solution.
//			We do not need to store ranges that has a solution, as we can directly return.

struct VolumeRange {
	int low, high;

	// operator== to make a set of these VolumeRanges
	bool operator== (const VolumeRange& that) const {
		return low == that.low && high == that.high;
	}
};

struct HashVolumeRange {
	size_t operator() (const VolumeRange& obj) const {
		return hash<int>()(obj.low) ^ hash<int>()(obj.high);
	}
};

bool IsPossibleToMeasureWCaching(int lo, int hi, const vector<VolumeRange>& jugs,
								 unordered_set<VolumeRange, HashVolumeRange>& impossible_ranges);

bool IsPossibleToMeasure(const VolumeRange& target, const vector<VolumeRange>& jugs) {
	// Use helper function to do the caching
	unordered_set<VolumeRange, HashVolumeRange> impossible_solutions;
	return IsPossibleToMeasureWCaching(target.low, target.high, jugs, impossible_solutions);
}

bool IsPossibleToMeasureWCaching(int lo, int hi, const vector<VolumeRange>& jugs,
								 unordered_set<VolumeRange, HashVolumeRange>& impossible_ranges) {
	//check if target makes sense
	if(lo > hi || (hi<0 && lo<0)) return false;

	//check if it is already found as impossible solution
	if(impossible_ranges.find(VolumeRange{lo, hi}) != impossible_ranges.end()) return false;


	for(const VolumeRange& jug: jugs) {
		//Base case
		if(lo <= jug.low && hi >= jug.high) {
			return true;
		}

		//Recursive case
		if(IsPossibleToMeasureWCaching(lo-jug.low, hi-jug.high, jugs, impossible_ranges)) {
			return true;
		}
		// can also print from here which jugs were in the solution
	}

	// If no solution possible for this volume range [lo, hi] then cache the finding
	impossible_ranges.emplace(VolumeRange{lo, hi});
	return false;
}

int main() {
	VolumeRange target1 = VolumeRange{10, 11};
	VolumeRange target2 = VolumeRange{10, 12};
	VolumeRange target3 = VolumeRange{20, 35};
	vector<VolumeRange> jugs = { VolumeRange{1,2}, VolumeRange{5,6}};

	cout << "Possible: " << IsPossibleToMeasure(target1, jugs) << endl;
	cout << "Possible: " << IsPossibleToMeasure(target2, jugs) << endl;
	cout << "Possible: " << IsPossibleToMeasure(target3, jugs) << endl;

}
