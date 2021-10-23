/*
 * 00.STLSortCustom.cpp
 *
 * Problem: Sort custom objects
 *
 *  Created on: Mar 6, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>


using namespace std;

// C++:
//		operator< can be defined in custom class to be used as default function. Notice that unlike lambda it is constant function
//		Note: Specialization for less<T> can NOT be used instead of operator<.
//			  Although that can be used as functor to pass as 3rd argument. Better pass some custom functor.
//		Lambda function can be used, similar to sort based on length

struct Student
{
	string name;
	double GPA;

	Student(string a, double b): name(a), GPA(b) {}

	bool operator< (const Student& that) const {
		return name < that.name;
	}
};

struct StudentComparator {
	bool operator() (const Student& a, const Student& b) const
	{
		return a.name < b.name ;
	}
};

void SortByName(vector<Student>& students)
{
	//sort(students.begin(), students.end());  // same
	sort(students.begin(), students.end(), StudentComparator());
}

void SortByGPA(vector<Student>& students)
{
	sort(students.begin(), students.end(), [] (const Student& a, const Student& b) { return a.GPA > b.GPA; } );
}

void PrintStudents(vector<Student>& students)
{
	cout << "Printing students:" << endl;
	for (Student a: students)
	{
		cout << "Name: " << a.name << ", GPA: " << a.GPA << endl;
	}
	cout << endl;
}

int main()
{
	vector<Student> students = {Student("pui", 4.8), Student("jeet", 4.1), Student("tito", 4.6), Student("rimpi", 3.2), Student("papai",3.8)};

	SortByName(students);
	PrintStudents(students);

	SortByGPA(students);
	PrintStudents(students);
}
