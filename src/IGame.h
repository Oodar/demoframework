#pragma once
#include <d3dx9.h>

class IGame
{
public:

	virtual ~IGame() { };
	
	// Whatever overrides this is responsible for making sure game is set up + ready
	// to rock - e.g. creating font/sprite interfaces, getting assets ready etc
	virtual void initGame( LPDIRECT3DDEVICE9 pDevice, HWND hWnd ) = 0;	


	virtual void render() = 0;
	virtual void update( float dT ) = 0;

	virtual void onLostDevice() = 0;
	virtual void onResetDevice() = 0;

	// Clean up
	virtual void endGame() = 0;

protected:

	LPD3DXFONT			m_pFont;
	LPDIRECT3DDEVICE9	m_pDevice;

	HWND				m_hGameWindow;

};