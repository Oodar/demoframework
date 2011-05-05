#include <sstream>

#include "CHashedString.h"
#include "Util.h"

CHashedString::CHashedString( std::string sOriginalString )
{
	m_iHash = DJBHash( sOriginalString );
	m_sOriginalString = sOriginalString;

	std::stringstream hashString;
	hashString.str("");

	hashString << "Original String: " << sOriginalString << " Hash: " << m_iHash;

	LogMessage( "HASH", hashString.str() );

}

bool CHashedString::operator< ( CHashedString const &rhs ) const
{
	bool result = false;
	result = getHash() < rhs.getHash();

	return result;
}

unsigned int CHashedString::getHash() const
{
	return m_iHash;
}

std::string CHashedString::getOriginalString()
{
	return m_sOriginalString;
}