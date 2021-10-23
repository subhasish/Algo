/*
 * FirstLarger.cpp
 *
 *  Created on: May 23, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

int searchFirstLargerThan(vector<int> arr, int k)
{
	int lo = 0;
	int hi = arr.size();
	int mid = lo + (hi-lo)/2;

	while (lo < hi)
	{
		mid = lo + (hi-lo)/2;
		if(arr[mid] <= k)
		{
			lo = mid + 1;
		} else if (arr[mid] > k)
		{
			hi = mid;
		}
	}
	return arr[mid];
}

int main() {

	int arr[] = {2,3,4,5,6};
	vector<int> vlist(arr, arr + sizeof(arr)/sizeof(arr[0]));

	cout << searchFirstLargerThan(vlist,4) << endl;

}

