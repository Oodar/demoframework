#include <iostream> // For console
#include <fcntl.h>	// For console
#include <io.h>		// For console
#include <Windows.h>

#include "CGameWindow.h"
#include "MyGame.h"

void StartConsole()
{
    AllocConsole();
    int hCrt;
    FILE *hf;

    hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT);
    hf = _fdopen( hCrt, "w" );
    *stdout = *hf;
    int   i = setvbuf( stdout, NULL, _IONBF, 0 );
}


// Windows entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	StartConsole();
	CGameWindow myWindow( hInstance, "DemoFramework" );

	MyGame myGame;
	myWindow.startGame( &myGame, myWindow.getWindowHandle() );

}