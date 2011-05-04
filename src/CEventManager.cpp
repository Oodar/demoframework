#include <iostream>
#include <sstream>

#include "CEventManager.h"
#include "Util.h"

CEventManager* CEventManager::m_pInstance = 0;


CEventManager* CEventManager::getInstance()
{
	if( !( m_pInstance ) )
	{
		// No instance currently available, create one
		m_pInstance = new CEventManager();
	}

	return m_pInstance;
}

CEventManager::CEventManager()
{
	// Do nothing
}

bool CEventManager::addListener( EventListenerPtr pListener, EventPtr pEvent )
{
	// Check EventType is valid
	// Check that entry doesn't already exist
		// 1. Check that pEvent->getType() has an entry in the map of types to listeners
		// 2. If it doesn't exist, create an entry
		// 3. If it does exist, add the entry into the map
		
	// Return condition:
		// True: Successfully added the listener to the type's mapping
		// False: Failed to add listener

	return false;
}

bool CEventManager::queueEvent( EventPtr pEvent )
{
	// Return condition:
		// True: Successfully queued the event
		// False: Failed to queue the event

	// TODO: 
	// 1. Check that event type is valid
	// 2. Check that insert was successful
			

	// Push event onto back of queue
	m_EventQueues[ m_iActiveQueue ].push_back( pEvent );


	return false;
}

void CEventManager::update( float timeAllowed )
{
	// timeAllowed: Amount of time allocated to process events in milliseconds
	// Process as many events as possible within timeAllowed.
	
	// Kick off high-resolution timer
	m_Timer.startTiming();

	float accumulatedTime = 0.0f;

	std::stringstream eventString;
	eventString.str("");

	for( EventQueue::iterator it = m_EventQueues[ m_iActiveQueue ].begin(),
			itEnd = m_EventQueues[ m_iActiveQueue ].end(); it != itEnd; it++ )
	{
		// Break the loop should we use up too much time
		if( accumulatedTime > timeAllowed )
		{
			break;
		}

		eventString << "Type: " << (*it)->getType().getHash() << ", " << (*it)->getType().getOriginalString();

		// Process events here

		accumulatedTime += m_Timer.lap();
	}

	LogMessage( "EVENT", eventString.str() );

	// Need to switch queues here, add any unprocessed events to the start of the
	// fresh queue
	m_iActiveQueue = ( m_iActiveQueue + 1 ) % 2;
	LogMessage( "EVENT", "Switched active queue!" );

}