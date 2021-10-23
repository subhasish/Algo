/*
 * 06.CircularTravel.cpp
 *
 * Problem: You have number of cities in circular fashion at different distance. Each city has some
 * 			amount of gas. Total amount of gas is equal that required to travel all cities.
 * 			You need to start at a city and come back to the same starting city without running out
 * 			of gas, refilling at each city.
 *
 * 			You need to find whether there is some city such that a full round is possible.
 *
 *  Created on: Jun 3, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			One thing to observe that independent of starting city the curve of gas remaining
//			in tank follow same form (allowing negative). Starting city only cause the curve to
//			translate in y-direction.
//
//			So independent of starting city, one city (may be more) will have minimum gas when
//			entering that city. This is because the graph only translates and shifts.
//			If we take that city as starting city then we have maximum chance of finishing
//			all the cities.

typedef vector<int> VI;

const int kMPG = 20;

size_t FindStartingCity(const VI& gas, const VI& distances)
{
	int remaining_gallon = 0;

	struct CityAndRemainingGas{
		int city, remaining_gallon;
	};

	CityAndRemainingGas min_city_gas;
	size_t num_cities = gas.size();

	for(int i=1; i < (int)num_cities ; ++i) {
		remaining_gallon += (gas[i-1] - distances[i-1] / kMPG);

		if(remaining_gallon < min_city_gas.remaining_gallon) {
			min_city_gas = CityAndRemainingGas{ i, remaining_gallon};
		}
	}

	return min_city_gas.city;
}

int main()
{
	VI gas = {50, 20, 5, 30, 25, 10, 10};
	VI dis = {900, 600, 200, 400, 600, 200, 100};

	cout << FindStartingCity(gas, dis) << endl;
}
