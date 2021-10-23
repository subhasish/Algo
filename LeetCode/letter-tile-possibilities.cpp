/*
 * letter-tile-possibilities.cpp
 *
 *  Created on: Jul 1, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

class SolutionTopDown {
    vector<long long> Factorial = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};

    // Computes (i_0 + i_1 + ... + i_n)! / ( i_0! * i_1! * ... * i_n!)
    long long ComputePermutationWRepetition(const vector<int>& Frequency) {
        int sum = 0;
        for(auto i: Frequency) {
            sum += i;
        }

        long long fac = Factorial[sum];
        for(auto i: Frequency) {
            fac /= Factorial[i];
        }
        return fac;
    }

    void CombinationTopDownRecursive(int curr, const vector<int>& Frequency, vector<int>& partial, int& res) {
        //Got one combination
        if(curr == (int) Frequency.size()) {
            long long r = ComputePermutationWRepetition(partial);
            res += r;
            return;
        }

        //For curr_th element try all possible frequency of it
        for(int i = 0; i <= Frequency[curr] ; ++i) {
            partial[curr] = i;
            CombinationTopDownRecursive(curr + 1, Frequency, partial, res);
        }
    }

public:
    int numTilePossibilities(string tiles) {
        unordered_map<char, int> freq_map;
        for(auto ch: tiles) {
            ++freq_map[ch];
        }
        vector<int> Frequency;
        for(auto it: freq_map) {
            Frequency.emplace_back(it.second);
        }

        vector<int> partial(Frequency.size());
        int res = 0;
        CombinationTopDownRecursive(0, Frequency, partial, res);

        return res-1; //subtract 1 for empty
    }
};

class SolutionBottomUp {

    int ComputeBottomUpPermutation(vector<int>& Frequency) {
        int sum = 0;

        //Try all possible character at current position.

        for(int i = 0 ; i < (int) Frequency.size() ; ++i) {
            if(Frequency[i] > 0) {
                //For all the rest of the permutations we can add current one in front of them
                //So count all possible downstream permutations
                --Frequency[i];
                sum += ComputeBottomUpPermutation(Frequency);
                ++Frequency[i];

                //Now count when none of the downstream characters are used.
                //Permutation having only this character.
                //But this can potentially be used by upstream permutations
                ++sum;
            }
        }
        return sum;
    }

public:
    int numTilePossibilities(string tiles) {
        unordered_map<char, int> freq_map;
        for(auto ch: tiles) {
            ++freq_map[ch];
        }

        vector<int> Frequency;
        for(auto it: freq_map) {
            Frequency.emplace_back(it.second);
        }

        return ComputeBottomUpPermutation(Frequency);
    }
};

int main() {
	SolutionTopDown objtd;
	cout << objtd.numTilePossibilities("AAABBC") << endl;

	SolutionBottomUp objbu;
	cout << objbu.numTilePossibilities("AAABBC") << endl;
}
