#include <boost\shared_ptr.hpp>
#include <list>

#include "IEvent.h"
#include "IEventListener.h"
#include "CTimer.h"

typedef boost::shared_ptr< IEventListener > EventListenerPtr;
typedef boost::shared_ptr< IEvent > EventPtr;
typedef std::list< EventPtr > EventQueue;

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
	
	EventQueue				m_qEventQueues[2];
	int						m_iActiveQueue;

	CTimer					m_Timer;



};