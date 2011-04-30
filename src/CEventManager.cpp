#include <iostream>

#include "CEventManager.h"

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