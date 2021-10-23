/*
 * 08.V.ParallelJobSchedule.cpp
 *
 * Problem: Let we have a set of tasks than can run on a single server. Each task has a duration and
 * 			a set of tasks that need to be completed before this task can be started.
 *
 * 			Now compute the least amount of time needed to complete all the tasks given that we
 * 			can run infinite number of tasks in parallel.
 *
 *  Created on: Jul 15, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			To use longest path in DAG, we will have to map each job length to an edge weight:
//			Two vertices (begin and end) for each job.
//			Edge between them will have weight equals the time taken by the job.
//			One 0 weight edge for each precedence constraint.
//			Make a graph with dummy source and sink. They connect to all vertices with 0 weight edges.
//
//			Now find the longest path in this DAG. That is the critical path and minimum time to
//			finish all the jobs maintaining precedence constraint.

