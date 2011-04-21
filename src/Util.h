#pragma once
#include <string>
#include <iostream>

void inline LogMessage( std::string tag, std::string message )
{
	std::cout << "[" << tag << "]: " << message << std::endl;
}

unsigned int inline DJBHash( const std::string key )
{
	unsigned int hash = 5381;

	for( int i = 0; i < key.length(); i++ )
	{
		hash = (( hash << 5 ) + hash ) + key[i];
	}

	return ( hash & 0x7fffffff );
}