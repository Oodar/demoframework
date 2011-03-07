#include "CGraphicsStats.h"
#include "Util.h"

CGraphicsStats::CGraphicsStats()
{
	LogMessage( "GFXSTATS", "Creating CGraphicsStats" );
	m_strGraphicsStats.str("");
	m_strGraphicsStats << "NULL" << std::endl;

	m_nNumVerts = 0;
	m_nNumTris = 0;
}

void CGraphicsStats::startTiming()
{
	m_frameTimer.startTiming();
}

void CGraphicsStats::updateFrameRate()
{
	m_fFrameTime = m_frameTimer.lap();
	m_fFrameRate = 1.0f / m_fFrameTime;
}

void CGraphicsStats::addTris( int numTris ) { m_nNumTris += numTris; }
void CGraphicsStats::subTris( int numTris ) { m_nNumTris -= numTris; }

void CGraphicsStats::addVerts( int numVerts ) { m_nNumVerts += numVerts; }
void CGraphicsStats::subVerts( int numVerts ) { m_nNumVerts -= numVerts; }

void CGraphicsStats::render( LPD3DXFONT pFont, RECT* textArea )
{
	// Render the current stats as text on-screen inside textArea
	// Clear out previous contents of m_strGraphicStats;
	m_strGraphicsStats.str("");

	m_strGraphicsStats << "Frame time: " << m_fFrameTime << std::endl;
	m_strGraphicsStats << "Frame rate: " << m_fFrameRate << std::endl;

	m_strGraphicsStats << "Num verts: " << m_nNumVerts << std::endl;
	m_strGraphicsStats << "Num tris: " << m_nNumTris << std::endl;
	
	pFont->DrawText( 0, m_strGraphicsStats.str().c_str(), -1,
					textArea, DT_LEFT | DT_VCENTER,
					D3DCOLOR_XRGB( 0, 0, 0 ) );
}
