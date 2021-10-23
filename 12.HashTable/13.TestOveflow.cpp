/*
 * 13.TestOveflow.cpp
 *
 * Problem: Testing overflow for multiplication
 *
 *  Created on: Mar 1, 2018
 *      Author: subha
 */

#include<bits/stdc++.h>

using namespace std;

typedef unsigned long long ULL;

// Main Findings: In case of overflow the result is undefined according to standard. Compiler can do whatever it want.
//				  So no point checking after. Check before the operation like
//				  https://stackoverflow.com/questions/1815367/multiplication-of-large-numbers-how-to-catch-overflow

// Function to demangle the c++ type names output by typeid(type).name()
//std::string demangle(const char* name);

void MultiplyWithOverflowHandling(ULL a, ULL b) {
	ULL mult = a * b;
	if(b == 0 || mult / b == a) {
		cout << "Multiplying " << a << " and " << b << " = " << mult << endl;
	} else {
		cout << "Overflow occurred while multiplying " << a << " and " << b << endl;
	}
}

int main()
{
	int digits10 = numeric_limits<ULL>::digits10;
	int digits = numeric_limits<ULL>::digits;

	//cout << "type info = " << demangle(typeid(ULL).name()) << endl;
	cout << "binary digits without sign bit = " << digits << endl;
	cout << "digits in base 10 = " << digits10 << endl;

	string sixes = "6";
	for(int i=0 ; i<17 ; i++) {
		sixes += "6";
	}
	stringstream ss(sixes);
	ULL sxNum;
	ss >> sxNum;
	cout << sxNum << endl;

	MultiplyWithOverflowHandling(sxNum, 3000);
	MultiplyWithOverflowHandling(sxNum, 3);

}



/*
#include <cxxabi.h>
std::string demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name ;
}
*/
