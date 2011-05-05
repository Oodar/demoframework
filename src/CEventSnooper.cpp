#include "CEventSnooper.h"

CEventSnooper::CEventSnooper( std::string outputFilePath )
{
	m_OutputFile.open( outputFilePath );
}

bool CEventSnooper::HandleEvent( EventPtr pEvent )
{
	if( m_OutputFile.is_open() )
	{
		m_OutputFile << "Event: " << pEvent->getType().getHash() << ", "
								  << pEvent->getType().getOriginalString() << std::endl;
	}
	else
	{
		LogMessage( "EventSnooper", "Unable to open output file" );
	}

	return true;
}