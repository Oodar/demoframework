// Allows us to track graphical stats:
// Frame Time (ms)
// Frame Rate (fps)
// Tris/Verts

#include <d3dx9.h>
#include <sstream>

#include "CTimer.h"

class CGraphicsStats
{

public:

	CGraphicsStats();

	void startTiming();
	void render( LPD3DXFONT pFont, RECT* textArea );
	void updateFrameRate();

	void addTris( int numTris );
	void subTris( int numTris );

	void addVerts( int numVerts );
	void subVerts( int numVerts );

private:

	CTimer m_frameTimer;
	float	m_fFrameTime;
	float	m_fFrameRate;

	int		m_nNumTris;
	int		m_nNumVerts;

	std::stringstream m_strGraphicsStats;

};