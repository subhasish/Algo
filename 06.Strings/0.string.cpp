/*
 * 0.string.cpp
 *
 *  Created on: Sep 24, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;


int main()
{
	string str = "Hello world!";
	string ins = "Pui";
	str.append(" Tito!");

	str.push_back(' ');
	str.push_back('A');
	str.push_back('m');
	str.push_back('r');
	str.pop_back();

	str.insert(str.begin()+19, 'S');
	//str.insert(str.begin()+19, "Saha"); //ERROR
	str.insert(str.begin()+11, ins.begin(), ins.end());

	str.insert(15, " Saha");
	str.insert(str.length(), " Saha");

	cout << str << endl;
	cout << "Length = " << str.length() <<endl;
	cout << "Size is same as length = " << str.size() << endl;

	string sub = str.substr(16,4);
	cout << "Sub-string of length 4 at position 16 = " << sub << endl;

	size_t found = str.find("Saha");
	if(found != string::npos) {
		cout << "First 'Saha' found at position = " << found << endl;
	} else {
		cout << "Sting 'Saha' not present" << endl;
	}

	found = str.find("Saha", found+1);
	if(found != string::npos) {
		cout << "String 'Saha' found at position = " << found << endl;
	} else {
		cout << "String 'Saha' not present after last position "  << endl;
	}

	found = str.find("Saha", found+1);
	if(found != string::npos) {
		cout << "String 'Saha' found at position = " << found << endl;
	} else {
		cout << "String 'Saha' not present after last position "  << endl;
	}

	str.replace(str.find("Saha"), 4, "Kumar");
	cout << "Saha replaced with Kumar: " << str << endl;


	string str1 ("green apple");
	string str2 ("red apple");
	if (str1.compare(str2) != 0)
	    std::cout << str1 << " is not " << str2 << '\n';
	if (str1.compare(6,5,"apple") == 0)
	    std::cout << "still, " << str1 << " is an apple\n";
	if (str1.compare(6,5,str2,4,5) == 0)
	    std::cout << "both are apples\n";

	const char* cStr = str.c_str();
	cout << "C string: " << cStr << endl;

	if(ins == "Pui") {
		cout << "Equality operator works!" << endl;
	} else {
		cout << "Equality operator does not work!" << endl;
	}
}


