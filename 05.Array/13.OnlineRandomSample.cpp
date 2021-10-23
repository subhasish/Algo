/*
 * 13.OnlineRandomSample.cpp
 *
 * Problem: Maintain a random sample of k elements given an input stream of data
 *
 * Assumption: Input stream has at least k elements
 *
 *  Created on: Aug 26, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;

void swap(int& A, int& B)
{
	int t=A;  A = B;   B = t;
}

void print_vector(vector<int> list)
{
	for(int i: list)
	{
		cout << i << " ";
	}
	cout << endl;
}


VI OnlineRandomSample(int k, istringstream* sin)
{
	int x;
	VI sample;

	for(int i=0; i<k && *sin >> x ; ++i) {
		sample.push_back(x);
	}

	//unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	unsigned seed = time(NULL);
	default_random_engine gen(seed);

	//random_device rd;
	//default_random_engine gen(rd());
	//default_random_engine gen((random_device())());

	int num_so_far = k;
	while(*sin >> x)
	{
		++num_so_far;

		// Now the new number has k/n chance to be in the list
		// Generate a random number [0, num_so_far-1]
		// And if the number is [0, k-1] then re place that element with x

		int idx_to_replace = uniform_int_distribution<int>{0, num_so_far-1}(gen);

		if(idx_to_replace < k) {
			sample[idx_to_replace] = x;
		}
	}

	return sample;
}

int main ()
{
	istringstream is("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16");
	VI res = OnlineRandomSample(3,&is);
	print_vector(res);
}


