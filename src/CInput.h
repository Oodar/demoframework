#pragma once
#include <Windows.h>
#include <set>

#include "Util.h"

class CInput
{

public:

	CInput::CInput();
	CInput::~CInput();

	void Update( LPARAM lParam );

private:

	void registerDevices();
	void readMouseData( RAWINPUT* rawInput );
	void readKeyboardData( RAWINPUT* rawInput );

	BYTE*				m_pInputBuffer;
	RAWINPUTDEVICE		m_rID[2];

	std::set<USHORT>	m_setCurrPressed;

};