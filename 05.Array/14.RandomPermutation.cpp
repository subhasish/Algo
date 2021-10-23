/*
 * 14.RandomPermutation.cpp
 *
 * Problem: Compute random permutation of an input
 *
 * Same as creating random samples but of as same size as the input
 *
 *  Created on: Aug 26, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
#include <random> //not needed as such

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



// Return random sample of k elements
// Selecting each element with probability k/n may not result in exact k samples
// So we need to select one element at a time, k times
VI RandomSampling(int k, VI A)
{
	int n = static_cast<int>(A.size());

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine gen(seed);
	//random_device rd;
	//default_random_engine gen(rd());

	for(int i=0; i<k ; ++i) {
		// generate a random index in [i, n-1]
		// Pick that element and put it in the ith position of the result

		uniform_int_distribution<int> distr(i, n-1);
		int r = distr(gen);

		swap(A[i],A[r]);
	}

	// Array [0,k-1] has the result
	VI result(A.begin(), A.begin()+k);
	return result;
}

VI RandomPermutation(VI A)
{
	VI permutation = RandomSampling(A.size(),A);
	return permutation;
}

int main()
{
	VI permutation = RandomPermutation({1,2,3,4,5,6,7,8,9,10});
	print_vector(permutation);
}



