/*
 * 14.HashFunctionForChess.cpp
 *
 * Problem: Design a hash function for chess game states.
 * 			The hash function should take a state and hash code for that state, and a move,
 * 			and efficiently compute the hash code for the updated state
 *
 *  Created on: Feb 28, 2018
 *      Author: subha
 */


// Solution:
//			Straightforward hash function is to treat the board as 64 "base 13" digits.
//			The 13 base comes from the total 13 possibilities for each positions.
//			Then hash function could produce a weighted sum of those 64 numbers.
//			It can also be incrementally updated by subtracting old position values and adding new position values.
//
//			Now instead of taking weighted sum, using XOR can produce a hash function that would be much faster to compute.
//			It is same strategy we had seen for collection of strings.
//			XOR is associative, commutative and fast to compute, additionally a^a=0
//			So, in general XOR is good to combine hash of collection of items.
//
//			To help XOR catch more information with less space, each state of a cell can be encoded in 13 CODES for 13 different states.
//			Now we can have 64 of them to depict the state of whole board. So total 13*64=832 different CODES need to depict all
//			possible states of a chess board.
//			So each cell will have 13 different codes.
//
//			The hash code for the state of the chess board will be XOR of all the codes for each location.
//
//			Now incremental update is fast as when a cell moves from state A to state B then just need to XOR those two codes,
//			so that old code gets nullified and new code gets added

