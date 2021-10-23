/*
 * codejam-2019-datbae.cpp
 *
 *  Created on: Apr 13, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

struct Segment {
	int in_start;
	size_t in_len;
	int out_start;
	size_t out_len;

	bool operator== (const Segment& that) const {
		return in_start == that.in_start;
	}
};

struct HashSegment {
	size_t operator() (const Segment& a) const {
		return hash<int>()(a.in_start);
	}
};

void parseSegmentsFromStr(const string& s, unordered_map<int, string>& seg_out, const int num_segments) {
	bool find_0 = true;
	int start = 0;

	//cout << "Trying to segment: " << s << endl;
	for(int j=0 ; j<num_segments ; ++j) {
		size_t end = s.find(find_0 ? "0" : "1", start);
		string sub = "";
		if(end == string::npos) {
			if(s.length() - start > 15) {
				end = start + 15;
				sub = s.substr(start, 15);
			} else {
				sub = s.substr(start);
			}
		} else {
			if(end - start > 15) {
				end = start + 15;
			}
			sub = s. substr(start, end-start);
		}

		//cout << j << " th segment: " << sub << ", ";
		seg_out[j] = sub;

		if(end == string::npos) {
			break;
		}
		start = end;
		find_0 = !find_0;
	}

	//cout << "Segment complete" << endl;
}

void makeInputStringFromSegments(const unordered_map<int, string>& segs, string& out, size_t cap) {
	out.reserve(cap);
	out = "";
	for(int i=0 ; i < (int)segs.size() ; ++i) {
		out += segs.at(i);
	}
}

int main() {
    int T, N, B, F;
    cin >> T;

    for(int i=1 ; i<=T ; ++i) {
        cin >> N >> B >> F;

        int num_segments = (int)ceil(N/15.0);
        unordered_map<int, string> seg_out;
        unordered_map<int, string> seg_in;
        unordered_map<int, int> len_in;
        string in_str = "";
        string out_str;

        // First try
        for(int n=N, j=0 ; n>0 ; n -= 15, ++j) {
        	seg_in[j] = string(min(n,15), (j%2 == 0) ? '1': '0');
        	len_in[j] = seg_in[j].length();
        }

        makeInputStringFromSegments(seg_in, in_str, N);

        cout << in_str << endl;
        cin >> out_str;
        parseSegmentsFromStr(out_str, seg_out, num_segments);

        unordered_set<Segment, HashSegment> toTest;
        int in_start = 0, out_start = 0;
        for(int j = 0 ; j < (int)seg_out.size() ; ++j) {
        	toTest.emplace(Segment{in_start, seg_in[j].length(), out_start, seg_out[j].length()});
        	in_start += seg_in[j].length();
        	out_start += seg_out[j].length();
        }

        set<int> broken;

        while(!toTest.empty()) {
        	unordered_set<Segment, HashSegment> new_toTest;
        	while(!toTest.empty()) {
        		Segment sg = *toTest.begin();
        		toTest.erase(toTest.begin());
        		string input = in_str.substr(sg.in_start, sg.in_len);
        		string output = out_str.substr(sg.out_start, sg.out_len);
        		if(output.length() == 0) {
        			for(int k = 0 ; k < (int) sg.in_len ; ++k ) {
        				broken.emplace(sg.in_start + k);
        			}
        		} else if(output.length() < input.length()) {
        			int first_len = input.length()/2;
        			for(int k = 0 ; k < (int) input.length() ; ++k) {
        				if(k < first_len) {
        					in_str[sg.in_start + k] = '1';
        				} else {
        					in_str[sg.in_start + k] = '0';
        				}
        			}
        			new_toTest.emplace(sg);
        		} else {
        			//Case matched. So no need to consider for future.
        		}
        	}

        	if(new_toTest.empty()) {
        		//We are done
        		break;
        	}

        	//Else
        	//Now each segment in new_toTest has half 1s and half 0s
        	//Test it

        	cout << in_str << endl;
        	cin >> out_str;

        	while(!new_toTest.empty()) {
        		Segment sg = *new_toTest.begin();
				new_toTest.erase(new_toTest.begin());
				string input = in_str.substr(sg.in_start, sg.in_len);
				string output = out_str.substr(sg.out_start, sg.out_len);
				unordered_map<int, string> temp_seg_out;
				parseSegmentsFromStr(output, temp_seg_out, 2);

				size_t first_in_len = sg.in_len / 2;
				size_t first_out_len = temp_seg_out[0].length();
				Segment a = Segment{sg.in_start, first_in_len, sg.out_start, first_out_len};
				Segment b = Segment{sg.in_start + (int)first_in_len, sg.in_len - first_in_len, sg.out_start + (int)first_out_len, temp_seg_out[1].length()};
				toTest.emplace(a);
				toTest.emplace(b);
        	}
        }

        stringstream bs;
        for(int br: broken) {
        	bs << br << " ";
        }
        cout << bs.str() << endl;
        int res;
        cin >> res;
        if(res == -1) {
        	return 0;
        }
    }
    return 0;
}

