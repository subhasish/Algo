/*
 * 09.CyclicRightShiftList.cpp
 *
 * Problem: Right shift a list by k nodes. k can be larger than the length of the list.
 *
 *  Created on: Nov 4, 2017
 *      Author: subha
 */


// if k>N then we can take k mod N. So lets assume k<N.
// That mean kth node from the end will become the head of the list.
// Find kth node from end. Cut the list and join it properly.

