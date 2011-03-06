#pragma once

#include "IGame.h"
#include "Util.h"
#include "CTimer.h"
#include <d3dx9.h>

class MyGame: public IGame
{

	void initGame( LPDIRECT3DDEVICE9 pDevice, HWND hWnd);

	void render();
	void update( float dT );

	void endGame();

	void setupFontInterface();

	void onLostDevice();
	void onResetDevice();

	CTimer testTimer;

};