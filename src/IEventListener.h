#pragma once

#include <boost\shared_ptr.hpp>

#include "IEvent.h"


class IEventListener
{
	// Returns true signal consumption of event
	virtual bool HandleEvent( EventPtr pEvent ) = 0;
};


typedef boost::shared_ptr< IEventListener > EventListenerPtr;