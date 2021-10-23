/*
 * 00.STLCustomBST.cpp
 *
 * Problem: Create Set and Map of custom objects
 *
 *  Created on: Mar 20, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Similar as custom hash table, that is custom unordered_map and unordered_set
//
//			 Can be defined in one of the 3 ways:
//			 	1. Define operator< ( instead of operator== ) in the class
//				2. Define one Comparator struct with operator() and pass it to constructor
//				3. Define std::less<Class> struct that has operator()
//
//			 Here we need less operator as we are interested in total ordering.
//
//			 **Another main difference is that we do not need hash function as in hash table
//
// C++:
//			operator< needs to implement strict weak ordering, so that equivalence can be tested as !((a<b)||(b<a))
//			This means checking (value <= that.value) will not work.
//
//			Map works with specialization of less<> but not sort.

class MyClass
{
public:

    MyClass(int i): val(i) {}

//    bool operator< (const MyClass& that) const { return val < that.val; }

    int val;
};

class MyComparator
{
public:
	bool operator() (const MyClass& a, const MyClass& b) const { return a.val < b.val; }
};

//namespace std
//{
//    template<> struct less<MyClass>
//    {
//       bool operator() (const MyClass& a, const MyClass& b) const { return a.val < b.val; }
//    };
//}

int main()
{
    MyClass c1(1);
    MyClass c2(2);
    MyClass c3(3);

    map<MyClass, int, MyComparator> table;
//    map<MyClass, int> table;

    table[c1] = 12;
    table[c2] = 22;
    table[c3] = 33;

    cout << "Mapped values are: " << table.lower_bound(c1)->second << " " << table[c2] << " " << table[c3] << endl;

    //vector<MyClass> V = { {1}, {2}, {3} };
    //sort(V.begin(), V.end());

}
