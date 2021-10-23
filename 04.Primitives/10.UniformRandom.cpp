/*
 * 10.UniformRandom.cpp
 *
 *  Using a random number generator that produces only 0 or 1,
 *  Generate a random number between [a,b], both inclusive
 *
 *  Created on: Jun 28, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

int UniformRandom1(int lower_bound, int upper_bound)
{
	int number_of_outcomes = upper_bound - lower_bound +1, result;
	do {
		result =0;
		// Generate one bit at a time. Append to the result.
		// Till number of bits is less than the number of bits in the range.
		// i starts with 0, so that result could be more than number_of_outcomes
		for(int i=0; (1 << i) < number_of_outcomes; ++i)
		{
			//rand()%2 will generate 0 or 1 at random
			result = (result << 1) | (rand() %2);
		}
	} while(result >= number_of_outcomes);

	return result + lower_bound;
}

int main()
{
	srand(time(NULL));
	cout << UniformRandom1(4,12) << endl;
	cout << UniformRandom1(4,12) << endl;
	cout << UniformRandom1(4,12) << endl;
	cout << UniformRandom1(4,12) << endl;
	cout << UniformRandom1(4,12) << endl;
	cout << UniformRandom1(4,12) << endl;
	cout << UniformRandom1(4,12) << endl;
}



