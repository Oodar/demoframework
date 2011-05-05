#pragma once

#include <string>
#include <boost/shared_ptr.hpp>

#include "CHashedString.h"

typedef CHashedString EventType;

class IEvent
{
public:

	virtual EventType getType() = 0;

};

typedef boost::shared_ptr< IEvent >			EventPtr;