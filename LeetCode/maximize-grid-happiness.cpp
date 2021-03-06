/*
 * maximize-grid-happiness.cpp
 *
 *  Created on: Nov 26, 2020
 *      Author: subha
 */


#include <bits/stdc++.h>
using namespace std;

void swap(int& a, int& b) {
	int t = a; a = b; b = t;
}

class Solution {
public:
    int getMaxGridHappiness(int m, int n, int iCnt, int eCnt) {
        if(m < n) { swap(m,n); }	//memory optimize as we consider (1 << n) combinations. Keep n lower of the two.

        int maxMask = ((1 << n) - 1);
        int maxBit = (1 << (n-1));

        // DP[i][j][i_count][e_count][i_mask][e_mask][curr] = maximum grid happiness of the grid cell upto cell [i,j]
        //                                                    using i_count number of introvert and e_count number of extrovert,
        //                                                    with position of introverts in last n cell represented as i_mask
        //                                                    and position of extroverts in last n cell represented as e_mask,
        //													  and current cell has items curr -> [0 - empty, 1 - introvert, 2 - extrovert]
        //
        // The detail of position of last n cells is required to compute bigger subproblem from smaller ones as position
        // of neighbors will affect results.

        int DP[m][n][iCnt+1][eCnt+1][maxMask+1][maxMask+1][3];
        memset(DP, 0, sizeof(DP));

        //Penalty for the combination of neighbors [0 - empty, 1 - introvert, 2 - extrovert]
        int penalty[3][3] = {{0, 0, 0}, {0, -60, -10}, {0, -10, 40}};

        //Try all positions from top left
        for(int i = 0 ; i < m ; ++i) {
            for(int j = 0 ; j < n ; ++j) {
            	//Try all possibilities of introvert and extrovert count
                for(int ic = 0 ; ic <= iCnt ; ++ic ) {
                    for(int ec = 0 ; ec <= eCnt ; ++ec) {

                    	//For first cell it is base case and can have direct answer
                        if(i == 0 && j == 0) {
                            if(ic > 0) {
                                DP[i][j][ic][ec][0][0][1] = 120;
                            }
                            if(ec > 0) {
                                DP[i][j][ic][ec][0][0][2] = 40;
                            }
                            continue;
                        }

                        //Cell in first row will have smaller number of previous cells to consider.
                        //If we are at column j then only previous j cells need to be considered and not n cells
                        if(i == 0) {
                        	maxMask = ((1 << j) - 1);
                        } else {
                        	maxMask = ((1 << n) - 1);
                        }

                        //Try all possible positions of introverts in previous n cells
                        for(int i_mask = 0 ; i_mask <= maxMask ; ++i_mask) {
                            int i_in_last = __builtin_popcount(i_mask);
                            if(i_in_last > ic) {	//If mask has more introverts than allowed then skip this iteration
                            	continue;
                            }

                            ////Try all possible positions of extroverts in previous n cells
                            for(int e_mask = 0 ; e_mask <= maxMask ; ++e_mask) {
                                int e_in_last = __builtin_popcount(e_mask);
                                if(e_in_last > ec) {	//If mask has more introverts than allowed then skip this iteration
                                	continue;
                                }

                                if(i_mask & e_mask) {		//Same cell cannot have both introvert and extrovert. Need this as we handle the masks separately
                                	continue;
                                }

                                int last_i = (j == 0 && i > 0) ? i - 1 : i;
                                int last_j = (j == 0) ? n - 1 : j - 1;

                                //Based on the mask value determine if there is any node on the left or up cell
                                bool isUpIntro = (i > 0) ? (i_mask & maxBit) : false;
                                bool isLeftIntro = (j > 0) ? (i_mask & 1) : false;
                                bool isUpExtro = (i > 0) ? (e_mask & maxBit) : false;
                                bool isLeftExtro = (j > 0) ? (e_mask & 1) : false;

                                //Previous node and the up node will be dictated by the mask values
                            	int prev = 0, up = 0;
                            	if(isLeftIntro || (j == 0 && (i_mask & 1))) { prev = 1; }
                            	else if(isLeftExtro || (j == 0 && (e_mask & 1))) { prev = 2; }
                            	if(isUpIntro) { up = 1; }
                            	else if(isUpExtro) { up = 2; }

                            	//For trying all possibilities of the previous cell, compute its all possible mask values
                            	int p_i_mask_empty = (i_mask >> 1);
                            	int p_e_mask_empty = (e_mask >> 1);
                            	int p_i_mask_one = (p_i_mask_empty | maxBit);
                            	int p_e_mask_one = (p_e_mask_empty | maxBit);
                            	int i_in_prev_one = __builtin_popcount(p_i_mask_one);
                            	int e_in_prev_one = __builtin_popcount(p_e_mask_one);

                            	//Now try 3 possibilities in the current cell
                            	//[0 - empty, 1 - introvert, 2 - extrovert]
                                for(int curr = 0 ; curr <= 2 ; ++curr) {
                                	if(curr == 1 && ic - i_in_last < 1) { continue; }
                                	if(curr == 2 && ec - e_in_last < 1) { continue; }

                                	int last_ic = (curr == 1) ? ic - 1: ic;
                                	int last_ec = (curr == 2) ? ec - 1 : ec;

                                	//Now try to find the difference we need to add for placing curr in this current setup
                                	int diff = 0;
                                	if(curr == 1 && ic > 0) { diff = 120; }
                                	else if(curr == 2 && ec > 0) { diff = 40; }

                                	if(isLeftIntro || isLeftExtro) {
                                		diff += penalty[curr][prev];
                                	}
                                	if(n > 0 && (isUpIntro || isUpExtro)) {
                                		diff += penalty[curr][up];
                                	}

                                	//We need to consider 3 cases for the previous node.
                                	// The lease significant (n-1) bits of the mask for the previous node is dictated by current mask
                                	// The most significant place can be these 3: [0 - empty, 1 - introvert, 2 - extrovert]

                                	//Case 1: MSB is 0 - empty
                                	int res = max(0, DP[last_i][last_j][last_ic][last_ec][p_i_mask_empty][p_e_mask_empty][prev] + diff);

                                	if(i > 1 || (i == 1 && j > 0)) {
                                		if(last_ic >= i_in_prev_one) {
                                			//Case 2: MSB is 1 - introvert
                                			res = max(res, DP[last_i][last_j][last_ic][last_ec][p_i_mask_one][p_e_mask_empty][prev] + diff);
                                		}
                                		if(last_ec >= e_in_prev_one) {
                                			//Case 3: MSB is 2 - extrovert
                                			res = max(res, DP[last_i][last_j][last_ic][last_ec][p_i_mask_empty][p_e_mask_one][prev] + diff);
                                		}
                                	}

                                	DP[i][j][ic][ec][i_mask][e_mask][curr] = res;
                                }
                            }
                        }
                    }
                }
            }
        }

        //For final result consider all possible mask value and placement
        int finalResult = 0;
        maxMask = ((1 << n) - 1);
        for(int i_mask = 0 ; i_mask <= maxMask ; ++i_mask) {
            for(int e_mask = 0 ; e_mask <= maxMask ; ++e_mask) {
                finalResult = max(finalResult, DP[m-1][n-1][iCnt][eCnt][i_mask][e_mask][0]);
                finalResult = max(finalResult, DP[m-1][n-1][iCnt][eCnt][i_mask][e_mask][1]);
                finalResult = max(finalResult, DP[m-1][n-1][iCnt][eCnt][i_mask][e_mask][2]);
            }
        }

        return finalResult;
    }
};


int main() {
	Solution obj;
	cout << "Expected: 240, Actual: " << obj.getMaxGridHappiness(2,3,1,2) << endl;
	cout << "Expected: 260, Actual: " << obj.getMaxGridHappiness(3,1,2,1) << endl;
	cout << "Expected: 240, Actual: " << obj.getMaxGridHappiness(2,2,4,0) << endl;
	cout << "Expected: 680, Actual: " << obj.getMaxGridHappiness(3,4,4,3) << endl;
	cout << "Expected: 800, Actual: " << obj.getMaxGridHappiness(5,5,4,4) << endl;
//	cout << "Expected: 1240, Actual: " << obj.getMaxGridHappiness(5,5,6,6) << endl;
}

