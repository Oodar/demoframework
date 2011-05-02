#pragma once

#include <d3dx9.h>

#include "IGame.h"
#include "CInput.h"
#include "Util.h"
#include "CGraphicsStats.h"
#include "CEventManager.h"

class MyGame: public IGame
{

	void initGame( LPDIRECT3DDEVICE9 pDevice, HWND hWnd);

	void render();
	void update( float dT );

	void endGame();

	void setupFontInterface();

	void onLostDevice();
	void onResetDevice();

	CGraphicsStats	m_stats;
	CEventManager*	m_pEventManager;
};