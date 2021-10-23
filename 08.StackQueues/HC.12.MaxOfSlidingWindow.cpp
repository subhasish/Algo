/*
 * HC.12.MaxOfSlidingWindow.cpp
 *
 * Problem: You are given traffic at various time stamps and a window length. Compute for each
 * 			time stamp, the maximum traffic over the window length time interval which ends at
 * 			that time stamp.
 *
 *  Created on: Nov 5, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			Need to sort the input array if it were not sorted. Then consider each point in the
//			time stamp and maintain the queue with max with all the time stamps within the window
//			length.
//			When encountering a new number remove all the elements from the queue front that
//			lies beyond the window length.
//
//			Queue with max can be implemented by maintaining an internal data structure
//			that is non-increasing in nature. Keep duplicate entries to handle duplicate maximums.
//			Non-increasing because if current element is greater than previous elements then it
//			will be maximum among the group and all previous elements will be popped first.

template <typename T>
struct QueueWithMax {
	queue<T> Q;
	deque<T> Non_decreasing;

	void enqueue(T& a) {
		Q.emplace(a);

		//Remove all elements smaller than current one
		while(!Non_decreasing.empty() && Non_decreasing.back()<a) {
			Non_decreasing.pop_back();
		}
		Non_decreasing.emplace_back(a);
	}

	void dequeue() {
		if(Q.empty()) {
			return;
		}

		T res = Q.front();
		if(res == Non_decreasing.front()) {
			Non_decreasing.pop_front();
		}
		Q.pop();
	}

	T front() const {
		return Q.front();
	}

	T Max() const {
		return Non_decreasing.front();
	}
};

typedef vector<double> VD;
struct TraficData {
	int time=0;
	double val=0;

	TraficData(int t, double v): time(t), val(v) {}
	bool operator== (TraficData& that)  { return val == that.val; }
	bool operator< (TraficData& that)  { return val < that.val; }
};


VD MaxOfSlidingWindow(vector<TraficData>& traffic, int W) {
	QueueWithMax<TraficData> QT;
	VD result;

	QT.enqueue(traffic[0]);
	result.emplace_back(traffic[0].val);
	for(size_t i=1,j=0 ; i<traffic.size() ; ++i) {
		QT.enqueue(traffic[i]);
		while(j<i && (traffic[i].time - traffic[j].time) > W) {
			QT.dequeue();
			++j;
		}
		result.emplace_back(QT.Max().val);
	}

	return result;
}

void PrintVector(VD& list) {
	for(double d: list) {
		cout << d << " ";
	}
	cout << endl;
}

int main() {
	vector<TraficData> T = {TraficData(0,1.3), TraficData(2,2.5), TraficData(3,3.7), TraficData(5,1.4), TraficData(6,2.6), TraficData(8,2.2), TraficData(9,1.7), TraficData(14,1.8)};
	vector<double> res = MaxOfSlidingWindow(T, 3);
	PrintVector(res);
}
