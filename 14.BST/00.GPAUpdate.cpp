/*
 * 00.GPAUpdate.cpp
 *
 * Problems: Students have to be stored in the order of their GPA.
 * 			 Also we should be able to quickly update the GPA of a student given name/roll of a student.
 *
 *  Created on: Mar 21, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			We can use BST to store the students based on GPA.
//			Tie can be broken using the name/roll. This will keep them sorted based on GPA.
//			Now we want to update GPA and have name and new GPA.
//
//			As we don’t have old GPA we might need to do full traversal to get the student based on their name.
//			To do that quickly we need another hash table, which can directly take us to the corresponding entry in the tree.
//
//			See 08.OnlineKMostFrequent.cpp for similar solution.
