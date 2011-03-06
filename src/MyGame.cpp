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
		fontDesc.Height = 20;
		fontDesc.Width = 10;
		fontDesc.Weight = FW_NORMAL;
		fontDesc.MipLevels = 0;
		fontDesc.Italic = false;
		fontDesc.CharSet = DEFAULT_CHARSET;
		fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
		fontDesc.Quality = DEFAULT_QUALITY;
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

	// Testing out CTimer
	testTimer.startTiming();


}

void MyGame::render()
{
	if( !SUCCEEDED( m_pDevice->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 255, 255, 255 ), 1.0f, 0 )))
	{
		LogMessage( "GAME", "m_pDevice->Clear failed!");
	}

	float time = testTimer.lap();

	std::stringstream frameTime;
	frameTime.str("");
	frameTime << "Frame time: " << time;


	RECT windowRect;
	GetClientRect( m_hGameWindow, &windowRect );

	m_pDevice->BeginScene();
		m_pFont->DrawText( 0, frameTime.str().c_str(), -1,
							&windowRect, DT_CENTER | DT_VCENTER,
							D3DCOLOR_XRGB( rand() % 256, rand() % 256, rand() % 256 ) );
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