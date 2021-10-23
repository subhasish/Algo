/*
 * 04.ShortestEquvalentPath.cpp
 *
 * Problem: Given a Unix path in non normalized form give the normalized shortest equivalent path
 * 			Example: scripts//./../scripts/awk/././ should give scripts/awk
 *
 *  Created on: Jan 2, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Keep the path in stack. '..' should pop. '.' and extra '/' should be ignored.

string ShortestEquivalentPath(string path)
{
	if(path.empty()) {
		throw invalid_argument("Empty string is not a valid path.");
	}

	// stack<string> pathStack; // Not using stack so that path can be printed easily
	vector<string> pathStack;

	if(path[0] == '/') {
		//absolute path
		pathStack.push_back("/");
	}

	stringstream ss(path);
	string token;
	const char delimeter = '/';

	while(getline(ss, token, delimeter)) {
		if(token == "..") {
			if(pathStack.back() == "/") { // absolute path cannot have '..' at start
				throw invalid_argument("Path error!");
			} else {
				if(pathStack.empty() || pathStack.back() == "..") { // '..' at start
					pathStack.push_back("..");
				} else {
					pathStack.pop_back();
				}
			}
		} else if(token == "." || token == "") { //skip

		} else {
			pathStack.push_back(token);
		}
	}

	string result;

	if(!pathStack.empty()) {
		result = pathStack[0];

		for(size_t i=1; i<pathStack.size() ; ++i) {
			if(i == 1 && result == "/") { // Avoid "//"
				result += pathStack[i];
			} else {
				result += "/" + pathStack[i];
			}
		}
	}

	return result;
}

int main()
{
	string path;

	path = "scripts//./../scripts/awk/././";
	cout << "Path=       " << path <<endl;
	cout << "Normalized= " << ShortestEquivalentPath(path) << endl;

	path = "/usr/lib/../bin/gcc";
	cout << "Path=       " << path <<endl;
	cout << "Normalized= " << ShortestEquivalentPath(path) << endl;
}
