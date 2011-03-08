#include <iostream>
#include <sstream>
#include "CGameWindow.h"

CGameWindow::CGameWindow( HINSTANCE hInstance, std::string windowCaption )
{
	m_hInstance = hInstance;
	m_strWindowCaption = windowCaption;
	m_bPaused = false;

	initGameWindow();
	initDirect3D();

}

CGameWindow::~CGameWindow()
{
	if( m_pDevice )
		m_pDevice->Release();
}

LRESULT CGameWindow::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam )
{
	std::stringstream inputstr;
	// Handle WM messages properly here, passed through from StaticMsgProc:
	switch( msg )
	{
	case WM_INPUT:

		// Process raw input here
		m_input.Update( lParam );
		break;

	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	}

	return DefWindowProc( m_hWnd, msg, wParam, lParam );
}

LRESULT CALLBACK CGameWindow::StaticMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	CGameWindow* pThisWindow;

	if( msg == WM_NCCREATE )
	{
		pThisWindow = (CGameWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr( hWnd, GWL_USERDATA, (LONG_PTR)pThisWindow );
	}
	else
	{
		pThisWindow = (CGameWindow*)GetWindowLongPtr( hWnd, GWL_USERDATA );
		if( !pThisWindow )
			return DefWindowProc( hWnd, msg, wParam, lParam );
	}

	// Call non-static msg proc
	pThisWindow->m_hWnd = hWnd;
	return pThisWindow->MsgProc( msg, wParam, lParam );
}

void CGameWindow::initGameWindow()
{
	// Fill out WNDCLASS structure
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = StaticMsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon( 0, IDI_APPLICATION ); // Customize this later
	wc.hCursor = LoadCursor ( 0, IDC_ARROW ); // Override this with custom pointer later
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "HelloWorldApp";

	if( !RegisterClass( &wc ) )
	{
		MessageBox( 0, "RegisterClass failed!", 0, 0 );
		PostQuitMessage( 0 );
	}

	// Default of 800 x 600
	RECT dim = { 0, 0, 800, 600 };

	AdjustWindowRect( &dim, WS_OVERLAPPEDWINDOW, false );

	m_hWnd = CreateWindow(	wc.lpszClassName,
							m_strWindowCaption.c_str(),
							WS_OVERLAPPEDWINDOW,
							100,
							100,
							dim.right,
							dim.bottom,
							0,
							0,
							m_hInstance,
							this );

	if( !m_hWnd )
	{
		MessageBox( 0, "CreateWindow failed!", 0, 0 );
		PostQuitMessage( 0 );
	}

	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );

}

