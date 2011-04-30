#pragma once

#include <string>

class CHashedString
{
public:

	CHashedString( std::string sOriginalString );

	unsigned int getHash();
	std::string getOriginalString();

private:

	std::string m_sOriginalString;
	unsigned int m_iHash;


};