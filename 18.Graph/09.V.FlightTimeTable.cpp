/*
 * 09.V.FlightTimeTable.cpp
 *
 * Problem: A flight is specified by start-time, originating city, destination city, and arrival
 * 			time (possibly on a later day). A time-table is a set of flights.
 *
 * 			Given a time-table, a starting city, a starting time, and a destination city, how
 * 			would you compute the soonest you could get to the destination city?
 *
 * 			Assume all flights start and end on time, that you need 60 minutes between flights, and
 * 			a flight departing from A to B cannot arrive earlier at B than another flight from A to B
 * 			which departed earlier.
 *
 *  Created on: Jul 14, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			Shortest path, so Dijkstra should be able to solve. All we need to do is to map it to
//			a graph.
//
//			Create an edge for each flight with weight if the edge being the flight duration.
//
//			For all possible flights arriving at a city and departing from a city add an edge.
//			If the gap between the flights is more than 60 minutes then add edge weight of the
//			duration of the gap. Otherwise add an edge weight for the gap between flight on the
//			next day.
//
//			Add a virtual source and add edge from the virtual source to all departing flights from
//			source city. The weight of the edges should be difference of the time of flight and the
//			starting time. Note than different starting time may result in different solution.
//
//			Add a virtual destination and add edge from all the flights arriving at the destination
//			city with the virtual destination node. All such edges can have 0 weights.
//
//			Now apply Dijkstra's algorithm to the graph.
