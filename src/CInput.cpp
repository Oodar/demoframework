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

void CInput::update( LPARAM lParam, HWND hWnd )
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


	// The above raw input is useful for high-res mouse movement, but for GUI it is better to have
	// the mouse coordinates relative to the window
	GetCursorPos( &m_guiCursorPos );
	ScreenToClient( hWnd, &m_guiCursorPos );
}

void CInput::readMouseData( RAWINPUT* rawInput )
{
	// Delta x/y for mouse coords
	long deltaX = rawInput->data.mouse.lLastX;
	long deltaY = rawInput->data.mouse.lLastY;

	// Check mouse buttons and update member variable booleans
	#pragma region Handling Mouse Buttons

	if( rawInput->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN )
	{
		LogMessage( "INPUT", "Mouse: LMB Down!" );
		m_bLMB = true;
	}
	else if( rawInput->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP )
	{
		LogMessage( "INPUT", "Mouse: LMB Up!" );
		m_bRMB = true;
	}

	if( rawInput->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN )
	{
		LogMessage( "INPUT", "Mouse: RMB Down!" );
		m_bRMB = true;
	}
	else if( rawInput->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP )
	{
		LogMessage( "INPUT", "Mouse: RMB Up!" );
		m_bRMB = false;
	}

	// Handle mouse wheel
	if( rawInput->data.mouse.usButtonFlags & RI_MOUSE_WHEEL )
	{
		// Cast from unsigned short to short
		m_usMouseWheelDelta = (short)rawInput->data.mouse.usButtonData; // Negative = scrolling down
																		// Positive = scrolling up

		if( m_usMouseWheelDelta < 0 )
		{
			LogMessage( "INPUT", "Mouse: Wheel scrolling down!" );
		}
		else
		{
			LogMessage( "INPUT", "Mouse: Wheel scrolling up!" );
		}
	}

	#pragma endregion


	

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