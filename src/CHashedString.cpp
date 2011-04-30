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

unsigned int CHashedString::getHash()
{
	return m_iHash;
}

std::string CHashedString::getOriginalString()
{
	return m_sOriginalString;
}