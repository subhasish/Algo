/*
 * 0.ArrayVectorLibraries.cpp
 *
 *  Created on: Aug 9, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

void print_vector(vector<int> list)
{
	for(int i: list)
	{
		cout << i << " ";
	}
	cout << endl;
}

int main()
{
	// instantiate array and vectors
	array<int, 3> A1 = {1,2,3};
	vector<int>   V1 = {1,2,3,4,5,6};

	cout << "1D array size: " << A1.size() << endl;

	// construct sub-array from array
	int i=1,j=4;
	vector<int> subarray_V1(V1.begin()+i, V1.begin()+j); // V1[i, j-1]
	cout << "Array :" ;
	print_vector(V1);
	cout << "Sub array from 1 to 3: " ;
	print_vector(subarray_V1);

	// instantiate 2D array
	array<array<int, 2> ,3> A2 = {1,2,3,4,5,6};
	vector<vector<int>>     V2 = {{1,2}, {3,4}, {5,6}};
	cout << "Element of 2D array initialized as 1D: ";
	cout << A2[2][1] <<endl;

	// old 2D array
	int** ary = new int*[3];
	for(int i = 0; i < 3; ++i)
	    ary[i] = new int[2];

	// grow array
	V1.push_back(42);
	V1.emplace_back(48);
	// Two differences between push_back and emplace_back
	// 1. Without compiler optimization, push_back creates a temporary object and then moves it to the vector.
	//    emplace_back passes the value forward to the constructor for in-place construction.
	// 2. push_back only calls implicit constructors whereas
	//    emplace_back can call explicit constructor and can be less safer


	// Key methods in algorithms. Array has to be sorted
	bool isPresent = binary_search(V1.begin(), V1.end(), 6);
	cout << "Value present? " << isPresent << endl;

	// lower_bound: first element in the range [first,last) which is not less than val. Can be equal.
	// upper_bound: first element in the range [first,last) which is greater than val. Cannot be equal.
	// return type of lower_bound, upper_bound is vector<int>::iterator
	auto lb = lower_bound(V1.begin(), V1.end(), 6);
	vector<int>::iterator ub = upper_bound(V1.begin(), V1.end(), 6);
	if(lb == V1.end()) cout << "No lower bound" << endl;
	else cout << "Lower bound (first one that is not less): " << *lb << endl;
	if(ub == V1.end()) cout << "No upper bound" << endl;
	else cout << "Upper bound (first one that is greater) : " << *ub << endl;


	// fill: assigns val to all the elements in the range [first,last).
	//       while (first != last) { *first = val; ++first;  }
	vector<int> Vfill (8);  // creates a vector of size 8 and fills with 0
	fill(Vfill.begin()+1, Vfill.end()-2, 5); // fills with 5
	cout << "Vector partially filled with 5: ";
	print_vector(Vfill);


	// min_element: returns smallest element in the range
	// max_element: returns largest element in the range
	// They return Iterator and NOT the element
	auto smallest = min_element(V1.begin(), V1.end());
	auto largest  = max_element(V1.begin(), V1.end());
	cout << "Smallest: " << *smallest << ", Largest: " << *largest << endl;

	//reverse 0: reverse a range
	reverse(Vfill.begin(), Vfill.begin()+4);
	cout << "Reversing partially: ";
	print_vector(Vfill);

	//reverse 1: reverse can easily be done using crbegin() and crend() iterators
	vector<int> rev(Vfill.crbegin(), Vfill.crend());
	cout << "Last array reversed: ";
	print_vector(rev);

	//rotate: Rotates [first,last), such that middle becomes the new first element.
	vector<int> Vrot;
	for (int i=1; i<10; ++i) Vrot.push_back(i); // 1 2 3 4 5 6 7 8 9
	cout << "Rotation test [make 4th element the first one]: " << endl;
	cout << "Original: "; print_vector(Vrot);
	rotate(Vrot.begin(), Vrot.begin()+3, Vrot.end());
	cout << "After   : "; print_vector(Vrot);


	//sort: sorts an array
	sort(Vrot.begin(),Vrot.end());
	cout << "Sorted: "; print_vector(Vrot);

	//copying a sub-vector in a new vector
	vector<int> copied(Vrot.begin()+2, Vrot.begin()+6);
	cout << "Copied done by using constructor: ";
	print_vector(copied);




}

