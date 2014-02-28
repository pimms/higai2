#include "Timer.h"
#include <string.h>

Timer::Timer() 
{
	memset(&_start, 0, sizeof(clock_t));
	memset(&_end, 0, sizeof(clock_t));
}


void Timer::Start()
{
	_start = clock();
}

void Timer::Stop()
{
	_end = clock();
}


float Timer::Get()
{
	float elapsed = float(_end-_start) / (float)CLOCKS_PER_SEC;
	return elapsed;
}
