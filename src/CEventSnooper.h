#pragma once

#include <iostream>
#include <fstream>


#include "IEventListener.h"
#include "Util.h"

class CEventSnooper : public IEventListener
{
public:

	CEventSnooper( std::string outputFilePath );

	bool HandleEvent( EventPtr pEvent );

private:

	std::ofstream m_OutputFile;
};