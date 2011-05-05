#pragma once

#include "IEventListener.h"

class CEventSnooper : public IEventListener
{
public:

	CEventSnooper( std::string outputFilePath );

	bool HandleEvent( EventPtr pEvent );
};