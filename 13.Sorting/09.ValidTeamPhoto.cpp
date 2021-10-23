/*
 * 09.ValidTeamPhoto.cpp
 *
 * Problem: Design an algorithm that takes as input two team and the heights of the players in the team,
 * 			and checks if it is possible to place players to take the photo in two rows subject to the placement constraint that a player in
 * 			the back row must be taller than a player in the front row.
 *
 *
 *  Created on: Mar 11, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//			If team A's tallest player is not taller than team B's tallest player then is not possible to place team A in front of team B.
//			Since tallest player is the hardest to place.
//			Apply the same logic to the remaining players.

struct Player {
	int height;

	bool operator< (const Player& that) const
	{
		return height < that.height;
	}
};


typedef vector<Player> VP;

bool ValidTeamPhotoPossible(VP& A, VP& B)
{
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	if(A[0] < B[0]) {   // A in front of B
		for(unsigned int i=0 ; i< A.size() ; ++i) {
			if(A[i].height >= B[i].height) {
				return false;
			}
		}
	} else {		// B in front of A
		for(unsigned int i=0 ; i< A.size() ; ++i) {
			if(B[i].height >= A[i].height) {
				return false;
			}
		}
	}

	return true;
}

int main()
{
	VP A = { {1}, {4} };
	VP B = { {5}, {2} };

	cout << "Possible: " << ValidTeamPhotoPossible(A,B) << endl;
}