void CGameWindow::initDirect3D()
{
	// Init basic D3D stuff here
	LogMessage( "D3D", "Initializing Direct3D" );
	
	// Create IDirect3D9 object
	m_pD3DObject = Direct3DCreate9( D3D_SDK_VERSION );

	if( !m_pD3DObject )
	{
		MessageBox( 0, "Direct3DCreate9 failed!", 0, 0 );
		PostQuitMessage( 0 );
	}

	// Hardware support?
	D3DDISPLAYMODE mode;
	D3DADAPTER_IDENTIFIER9 identifier;
	DISPLAY_DEVICE dev;
	dev.cb = sizeof( DISPLAY_DEVICE );


	LogMessage( "D3D", "Enumerating adapters and their supported modes:" );

	for( int i = 0; i < m_pD3DObject->GetAdapterCount(); ++i )
	{
		UINT modeCnt = m_pD3DObject->GetAdapterModeCount( i, D3DFMT_X8R8G8B8 );
		m_pD3DObject->GetAdapterIdentifier( (UINT)i, 0, &identifier );

		std::stringstream adapterString;
		adapterString << "Device Name: " << identifier.DeviceName << "\t" << identifier.Description;

		EnumDisplayDevices( identifier.DeviceName, i, &dev, 0 );
		adapterString << "on " << dev.DeviceString;

		LogMessage( "D3D", adapterString.str() );

		for( int j = 0; j < modeCnt; ++j )
		{
			m_pD3DObject->EnumAdapterModes( i, D3DFMT_X8R8G8B8, j, &mode );

			adapterString.str("");
			adapterString << "Width = " << mode.Width << "\t" << "Height = " << mode.Height;
			adapterString << "\t" << "Format = " << mode.Format << "\t" << "Refresh = " << mode.RefreshRate;

			LogMessage( "D3D", adapterString.str() );

		}

		// Check that hardware support is available for our preferred setting on each available adapter:
		m_pD3DObject->GetAdapterDisplayMode( i, &mode );

		// Check that hardware support is available for current mode, windowed
		if( !( SUCCEEDED( m_pD3DObject->CheckDeviceType( i, D3DDEVTYPE_HAL, mode.Format, mode.Format, true ))))
		{
			adapterString.str("");
			adapterString << "Device Name: " << identifier.DeviceName << " does not support D3DDEVTYPE_HAL in format: " << std::endl;
			adapterString << "\t" << "Width = " << mode.Width << " Height = " << mode.Height;
			adapterString << " Format = " << mode.Format << " Refresh = " << mode.RefreshRate;
			adapterString << " Windowed = true";

			LogMessage( "D3D", adapterString.str() );
			
			// Need to quit here - DXTrace?

		}
		else
		{
			adapterString.str("");
			adapterString << "Found D3DDEVTYPE_HAL support in windowed mode on " << identifier.DeviceName << ":" << std::endl;
			adapterString << "\t" << "Width = " << mode.Width << " Height = " << mode.Height;
			adapterString << " Format = " << mode.Format << " Refresh = " << mode.RefreshRate;
			adapterString << " Windowed = true";

			LogMessage( "D3D", adapterString.str() );
		}
		// Hardware support available for non-windowed
		if( !( SUCCEEDED( m_pD3DObject->CheckDeviceType( i, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, false ))))
		{
			adapterString.str("");
			adapterString << "Device Name: " << identifier.DeviceName << " does not support D3DDEVTYPE_HAL in format: " << std::endl;
			adapterString << "\t" << "Width = " << mode.Width << " Height = " << mode.Height;
			adapterString << " Format = " << mode.Format << " Refresh = " << mode.RefreshRate;
			adapterString << " Windowed = false";

			LogMessage( "D3D", adapterString.str() );

			// Need to quit here - DXTrace?
		}
		else
		{
			adapterString.str("");
			adapterString << "Found D3DDEVTYPE_HAL support in non-windowed mode on " << identifier.DeviceName << ":" << std::endl;
			adapterString << "\t" << "Width = " << mode.Width << " Height = " << mode.Height;
			adapterString << " Format = " << mode.Format << " Refresh = " << mode.RefreshRate;
			adapterString << " Windowed = false";

			LogMessage( "D3D", adapterString.str() );
		}

		

	}

	// Check device caps on D3DADAPTER_DEFAULT
	// To Do: Multi-monitor support
	// Check for hardware vertex processing + pure device capabilities
	LogMessage( "D3D", "Checking D3DADAPTER_DEFAULT capabilities:" );

	D3DCAPS9 caps;
	DWORD devBehaviourFlags = 0;
	std::stringstream capsString;

	if( !( SUCCEEDED( m_pD3DObject->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps ) ) ) )
	{
		capsString.str("");
		capsString << "GetDeviceCaps failed!";

		LogMessage( "D3D", capsString.str() );
	}
	else
	{
		
		if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		{
			devBehaviourFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
			capsString.str("");
			capsString << "Hardware vertex processing supported";

			LogMessage( "D3D", capsString.str() );
		}
		else
		{
			devBehaviourFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
			capsString.str("");
			capsString << "Hardware vertex processing not supported, defaulting to software :(";

			LogMessage( "D3D", capsString.str() );
		}

		// Is pure device + hardware t&l supported?
		if( caps.DevCaps & D3DDEVCAPS_PUREDEVICE && devBehaviourFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING )
		{
			devBehaviourFlags |= D3DCREATE_PUREDEVICE;
			capsString.str("");
			capsString << "Pure device supported";

			LogMessage( "D3D", capsString.str() );
		}

	}

	// Fill out D3DPRESENT_PARAMETERS
	ZeroMemory( &m_pPP, sizeof( D3DPRESENT_PARAMETERS ) );
	m_pPP.BackBufferWidth				= 0;
	m_pPP.BackBufferHeight				= 0;
	m_pPP.BackBufferFormat				= D3DFMT_UNKNOWN;
	m_pPP.BackBufferCount				= 1;
	m_pPP.MultiSampleType				= D3DMULTISAMPLE_NONE;
	m_pPP.MultiSampleQuality			= 0;
	m_pPP.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	m_pPP.hDeviceWindow					= m_hWnd;
	m_pPP.Windowed						= true;	// This needs to be dependant upon user choice later
	m_pPP.EnableAutoDepthStencil		= true;
	m_pPP.AutoDepthStencilFormat		= D3DFMT_D24S8;
	m_pPP.Flags							= 0;
	m_pPP.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	m_pPP.PresentationInterval			= D3DPRESENT_INTERVAL_IMMEDIATE; // Should be dependant upon user settings of v-sync

	// Now create device
	if( !SUCCEEDED( m_pD3DObject->CreateDevice(
										D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										m_hWnd,
										devBehaviourFlags,
										&m_pPP,
										&m_pDevice ) ) )
	{
		// Couldn't create D3D Device :(
		LogMessage( "D3D", "CreateDevice failed!" );
	}
	else
	{
		LogMessage( "D3D", "CreateDevice was successful!" );
	}

}

bool CGameWindow::isDeviceLost()
{

	HRESULT hr = m_pDevice->TestCooperativeLevel();

	if( hr == D3DERR_DEVICELOST )
	{
		return true;
	}
	else if( hr == D3DERR_DRIVERINTERNALERROR )
	{
		LogMessage( "GAME", "isDeviceLost -> D3DERR_DRIVERINTERNALERROR" );
		PostQuitMessage( 0 );
		return true;
	}
	else if( hr == D3DERR_DEVICENOTRESET )
	{
		LogMessage( "GAME", "isDeviceLost -> D3DERR_DEVICENOTRESET" );
		LogMessage( "GAME", "Resetting DX9 Device" );

		// Device is lost, but can be reset
		m_pRunningGame->onLostDevice();
		m_pDevice->Reset( &m_pPP );
		m_pRunningGame->onResetDevice();

		return false;
	}
	else
	{
		return false;
	}
}

void CGameWindow::startGame( IGame* pGame, HWND hWnd )
{
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ));

	// local pointer to the currently running game
	m_pRunningGame = pGame;

	pGame->initGame( m_pDevice, hWnd );

	// Message-pumping loop
	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ))
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			// Ask the game to do some stuff - Render/Update, etc
			// This needs to follow the algorithm as per Fix Your Timestep! article @ gafferongames
			if( !isDeviceLost() )
			{
				pGame->update( 0.0f ); // just for illustration, atm
				pGame->render(); // just for illustration, atm
			}
		}
	}

	// If we get here, game window has recieved WM_QUIT message
	// Do some cleanup
	std::cout << "Game exiting, do some cleanup!" << std::endl;
	pGame->endGame();
}

HWND CGameWindow::getWindowHandle() { return m_hWnd; }
HINSTANCE CGameWindow::getInstanceHandle() { return m_hInstance; }