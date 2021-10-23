/*
 * 09.FindMissingElement.cpp
 *
 * Problem: You are given a file containing one billion IP addressed, each of which is 32 bit quantity.
 * 			How do you find an IP address not in the file.
 *
 * Restriction: We have unlimited disk space but few megabytes of memory.
 *
 *  Created on: Feb 11, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution:
//		Total possible IP address of 32 bit: 2^32 = 2^10 * 2^10 * 2^10 * 2^2 ~= 10^3 * 10^3 * 10^3 * 4 = 4 billion
//		As we have 1 billion addresses in the file then there has to be some addressed missing.
//
//		If we want to make an bit array of 2^32 addresses then total memory required:
//		2^32 / 8 bytes = (10^3 * 10^3 * 10^3 * 4) / 8 bytes = 1/2 GB (B -> KB -> MB -> GB) = 512 MB
//		But we have only a few MBs.
//
//		That was the best thing we could do using one pass of the file. But we can do multiple passes.
//		We make a pass through the file to count number of addresses starting with 1 and starting with 0.
//		One of the has be less than 2^31. The we can continue the counting with 2nd bit and reduce our search space.
//		So we can find the number in 32 passes using 2 counter variables.
//
//		But we have more memory than that. So how many counter we can have in few megabytes?
//		2^16 integers = 2^16 * 4 bytes = 2^18 bytes = 2^8 KBs < 1MB
//		So with 2^16 integers and we can count a group of bits, specifically group of 16 MSBs.
//		One of them has to be less than 2^16. Then we will only inspect that group.
//
// C++:
//		bitset<size> bit_vector;  // will create a bit array
//      bit_vector.set(index);    // will set the bit at the index
//		bit_vector[i] == 0;		  // will check if ith bit is not set
//		ifstream::clear()   // once file is read till end, the eof state will be set. We need to clear it before trying to read the file again.
//		ifstream::seekg(0, ios::beg)  // this will return the stream to the beginning of the file

int FindMissingElement(ifstream *ifs)
{
	const size_t sizeOfBucket = 1 << 16;   // Note: 1 = 2^0;  1<<1 = 2 = 2^1; 1<<2 = 4 = 2^2; => 1<<n = 2^n

	vector<size_t> counter(sizeOfBucket, 0);

	unsigned int x;  // So that left shift do not move any leading 1; also there is no negative

	while(*ifs >> x) {
		int upper_bits = x >> 16;
		++counter[upper_bits];
	}

	// Now look for a bucket for which count is less than 2^16
	const int bucketLimit = 1 << 16;
	size_t bucket_to_search;
	for(size_t i=0; i<counter.size() ; ++i) {
		if(counter[i] < bucketLimit) {
			bucket_to_search = i;
			break;
		}
	}

	// Now all IP addresses whose MSB equals the bucket_to_search
	ifs->clear();  // Clear the eof state of the stream
	ifs->seekg(0, ios::beg);  // Seek to the beginning of the file

	bitset<bucketLimit> bit_vec;   // bit array of size 2^16
	size_t lsbMask = (1 << 16) - 1; // Mask of LBS 16 bits set to 1

	while(*ifs >> x) {
		size_t upper_bits = x >> 16;
		if(upper_bits == bucket_to_search) {  // MSB match
			size_t lower_bits = x & lsbMask;
			bit_vec.set(lower_bits);
		}
	}

	// Now see for which bit_vec is false
	for(size_t i=0 ; i<bucketLimit ; ++i) {
		if(bit_vec[i] == 0) {
			return (bucket_to_search << 16) | i;
		}
	}

	// Dead code
	return 0;
}

int main()
{
	std::ifstream ifs;
	ifs.open("09.LogFile.txt", std::ifstream::in);

	cout << "Number not in file: " << FindMissingElement(&ifs) << endl;

	ifs.close();
}
