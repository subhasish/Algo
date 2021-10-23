/*
 * 16.NonUniformRandomNumber.cpp
 *
 * Problem: Given an array and probability of each element to be selected,
 *          select an element with that probability
 *          Sum of the probabilities will be 1.
 *
 *  Created on: Aug 26, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;
typedef vector<double> VD;

void swap(int& A, int& B)
{
	int t=A;  A = B;   B = t;
}

void print_vector(vector<int> list)
{
	cout << "Size " << list.size() << ": ";
	for(int i: list)
	{
		cout << i << ", ";
	}
	cout << endl;
}
void print_vector(vector<double> list)
{
	cout << "Size " << list.size() << ": ";
	for(double i: list)
	{
		cout << i << ", ";
	}
	cout << endl;
}

// Two equal floating point number can differ by epsilon due to machine precision error
bool LessThanDouble(double a, double b)
{
	return (a + numeric_limits<double>::epsilon()) < b;
}

// Vector P represents the probability of each element being selected
// We need to create a range equal to the sum of the probabilities.
//   Then each element will have a range proportional to their probability of being selected.
//   Now if we generate a uniform random number over that range then
//   the probability of a range being selected is equal to the probability of the corresponding number being selected.
int NonUniformRandomNumberGenerator(VI A, VD P)
{
	// Creating a cumulative range
	VD cum;
	cum.push_back(0.0);
	for(unsigned int i=0; i<P.size() ; ++i) {
		cum.push_back(cum[i]+P[i]);
	}
	//cumulative.emplace_back(0.0);
	//partial_sum(P.begin(), P.end(), back_inserter(cumulative));

	// Generate a random number in [0,1)
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	double uniform_0_1 = generate_canonical<double, numeric_limits<double>::digits>(generator);

	cout << "Random number: " << uniform_0_1 << endl;
	VD::iterator lb = lower_bound(cum.begin(), cum.end(), uniform_0_1, LessThanDouble);
	int index_of_range = lb - cum.begin();

	print_vector(cum);
	cout << "Value " << uniform_0_1 << " at index " << index_of_range << endl;

	int index = index_of_range - 1;

	return A[index];
}

int main()
{
	int randomNumber = NonUniformRandomNumberGenerator({1,2,3,4,5,6},{.25,.1,.1,.1,.1,.35});
	cout << "Randomly selected number is: " << randomNumber << endl;
}


