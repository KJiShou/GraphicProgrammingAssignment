#include "pch.h"
#include "Timer.h"

void Timer::Init(int fps)
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeNow);
	QueryPerformanceCounter(&timePrevious);

	requestedFPS = fps;

	intervalsPerFrame = (double)(timerFreq.QuadPart / requestedFPS);
}

int Timer::FramesToUpdate()
{
	int framesToUpdate = 0;
	QueryPerformanceCounter(&timeNow);

	// Get the delta time
	intervalSinceLastUpdate = (double)timeNow.QuadPart - (double)timePrevious.QuadPart;

	framesToUpdate = (int)(intervalSinceLastUpdate / intervalsPerFrame);

	if (framesToUpdate != 0) {
		QueryPerformanceCounter(&timePrevious);
	}

	return framesToUpdate;
}
