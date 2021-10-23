/*
 * 03.MinIntervalCoverCircular.cpp
 *
 * Problem: This is the circular version of the minimum interval cover problem.
 *
 * 			Given the circular arcs in concentric fashion we need to find minimum number of rays
 * 			from the center that would cover all the arcs.
 *
 *  Created on: May 20, 2018
 *      Author: subha
 */

// Solution:
//			The solution involved transforming the circular problem in to linear one.
//			We want to do it such a way that there is some guarantee that we are not losing the
//			optimum solution.
//
//			Breaking the circular chain is the key to convert circular to linear problem.
//			So we need to find one ray that would create a break but that ray has to be part of
//			the optimal solution.
//
//			Now consider the smallest arc. There will be no arc that smallest arc can fully contain.
//			So either end of the smallest arc should be part of the solution. So we can try with
//			rays on both the end and see which one gives optimal solution.
//
//			Once the first ray converts circular problem to linear we can solve the linear problem
//			in n log n time. We will have to do it twice and take the minimum.
//
//			The problem representation may need transformation to transform the arcs to lines.
//
// Time complexity:
//			Once find minimum length arc in O(n).
//			Then for both of its end see which arc they overlap and create two problem list in O(n).
//			Then on both of those problems apply linear algorithm of O(n log n).
//			Overall O(n log n).

