/*
 * minimum-cost-to-hire-k-workers.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

double min(double& a, double b) {
    return (a<b) ? a : b;
}
class Solution {
    struct Emp {
        int quality;
        int wage;
    };
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        vector<Emp> emps;
        double min_wage = wage[0];
        for(int i=0 ; i< (int)quality.size() ; ++i) {
            emps.emplace_back(Emp{quality[i], wage[i]});
            min_wage = min(min_wage, wage[i]);
        }

        if(K == 1) {
            return min_wage;
        }

        // Observation 1: Someone will be paid their minimum wage in the paid group. That one is the bottleneck.
        // Observation 2: The one with the highest wage/quality ratio is creating the bottleneck

        // Brute force:
        // Now it can be brute force that we consider for all possible ratios take the minimum valid k wages
        // Its time complexity is O(N * N log K) or O(N * N log N) depending on whether we use heap or sorting
        // in the inner loop

        // Optimized approach:
        // Hypothesis 3: To keep the wage low we start with lowest possible ratios. And then increase the ratio.
        // Basically it is some kind of optimized brute force.

        // So we can consider K lowest possible ratios. Note that the highest ratio will dominate the group.
        // Then include elements in the group with higher ratio that will increase the ratio for the whole group.

        // But which element to exclude?
        // Observation 3: With same ratio in the group, the element with high quality is causing more wage.
        // So remove the element with highest quality, i.e., highest wage.

        // So we can use heap to track element with highest quality
        // **Observation 4: As ratio in the group is same, total quality * ratio is total wage for the group.
        // So as we push and pop from the heap we can keep track of the total quality and use ratio to find the wage.

        sort(emps.begin(), emps.end(),
            [](const Emp& a, const Emp& b) {
                return (a.wage/(double)a.quality) < (b.wage/(double)b.quality);} );

        min_wage = numeric_limits<double>::max();
        priority_queue<int, vector<int>, less<int>> max_heap_quality;
        double total_quality = 0;
        for(int i=0 ; i< (int)emps.size() ; ++i) {
            total_quality += emps[i].quality;
            double r = emps[i].wage / (double)emps[i].quality;
            max_heap_quality.push(emps[i].quality);
            if(i >= K-1) {
                if(i > K-1) {
                    total_quality -= max_heap_quality.top();
                    max_heap_quality.pop();
                }
                min_wage = min(min_wage, r * total_quality);
            }
        }
        return min_wage;
    }
};

int main() {
	Solution obj;
	vector<int> quality = {10,20,5};
	vector<int> wages = {70,50,30};

	double res = obj.mincostToHireWorkers(quality, wages, 2);

	cout << res << endl;
}

