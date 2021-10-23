/*
 * 00.CustomKeyHashTable.cpp
 *
 * Problem: Create a hash table / set where key is a custom object, say a collection of strings named as contacts.
 * 			The collection can contain duplicates. All the keys are to meant equal based on distinct strings.
 * 			Order of strings in a key should also not matter.
 *
 *  Created on: Feb 19, 2018
 *      Author: subha
 */

#include<bits/stdc++.h>

using namespace std;

// Solution: For keys of built-in types we can directly use the STL unordered_set or unordered_map.
//			 But for custom objects it is not the case.
//
//			 In order to be able to store it in a hash table, we first need to explicitly define equality, that is operator==
//			 Also we need to provide custom hash function.
//
//			 Good hash function for collection of distinct entities is to XOR them
//
// C++:
//		hash<T>() is generic hash function defined for most built-in types.

typedef vector<string> VS;

// This is the custom class that is hashable
struct ContactList{
	VS names;

	// Use set to determine equality
	unordered_set<string> name_set;

	ContactList(VS l): names(l)
	{
		name_set = unordered_set<string>(names.begin(), names.end());
	}

	// Equal function for hash table
	bool operator== (const ContactList& that) const
	{
		return name_set == that.name_set;
	}

};

// Custom hash function to use STL. There are two ways: 1) Create a Hash Function class and pass that class as template parameter
// 2) Declare the specialization of hash<Edge> then we do not need to pass the template parameter
namespace std {

  template <>
  struct hash<ContactList>
  {
    std::size_t operator()(const ContactList& contacts) const
    {
    	size_t hash_code = 0;

    	// For collection of distinct entities good idea is to hash them
    	for(string contact: contacts.name_set)
    	{
    		hash_code ^= hash<string>()(contact);   //NOTE: the extra parentheses
    	}

    	return hash_code;
    }
  };

}

int main()
{
	ContactList c1({"a1", "a2", "b1", "b2"});
	ContactList c2({"a1", "a2", "b1", "b2", "a1", "a2", "b1"});
	ContactList c3({"a2", "b1", "a1", "a2", "b1", "b2"});
	ContactList c4({"a2", "b1", "b2"});

	unordered_map<ContactList, int> custom_map;
	custom_map[c1] = 2;

	cout << custom_map[c1] << endl;
	cout << custom_map[c2] << endl;
	cout << custom_map[c3] << endl;
	cout << custom_map[c4] << endl;
}
