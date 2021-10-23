/*
 * 11.HighestBestOfThree.cpp
 *
 * Problem: Write a program that takes an input file containing name and test score of students and
 * 			returns the student who has maximum score averaged across his or her top 3 scores.
 * 			Ignore student that has less than 3 scores.
 *
 *  Created on: Feb 25, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: For top 3 scores we need min-heap. To map each student to their min-heap we need a hash table

typedef priority_queue<int, vector<int>, greater<int>> MINPQ;

int SumOfPriorityQueue(MINPQ pq)
{
	int sum = 0;
	while(!pq.empty())
	{
		sum += pq.top();
		pq.pop();
	}
	return sum;
}

string FindHighestBestOfThree(ifstream* ifs)
{
	unordered_map<string, MINPQ> student_scores;

	string name;
	int score;
	while(*ifs >> name >> score) {
		student_scores[name].emplace(score);
		if(student_scores[name].size() > 3) {
			student_scores[name].pop();
		}
	}

	string top_student = "no such student";
	int current_top = 0;
	for(auto it: student_scores)
	{
		if(it.second.size() == 3)
		{
			int sum = SumOfPriorityQueue(it.second);
			if(current_top < sum)
			{
				current_top = sum;
				top_student = it.first;
			}
		}
	}

	return top_student;
}


int main()
{
	std::ifstream ifs;
	ifs.open("11.StudentScore.txt", std::ifstream::in);

	cout << "Top Student: " << FindHighestBestOfThree(&ifs) << endl;

	ifs.close();
}
