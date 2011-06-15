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
	m_iActiveQueue = 0;
}

bool CEventManager::addListener( EventListenerPtr pListener, EventType eventType )
{
	// Check EventType is valid
	// Check that entry doesn't already exist
		// 1. Check that pEvent->getType() has an entry in the map of types to listeners
		// 2. If it doesn't exist, create an entry
		// 3. If it does exist, add the entry into the map

	std::stringstream listenerString;
	listenerString.str("");

	listenerString << "Attempting to add listener for type: " << eventType.getHash() << " full name: " << eventType.getOriginalString();

	LogMessage( "EVENT", listenerString.str() );

	EventListenerMap::iterator it = m_EventListenerMap.find( eventType );

	if( it == m_EventListenerMap.end() )
	{
		// No event of this type listed
		// Need to create a pair to push into the map
		EventListenerTable newTable;
		newTable.push_back( pListener );

		MapInsertResult insertResult = m_EventListenerMap.insert( MapInsertPair( eventType, newTable ) );

		if( (insertResult.second ) )
		{
			// Successfully inserted
			LogMessage( "EVENT", "Successfully inserted Key/Value pair" );
		}
		else
		{
			// Something went wrong here
			LogMessage( "EVENT", "Key/Value pair already existed in listener map" );
		}
																	
	}
	else
	{
		// Event listed, it points to the key, add the listener
		(*it).second.push_back( pListener );
	}


		
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
	// TODO: This doesn't actually remove queued events, which it should do if they are processed.

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
		LogMessage( "EVENT", eventString.str() );

		// Process events here
		EventListenerMap::iterator findResult = m_EventListenerMap.find( (*it)->getType() );

		std::cout << "findResult, Hash: " << (*findResult).first.getHash();
		std::cout << " Listener table size: " << (*findResult).second.size() << std::endl;

		if( findResult == m_EventListenerMap.end() )
		{
			// Unable to find an entry for this type
			LogMessage( "EVENT", "Unable to find entry for type" );
		}
		else
		{
			// Call everyone that was interested in this event type
			for( EventListenerTable::iterator it2 = (*findResult).second.begin(), it2End = (*findResult).second.end();
						it2 != it2End; it2++ )
			{
				LogMessage( "EVENT", "Calling HandleEvent" );
				(*it2)->HandleEvent( (*it) );
			}
		}


		eventString.str("");
		float addedTime = m_Timer.lap(); // Don't allocate memory in this loop, fix this when not debugging
		accumulatedTime += addedTime;

		eventString << "Time used to process this event: " << addedTime;
		LogMessage( "EVENT", eventString.str() );
	}

	// Need to switch queues here, add any unprocessed events to the start of the
	// fresh queue
	m_iActiveQueue = ( m_iActiveQueue + 1 ) % 2;
	LogMessage( "EVENT", "Switched active queue!" );

}