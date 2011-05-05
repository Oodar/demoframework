#pragma once

#include "IEvent.h"

class CSnooperEvent : public IEvent
{
public:

	CSnooperEvent();
	EventType getType();


	std::string	m_sTestString;
	static EventType m_kEventName;

};