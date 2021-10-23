/*
 * 0.distribution.cpp
 *
 *  Created on: Jun 13, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

#include <chrono>
#include <limits>
#include <random>

using namespace std;

int main()
{

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);

	uniform_int_distribution<int> iDistribution(1,6);
	uniform_real_distribution<double> dDistribution(1.3,2.9);

	cout << "One integer between 1 to 6 => " << iDistribution(generator) << endl;
	cout << "One float between 1.3 to 2.9 => " << dDistribution(generator) << endl;


	double d = generate_canonical<double,std::numeric_limits<double>::digits>(generator);
	std::cout << "Canonical random value: " << d << std::endl;


	random_device rd;
//	mt19937 rgen(rd());
//	default_random_engine rgen(rd());

	default_random_engine rgen(seed);

	cout << "One random integer => " << rgen() << endl;
	cout << "One random integer => " << rgen() << endl;
	cout << "One random integer => " << rgen() << endl;
}


