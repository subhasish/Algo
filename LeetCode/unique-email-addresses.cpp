/*
 * unique-email-addresses.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

int numUniqueEmails(vector<string>& emails) {
	unordered_set<string> uniq;
	for(string& s: emails ) {
		size_t pos = s.find("@");
		string localname = s.substr(0, pos);
		string domain = s.substr(pos);
		localname = localname.substr(0, localname.find("+"));
		string final;
		final.reserve(s.size());
		for(char& c: localname) {
			if(c == '.') continue;
			final += c;
		}
		final += domain;
		cout << localname << "  " << final << endl;
		uniq.emplace(final);
	}
	return (int)uniq.size();
}


int main() {
	vector<string> email = {"test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"};
	cout << numUniqueEmails(email) << endl;
}
