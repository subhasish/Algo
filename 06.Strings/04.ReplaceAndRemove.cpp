/*
 * 04.ReplaceAndRemove.cpp
 *
 * Problem: Modify a string by replace and delete using following rule:
 *          - replace all 'a' by two 'd's
 *          - delete all 'b's
 *
 *  Created on: Oct 8, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Doing these operations one by one will require moving all characters multiple times
//  Replacing with different size string will require right shifting
//  Deleting will require left shift

// Another alternative is to copy it to another string according to rule. But requires additional space.

// Deleting 'b' can be done by doing a forward iteration and copying only other characters to a current index

// If we know the final length of string after replacing 'a's then we can start writing from back.

// Return: size of final string.
// Assume: string has storage to store the final result
int ReplaceAndRemove(char* str, int size)
{
	//Forward iteration: remove 'b' and count number of 'a's
	int write_idx = 0, a_count=0;
	for(int i=0; i<size ; i++) {
		if(str[i] != 'b') {
			str[write_idx] = str[i];
			++write_idx;
		}
		if(str[i] == 'a') {
			++a_count;
		}
	}


	//Backward iteration: replace 'a's with 'dd's starting from the end
	int final_sz= write_idx + a_count;
	str[final_sz] = '\0';
	for(int i=final_sz-1, j=write_idx-1; j>=0 ; i--, j--) {
		if(str[j] != 'a') {
			str[i] = str[j];
		} else {
			str[i] = str[i-1] = 'd';
			--i;
		}
	}

	return final_sz;
}

int main()
{
	char str[20] = "acdbbcae";
	ReplaceAndRemove(str,8);
	cout << str << endl;
}



