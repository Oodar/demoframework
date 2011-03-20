#include "MyGame.h"
#include <sstream>
#include <iostream>
#include <tchar.h> // required for _tcscpy

void MyGame::setupFontInterface()
{
	if( !m_pDevice )
	{
		LogMessage( "GAME", "m_pDevice is not initialised!" );
	}
	else
	{
		LogMessage( "GAME", "Creating font interface" );

		// Fill out D3DXFONT_DESC:
		D3DXFONT_DESC fontDesc;
		fontDesc.Height = 14;
		fontDesc.Width = 0;
		fontDesc.Weight = FW_NORMAL;
		fontDesc.MipLevels = 0;
		fontDesc.Italic = false;
		fontDesc.CharSet = DEFAULT_CHARSET;
		fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
		fontDesc.Quality = CLEARTYPE_QUALITY;
		fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
		// Copy TCHAR into fontDesc.FaceName
		_tcscpy( fontDesc.FaceName, _T("Consolas") );

		if( !SUCCEEDED( D3DXCreateFontIndirect( m_pDevice, &fontDesc, &m_pFont ) ) )
		{
			LogMessage( "GAME", "D3DXCreateFontIndirect failed!" );
		}
		else
		{
			LogMessage( "GAME", "D3DXCreateFontIndirect succeeded!" );
		}
	}
}

void MyGame::initGame( LPDIRECT3DDEVICE9 pDevice, HWND hWnd )
{
	LogMessage( "GAME", "MyGame::initGame called!" );

	// Local pointer to DX9 device
	m_pDevice = pDevice;

	// Local handle to game window
	m_hGameWindow = hWnd;

	// Derp
	setupFontInterface();

	// Testing out CGraphicsStats
	m_stats.startTiming(); // Kick off frame rate timer

	// Testing out hashing strings:
	std::string hashString = "Event_Fire_Weapon";

	size_t h(0);

	for( int i = 0; i < hashString.length(); i++ )
	{
		unsigned highorder = hashString[i] & 0xf80000000;
		h = h << 5;
		h = h ^ ( highorder >> 27 );
		h = h ^ (unsigned int)hashString[i];
	}

	std::stringstream finalHash;
	finalHash.str("");

	finalHash << "Hashed: " << hashString << " to: " << h;

	LogMessage( "EVENT", finalHash.str() );

	hashString = "Event_Fire_Weapon_2";

	h = 0;

	for( int i = 0; i < hashString.length(); i++ )
	{
		unsigned highorder = hashString[i] & 0xf80000000;
		h = h << 5;
		h = h ^ ( highorder >> 27 );
		h = h ^ (unsigned int)hashString[i];
	}

	finalHash.str("");
	finalHash << "Hashed: " << hashString << " to: " << h;

	LogMessage( "EVENT", finalHash.str() );

}

void MyGame::render()
{
	if( !SUCCEEDED( m_pDevice->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 255, 255, 255 ), 1.0f, 0 )))
	{
		LogMessage( "GAME", "m_pDevice->Clear failed!");
	}

	m_stats.updateFrameRate();

	RECT statsRect, windowRect;

	GetClientRect( m_hGameWindow, &windowRect );

	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;

	statsRect.top = 10;
	statsRect.left = 10;
	statsRect.right = width / 2;
	statsRect.bottom = height / 2;

	m_pDevice->BeginScene();
		m_stats.render( m_pFont, &statsRect );
	m_pDevice->EndScene();
	m_pDevice->Present( 0, 0, 0, 0 );

}

void MyGame::update( float dT )
{
}

void MyGame::onLostDevice()
{
	LogMessage( "GAME", "MyGame::onLostDevice" );
}

void MyGame::onResetDevice()
{
	LogMessage( "GAME", "MyGame::onResetDevice" );
}

void MyGame::endGame()
{
	LogMessage( "GAME", "MyGame::endGame called!" );

	// Release COM interfaces here
	if( m_pFont )
		m_pFont->Release();

	// We're not responsible for the DX9 device, so don't bother releasing it
}