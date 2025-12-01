#include "pch.h"
class Timer
{
public:
	void Init(int);
	int FramesToUpdate();

private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrevious;
	int requestedFPS;
	double intervalsPerFrame;
	double intervalSinceLastUpdate;
};

