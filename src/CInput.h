#pragma once
#include <Windows.h>
#include <set>

#include "Util.h"

class CInput
{

public:

	CInput::CInput();
	CInput::~CInput();

	void update( LPARAM lParam, HWND hWnd );

private:

	void registerDevices();
	void readMouseData( RAWINPUT* rawInput );
	void readKeyboardData( RAWINPUT* rawInput );

	BYTE*				m_pInputBuffer;
	RAWINPUTDEVICE		m_rID[2];

	std::set<USHORT>	m_setCurrPressed;

	POINT				m_guiCursorPos;
	bool				m_bLMB;
	bool				m_bRMB;
	SHORT				m_usMouseWheelDelta;

};