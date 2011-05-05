#include "CSnooperEvent.h"

CSnooperEvent::CSnooperEvent()
{
	m_sTestString = "CSnooperEvent - Test String";
}

EventType CSnooperEvent::getType()
{
	return m_kEventName;
}

EventType CSnooperEvent::m_kEventName = "SnooperEvent";
