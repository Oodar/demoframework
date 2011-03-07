#pragma once
#include <Windows.h>

#include "Util.h"

class CInput
{

public:

	CInput::CInput();

	void Update( LPARAM lParam );

private:

	void registerDevices();

	BYTE*			m_pInputBuffer;
	RAWINPUTDEVICE	m_rID[2];

};