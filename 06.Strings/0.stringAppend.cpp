/*
 * 0.stringAppend.cpp
 *
 *  Created on: Nov 3, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;
using std::chrono::system_clock;

#define TESTLENGTH 100000000

void print_duration(const system_clock::time_point& start, const system_clock::time_point& stop) {
    using namespace std::chrono;
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << duration.count() << std::endl;
}

string FindAs(const string& A) {
	string out;
	out.reserve(A.size());		// Reserve
	auto start = system_clock::now();
	for(size_t i=0 ; i<TESTLENGTH ; ++i) {
		out += 'a';
	}
	auto stop = system_clock::now();
	print_duration(start, stop);
	out.shrink_to_fit();		// Shrink to fit
	return out;
}

int main() {
	FindAs("aaaaaaaaaaaaaaaaaaaaaaaaaaaaadddaaaa");
}

