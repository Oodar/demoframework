// Hi-res timer that uses QueryPerformanceCounter/Frequency

#pragma once
#include <Windows.h>

class CTimer
{
public:

	CTimer();

	void startTiming();
	float timeToNow(); // gets time since startTiming
	float lap(); // gets time since startTiming or last lap call

private:

	// Calculated at construction
	float secsPerCount;

	__int64 startCount;
	__int64	prevCount;
	__int64 currCount;

};