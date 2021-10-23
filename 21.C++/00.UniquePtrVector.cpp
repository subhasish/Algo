/*
 * 00.UniquePtrVector.cpp
 *
 * Problem: Design a class that has vector of objects where each object has an unique_ptr inside
 *
 *  Created on: Apr 17, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
//using namespace std;

// C++:
//		Initializer List & unique_ptr:
//			unique_ptr cannot be used with initializer list. Initializer list always copy constructs
//			all elements. But unique_ptr cannot be copied. So when making a vector of unique_ptr or
//			vector of objects that has unique_ptr inside them cannot be done using initializer list.
//			We need to use emplace_back/push_back.
//
//		Rule of zero:
//			Unless class is not managing memory itself there should not be any need to write
//			constructors.

struct Container
{
	struct Nested{
		std::unique_ptr<Container> node;

		Nested(): node(nullptr) {}
		Nested(std::unique_ptr<Container> t) : node(std::move(t)) {}
	};

	std::vector<Nested> edges;
};

typedef std::unique_ptr<Container> UCont;
typedef Container::Nested Nested;


int main()
{
	auto v = std::vector<Nested>{3};
	v.push_back(std::move(Nested(std::move(std::unique_ptr<Container>(new Container{})))));
	v.push_back(std::move(Nested(std::move(std::unique_ptr<Container>(new Container{})))));
	v.push_back(std::move(Nested(std::move(std::unique_ptr<Container>(new Container{})))));
	std::unique_ptr<Container> object = UCont(new Container { std::move(v) });

}



