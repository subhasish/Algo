/*
 * 03.ViewMaxPoints.cpp
 *
 * Problem: There are number of points in the plane that we want to observe.
 * 			You are located at point (0,0). You can rotate about this point, and
 * 			your field of view is a fixed angle.
 *
 * 			Which direction should you face to maximize the number of visible points.
 *
 *  Created on: Jun 2, 2018
 *      Author: subha
 */

// Solution:
//			Obviously we need to try all possible angles. It would be better if we
//			have all the points sorted based on their angle and we incrementally
//			consider them.
//
//			Convert all the points from Cartesian form to Polar form. Then sort them based on the
//			angle. Now consider points in order. At each step add new point, and leave all points
//			that beyond the viewing angle.
//			Keep track of maximum.
//
// Time complexity:
// 			Converting from Cartesian to Polar is O(n).
//			Sorting based on polar angle is O(n log n).
//			Traversing over all points in sorted order id O(n).
//			Overall O(n log n).
