#pragma once

#include "IEvent.h"


class IEventListener
{
	// Returns true signal consumption of event
	virtual bool HandleEvent( EventType & eventType ) = 0;
};