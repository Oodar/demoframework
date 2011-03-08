#include <sstream>

#include "CInput.h"

CInput::CInput()
{
	LogMessage( "INPUT", "Setting up raw input devices" );

	// Keyboard
	m_rID[0].usUsagePage = 1;
	m_rID[0].usUsage = 6;
	m_rID[0].dwFlags = RIDEV_NOLEGACY;
	m_rID[0].hwndTarget = NULL;

	// Mouse
	m_rID[1].usUsagePage = 1;
	m_rID[1].usUsage = 2;
	m_rID[1].dwFlags = 0;
	m_rID[1].hwndTarget = NULL;

	registerDevices();

	m_pInputBuffer = new BYTE[ 40 ];	// Mouse input buffer size = 40
										// Keyboard input buffer size = 32
										// Just use 40

}

CInput::~CInput()
{
	delete m_pInputBuffer;
}

void CInput::registerDevices()
{
	LogMessage( "INPUT", "Registering raw input devices..." );

	if( !( RegisterRawInputDevices( m_rID, 2, sizeof(RAWINPUTDEVICE) )))
	{
		LogMessage( "INPUT", "Unable to register raw input devices" );
	}
	else
	{
		LogMessage( "INPUT", "Successfully registered raw input devices" );
	}
}

void CInput::Update( LPARAM lParam )
{
	// Double check buffer size, it shouldn't be bigger than 40!
	UINT tmp;
	GetRawInputData( (HRAWINPUT)lParam, RID_INPUT, NULL, &tmp, sizeof(RAWINPUTHEADER) );

	if( tmp > 40 )
	{
		std::stringstream bufsize;
		bufsize.str("");
		bufsize << "Raw input buffer size is too big! ( " << tmp << " ). Should be 32 (Keyboard) or 40 (Mouse)";
		LogMessage( "INPUT", bufsize.str() );
	}
	else
	{
		// Actually get the raw input data
		GetRawInputData( (HRAWINPUT)lParam, RID_INPUT, (LPVOID)m_pInputBuffer, &tmp, sizeof(RAWINPUTHEADER) );

		RAWINPUT* rawInput = (RAWINPUT*) m_pInputBuffer;

		if( rawInput->header.dwType == RIM_TYPEMOUSE )
			readMouseData( rawInput );

		if( rawInput->header.dwType == RIM_TYPEKEYBOARD )
			readKeyboardData( rawInput );

	}
}

void CInput::readMouseData( RAWINPUT* rawInput )
{

}

void CInput::readKeyboardData( RAWINPUT* rawInput )
{
	USHORT keyCode = rawInput->data.keyboard.VKey;
	bool keyUp = rawInput->data.keyboard.Flags & RI_KEY_BREAK;

	std::stringstream keyCodeStr;
	keyCodeStr.str("");


	if( keyUp )
	{
		keyCodeStr << "You released: " << keyCode;
		
		// Erase released key from set
		m_setCurrPressed.erase( m_setCurrPressed.find( keyCode ));

	}
	else
	{
		keyCodeStr << "You pressed: " << keyCode;

		// Insert pressed key into set
		m_setCurrPressed.insert( keyCode );
	}

	LogMessage( "INPUT", keyCodeStr.str() );
}