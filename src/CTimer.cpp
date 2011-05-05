#include "CTimer.h"
#include "Util.h"

#include <sstream>

CTimer::CTimer()
{
	LogMessage( "TIME", "Creating timer" );

	// calculate seconds per count
	__int64 countsPerSecond = 0;
	QueryPerformanceFrequency( (LARGE_INTEGER*) &countsPerSecond);

	secsPerCount = 1.0f / (float)countsPerSecond;

	std::stringstream counter;
	counter.str("");
	counter << "Seconds per Count: " << secsPerCount;
	LogMessage( "TIME", counter.str() );


}

void CTimer::startTiming()
{

	QueryPerformanceCounter( (LARGE_INTEGER*) &prevCount );

	// Remember when we started
	startCount = prevCount;
	
	//std::stringstream counter;
	//counter.str("");
	//counter << "Starting time: " << prevCount;

	//LogMessage( "TIME", counter.str() );
}

float CTimer::timeToNow()
{
	__int64 temp;
	QueryPerformanceCounter( (LARGE_INTEGER*) &temp );

	float diff = ( ( temp - startCount ) * secsPerCount );

	std::stringstream counter;
	counter.str("");
	counter << "timeToNow, Count Diff = " << ( temp - startCount );
	//LogMessage( "TIME",  counter.str() );

	counter.str("");
	counter << "timeToNow, secsPerCount = " << secsPerCount;
	//LogMessage( "TIME", counter.str() );

	return diff;
}

float CTimer::lap()
{

	QueryPerformanceCounter( (LARGE_INTEGER*) &currCount );
	float diff = ( ( currCount - prevCount ) * secsPerCount );

	prevCount = currCount;

	return diff;
}