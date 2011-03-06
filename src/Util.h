#pragma once
#include <string>
#include <iostream>

void inline LogMessage( std::string tag, std::string message )
{
	std::cout << "[" << tag << "]: " << message << std::endl;
}