#pragma once
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

#include "Util.h"
#include "IGame.h"
#include "CInput.h"

class CGameWindow
{

public:
	// Constructor	
	CGameWindow( HINSTANCE hInstance, std::string windowCaption );
	~CGameWindow();

	// Getters
	HINSTANCE getInstanceHandle(); // Return instance handle
	HWND getWindowHandle(); // Return window handle


	// Takes care of initialising the game's window
	void initGameWindow();

	// Takes care of initialising Direct3D  -- Should this be here?
	void initDirect3D();
	bool isDeviceLost();

	// Kicks off and loops game
	void startGame( IGame* pGame, HWND hWnd );

protected:

	std::string		m_strWindowCaption;	// Game window's title-bar caption

	// Instance/Window handles
	HINSTANCE		m_hInstance;
	HWND			m_hWnd;

	// D3D
	IDirect3D9*				m_pD3DObject;
	LPDIRECT3DDEVICE9		m_pDevice;
	D3DPRESENT_PARAMETERS	m_pPP;
	IGame*					m_pRunningGame;
	CInput					m_input;

	bool			m_bPaused;

private:

	// Non-static MsgProc, its actually allowed to see class members!
	LRESULT MsgProc( UINT msg, WPARAM wParam, LPARAM lParam );

	// Handles WM messages, passes them to the non-static version of this function
	static LRESULT CALLBACK StaticMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );	// Messages we care about:
																						// WM_ACTIVATE -- Sent when application activates or deactivates
																						// WM_SIZE -- Called when window is resized (note: this is repeatedly when user drags window size handles)
																						// WM_EXITSIZEMOVE -- Called when user releases the resize bars (update backbuffer here)
																						// WM_CLOSE -- User pressed 'x' button
																						// WM_DESTROY -- Window was destroyed
																						// WM_KEYDOWN -- Key down!
};