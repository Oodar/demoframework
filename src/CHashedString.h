#pragma once

#include <string>

class CHashedString
{
public:

	CHashedString( std::string sOriginalString );

	unsigned int getHash() const;
	std::string getOriginalString();

	bool operator< ( CHashedString const & rhs ) const;
	bool operator==( CHashedString const & rhs ) const;

private:

	std::string m_sOriginalString;
	unsigned int m_iHash;


};