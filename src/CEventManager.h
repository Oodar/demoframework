#include <boost\shared_ptr.hpp>
#include <list>
#include <map>
#include <vector>

#include "IEvent.h"
#include "IEventListener.h"
#include "CTimer.h"

typedef boost::shared_ptr< IEventListener > EventListenerPtr;
typedef boost::shared_ptr< IEvent > EventPtr;
typedef std::list< EventPtr > EventQueue;
typedef std::map< EventType, std::vector< EventListenerPtr > > EventListenerMap;

class CEventManager
{
public:

	static CEventManager* getInstance();
	bool addListener( EventListenerPtr pListener, EventPtr pEvent );
	bool queueEvent( EventPtr pEvent );
	void update( float timeAllowed );

private:

	CEventManager();
	static CEventManager*	m_pInstance;
	
	EventQueue				m_EventQueues[2];
	int						m_iActiveQueue;

	EventListenerMap		m_EventListenerMap;

	CTimer					m_Timer;



};

// TODO
// Implement functions using the EventListenerMap
// Going to need typedefs for the iterator/const_iterators returned
// by std::map find functions, etc, to make the code more readable