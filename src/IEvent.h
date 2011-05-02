#pragma once

#include <string>

#include "CHashedString.h"

typedef CHashedString EventType;

class IEvent
{
public:

	virtual EventType getType() = 0;

};