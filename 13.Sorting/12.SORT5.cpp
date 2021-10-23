/*
 * 12.SORT5.cpp
 *
 * Problem: Suppose you have 25 integers to sort and CPU has a special instruction SORT5 that can sort 5 integers in one cycle.
 * 			Compute the largest, second largest and third largest integers among the 25 numbers using the SORT5 function.
 *
 * 			Minimize the calls to the SORT5.
 * 			Assume the integers to be distinct.
 *
 *  Created on: Mar 14, 2018
 *      Author: subha
 */


// Solution:
//			Divide them in 5 sets A1, A2, A3, A4 and A5. Sort them. Let m1, m2, m3, m4 and m5 be the largest among these sets.
//			Assume without loss of generality that m1 > m2 > m3 > m4 > m5. Then m4 and m5 cannot be third largest.
//			So compute among a2,a3,m2,b2,m3.


