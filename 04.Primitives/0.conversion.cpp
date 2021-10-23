/*
 * 0.conversion.cpp
 *
 *  Created on: Jun 11, 2017
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

int stoi( std::string str )
{
	std::istringstream stm(str) ;
	long long v = 0 ;

	if( stm >> v )
	{
		if( v < std::numeric_limits<int>::min() || v > std::numeric_limits<int>::max() )
			throw std::out_of_range( "my::stoi: out of range" ) ;
		return v ;
	}

	else throw std::invalid_argument( "my::stoi: invalid argument" ) ;
}

template < typename T > std::string to_string( const T& v )
{
	std::ostringstream stm ;
	stm << v ;
	return stm.str() ;
}

int main()
{
	cout << (int) '5' - '0' << endl;

	//to_string(123) does not work in MinGW
	cout << (string) to_string(123) << endl;


	//stoi("123") does not work in MinGW
	cout << (int) stoi("42") << endl;
}


