/*
 * 00.TriominoPlacement.cpp
 *
 * Problem: A triomino is formed by three unit sized squares in L shape.
 * 			A mutilated chess board formed by 8x8 square chess board minus the top left square.
 *
 * 			Design an algorithm an algorithm of computing placement of 21 triominos that
 * 			cover the 8x8 mutilated chess board.
 *
 *  Created on: Mar 31, 2018
 *      Author: subha
 */

// Solution:
//			Normal recursively thinking may prompt us to think building placement of NxN board can
//			from solution of (N-1)x(N-1). But quickly we see that this line of reasoning do not lead
//			us anywhere.
//
//			Another hypothesis is that if a placement exists for an NxN board then there also one
//			exists for 2Nx2N board. Take 4 NxN board and place them such that 3 of them have their
//			missing piece in the center so that it can be filled by one more triomino.
//
//			See book for the pictures.
//
// Question?
//			What about other possible configurations that spans multiple of the 4 boards? Seems like
//			either assuming none of such is possible or not counting them.


